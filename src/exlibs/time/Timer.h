// ======================================================================================
// File         : Timer.h
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 10:42:57 AM | Tuesday,March
// Description  : Timer is a class to operate CTime 
// ======================================================================================

// #################################################################################
#ifndef TIMER_H_1267497779
#define TIMER_H_1267497779
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class Timer 
// 
// Purpose: 
//
// NOTE: you need to add EX_GP(TimerMng)->tick() at the beginning the of mainloop 
//       phase in your system.
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Timer
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    // NOTE: the callback function return true/false, 
    //       if false the timer will disable the callback in the list.
    //       if there's no callback enable in the list, the timer will stop.
    typedef Functor <bool,Seq<const Timer&,const timespan_t&> > timeout_callback_t;
    typedef bool (*timeout_pfn_t)( const Timer&, const timespan_t& );

protected:

    struct SCallbackInfo
    {
        bool enable;
        timeout_callback_t callback;
    }; // end struct SCallbackInfo

    typedef List<SCallbackInfo> callbacks_t;

    enum EState
    {
        eState_Running,
        eState_Paused,
        eState_Stopped,
    }; // end enum EState

    friend class TimerMng;

    ///////////////////////////////////////////////////////////////////////////////
    // static functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static void wait ( const timespan_t& _span );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    void restart ();
    void reset ();
    void start ();
    void stop ();
    void pause ();
    void resume ();
    void tick ();

    // if true, it will set lifetime to interval
    void tickonce ( bool _tickonce );

    // default is true, the timer will be released automatically when trigger stop() function.
    // false: you need to manually delete the timer.
    void autoDelete ( bool _autoDelete );

    //
    void setDebugName ( const string_t& _dbgName );

    //
    void setInterval ( timespan_t _span );
    const timespan_t& interval () const { return m_interval; }

    //
    void setLifetime ( timespan_t _span );
    const timespan_t& lifetime () const { return m_lifetime; }

    //
    timespan_t remainTick () { return m_interval - m_elapsed; }
    timespan_t remainLife () { return (m_lifetime == timespan_t::INF) ? timespan_t::INF : (m_lifetime - m_currentLife); }
    float lifeRatio () const { return float(double(m_currentLife.ToMSecs()) / double(m_lifetime.ToMSecs())); }

    //
    template < class OBJ_PTR_T, typename MEM_FN_PTR_T >
    result_t addCallback( const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn ) { return addCallback( timeout_callback_t(_pObj,_pfn) ); }
    result_t addCallback ( timeout_pfn_t _pfn ) { return addCallback( timeout_callback_t(_pfn) ); }
    result_t addCallback ( timeout_callback_t _functor );

    //
    template < class OBJ_PTR_T, typename MEM_FN_PTR_T >
    result_t removeCallback( const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn ) { return removeCallback( timeout_callback_t(_pObj,_pfn) ); }
    result_t removeCallback ( timeout_pfn_t _pfn ) { return removeCallback( timeout_callback_t(_pfn) ); }
    result_t removeCallback ( timeout_callback_t _functor );

    //
    bool isRunning () const { return m_state == eState_Running; }
    bool isPaused () const { return m_state == eState_Paused; }
    bool isStopped () const { return m_state == eState_Stopped; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    Timer ( const timespan_t& _interval = 0, timeout_callback_t _callback = timeout_callback_t() );
    ~Timer ();

    void onTimeout ( const timespan_t& _elapsed );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    EState  m_state;
    bool    m_autoDelete;
    bool    m_onStopTick;

    timespan_t  m_interval;
    timespan_t  m_elapsed;

    timespan_t  m_lifetime;
    timespan_t  m_currentLife;

    date_time_t m_startTime;
    date_time_t m_currentTime;
    date_time_t m_lastTick;

    callbacks_t m_callbackList;

#ifdef EX_DEBUG
    string_t m_dbgName;
#endif

}; // end class Timer

///////////////////////////////////////////////////////////////////////////////
// typedefs
///////////////////////////////////////////////////////////////////////////////

typedef Timer timer_t;

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END TIMER_H_1267497779
// #################################################################################


