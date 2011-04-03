// ======================================================================================
// File         : TimerMng.cpp
// Author       : Wu Jie 
// Last Change  : 03/26/2010 | 19:23:05 PM | Friday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//  includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "TimerMng.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// public member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimerMng::TimerMng ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimerMng::~TimerMng ()
{
    for ( timers_t::iterator iter = m_timers.begin(); iter != m_timers.end(); ++iter )
    {
        processDelete(*iter);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timer_t* TimerMng::createTimer ( const timespan_t& _interval, timer_t::timeout_callback_t _callback )
{
    timer_t* pTimer = ex_new timer_t(_interval,_callback);
    this->addTimer (pTimer);
    return pTimer;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimerMng::deleteTimer ( timer_t* _pTimer )
{
    _pTimer->stop();
    m_freeTimers.push_back (_pTimer);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimerMng::tick ()
{
    // tick timers
    for ( timers_t::iterator iter = m_timers.begin(); iter != m_timers.end(); ++iter )
    {
        (*iter)->tick();
    }

    // remove freed timers
    for ( timer_list_t::iterator iter = m_freeTimers.begin(); iter != m_freeTimers.end(); ++iter )
    {
        this->removeTimer (*iter);
        processDelete(*iter);
    }
    m_freeTimers.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimerMng::addTimer ( timer_t* _pTimer )
{
    m_timers.push_back (_pTimer);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimerMng::removeTimer ( timer_t* _pTimer )
{
    timers_t::iterator iter = m_timers.find (_pTimer);
    if ( iter != m_timers.end() )
    {
        m_timers.erase (iter);
    }
    else
    {
        ex_warning ( "the timer is not in the timer list." );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimerMng::processDelete ( timer_t* _pTimer )
{
    // HACK: cause the ex_delete will not access protected destructor, we use this way....
    _pTimer->~Timer ();
    ex::_private::free( _pTimer, EX_GP(EX_ALLOCATOR), __FILE__, __FUNCTION__, __LINE__, ex::EMemop::cpp_delete ); 
    // } HACK end 
}

// ######################### 
} // end namespace ex 
// ######################### 

