// ======================================================================================
// File         : Timer.cpp
// Author       : Wu Jie 
// Last Change  : 03/03/2010 | 11:30:44 AM | Wednesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Timer.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// static 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::wait ( const timespan_t& _span )
{
    if ( _span < 0 || _span == timespan_t::INF )
    {
        ex_warning ("Invalid input: the time-span can't be Infinity or minus.");
        return;
    }

    date_time_t start = date_time_t::CurrentDateTime();
    timespan_t elapsed = 0;
    while ( elapsed < _span )
    {
        elapsed = date_time_t::CurrentDateTime() - start;
    }
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Timer::Timer ( const timespan_t& _interval, timeout_callback_t _callback )
    : m_state (eState_Stopped)
    , m_autoDelete (true)
    , m_onStopTick (false)
    , m_interval (_interval)
    , m_lifetime (timespan_t::INF)
    , m_currentLife (0)
    , m_elapsed (0)
    , m_startTime (0,1,1)
    , m_currentTime (0,1,1)
    , m_lastTick (0,1,1)
{
    if ( _callback.isValid() ) {
        addCallback(_callback);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Timer::~Timer ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::tickonce ( bool _tickOnce )
{
    if ( _tickOnce )
    {
        setLifetime(m_interval);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::autoDelete ( bool _autoDelete )
{
    m_autoDelete = _autoDelete;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::setDebugName ( const string_t& _dbgName )
{
#ifdef EX_DEBUG
    m_dbgName = _dbgName;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::setInterval ( timespan_t _span )
{
    m_interval = _span;
    tick ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::setLifetime ( timespan_t _span )
{
    m_lifetime = _span;
    if ( m_lifetime != timespan_t::INF )
        m_onStopTick = true;
    else
        m_onStopTick = false;

    tick ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::restart ()
{
    reset();
    start();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::reset ()
{
    m_currentLife = 0;
    m_state = eState_Stopped;
    m_elapsed = 0;
    m_startTime.set (0,1,1);
    m_currentTime.set (0,1,1);
    m_lastTick.set (0,1,1);

    //
    for ( callbacks_t::iterator iter = m_callbackList.begin(); iter != m_callbackList.end(); ++iter )
    {
        (*iter).enable = true;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::start ()
{
    // ======================================================== 
    // pre-check 
    // ======================================================== 

    //
    if ( isRunning() )
    {
        ex_warning ("the timer already started.");
        return;
    }

    //
    if ( m_interval == 0 )
    {
        ex_warning ("can't not start a timer with 0 interval.");
        return;
    }

    //
    if ( m_callbackList.size() == 0 )
    {
        ex_warning ("can't not start a timer if there is no callback function in the list.");
        return;
    }

    // ======================================================== 
    // reset and start
    // ======================================================== 

    //
    reset ();

    //
    m_state = eState_Running;
    m_startTime = date_time_t::CurrentDateTime();
    m_lastTick = m_startTime;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::stop ()
{
    m_state = eState_Stopped;
    if ( m_autoDelete ) {
        m_autoDelete = false;
        EX_GP(TimerMng)->deleteTimer (this);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::pause ()
{
    m_state = eState_Paused;

    // we save the elapsed time
    m_currentTime = date_time_t::CurrentDateTime();
    m_elapsed = m_currentTime - m_startTime;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::resume ()
{
    m_state = eState_Running;

    // resume the elapsed time
    m_currentTime = date_time_t::CurrentDateTime();
    m_startTime = m_currentTime - m_elapsed;
    m_lastTick = m_currentTime;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::tick ()
{
    if ( isStopped() || isPaused() )
        return;

    //
    m_currentTime = date_time_t::CurrentDateTime();
    timespan_t deltaTime = m_currentTime - m_lastTick;
    m_lastTick = m_currentTime;

    //
    timespan_t elapsed = m_currentTime - m_startTime;
    m_elapsed = elapsed;

    // add lifetime before timeout-check. cause you may use lifeRatio in timeout callback
    m_currentLife += deltaTime;

    // check timeout
    if ( m_elapsed >= m_interval )
    {
        m_elapsed -= m_interval;
        m_startTime = m_currentTime - m_elapsed;
        onTimeout (elapsed);
    }

    // check the life-time
    if ( m_lifetime != timespan_t::INF && m_currentLife >= m_lifetime )
    {
        // the on-stop tick will guarantee that we pass the right ratio to the life-time timeout.
        if ( m_onStopTick ) {
            onTimeout (elapsed);
        }
        stop ();
    }

    return;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Timer::addCallback ( timeout_callback_t _functor )
{
    if ( !_functor.isValid() )
        return EResult::invalid_input;

    SCallbackInfo callback_info;
    callback_info.enable = true;
    callback_info.callback = _functor;

    // push callback functor unique
    for ( callbacks_t::iterator iter = m_callbackList.begin(); iter != m_callbackList.end(); ++iter )
    {
        if ( (*iter).callback == _functor )
            return EResult::already_existed;
    }
    m_callbackList.push_back ( callback_info );
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Timer::removeCallback ( timeout_callback_t _functor )
{
    if ( !_functor.isValid() )
        return EResult::invalid_input;

    // push callback functor unique
    for ( callbacks_t::iterator iter = m_callbackList.begin(); iter != m_callbackList.end(); ++iter )
    {
        if ( (*iter).callback == _functor )
        {
            m_callbackList.erase ( iter );
            return EResult::ok;
        }
    }
    return EResult::not_found;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Timer::onTimeout ( const timespan_t& _elapsed )
{
    uint callback_count = 0;
    for ( callbacks_t::iterator iter = m_callbackList.begin(); iter != m_callbackList.end(); ++iter )
    {
        bool enable_nextTime = false;
        if ( (*iter).enable )
        {
            enable_nextTime =  (*iter).callback( *this, _elapsed );
            (*iter).enable = enable_nextTime;
        }
        if ( enable_nextTime )
        {
            ++callback_count;
        }
    }
    if ( callback_count == 0 )
    {
        stop();
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

