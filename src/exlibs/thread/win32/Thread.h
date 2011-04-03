// ======================================================================================
// File         : Thread.h
// Author       : Wu Jie 
// Last Change  : 02/27/2010 | 13:46:07 PM | Saturday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef THREAD_H_1267249574
#define THREAD_H_1267249574
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class Thread 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Thread
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: EState
    // ------------------------------------------------------------------ 

    enum EState 
    {
        eState_Stopped,
        eState_Running,
        eState_Paused
    }; // end enum EState

    // ------------------------------------------------------------------
    // Desc: EPriority 
    // ------------------------------------------------------------------

    enum EPriority
    {
        ePriority_Idle = -15,
        ePriority_Lowest = -2,
        ePriority_BelowNormal = -1,
        ePriority_Normal = 0,
        ePriority_AboveNormal = 1,
        ePriority_Highest = 2,
        ePriority_TimeCritical = 15
    }; // end enum EPriority

    ///////////////////////////////////////////////////////////////////////////////
    // public
    ///////////////////////////////////////////////////////////////////////////////

public:

    Thread ();
    virtual ~Thread ();
    void entry ();

    virtual result_t run () = 0;

    //
    result_t start ();
    result_t pause ();
    result_t resume ( bool _forceResume );
    result_t kill ();
    result_t join ( uint32 _timeout );
    result_t sleep ( uint32 _milli_seconds );

    //
    void setPriority ( EPriority _priority ); 
    EPriority priority () const { return (EPriority)m_priority; }

    //
    void usePriorityBoost ( bool _useBoost ); 
    bool priorityBoost () const { return m_usePriorityBoost; }

    //
    void setName ( const string_t& _name ) { m_name = _name; }
    const string_t& name () const { return m_name; }

    //
    void setAutoRelease ( bool _autoRelease ) { m_autoRelease = _autoRelease; }
    bool autoRelease () const { return m_autoRelease; }

    //
    bool isPaused () { return m_state == eState_Paused; }
    bool isRunning () { return m_state == eState_Running; }
    bool isStopped () { return m_state == eState_Stopped; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void*       m_handle;

    uint32      m_ID;
    string_t    m_name;
    EState      m_state;
    uint        m_stackSize;
    int         m_priority;
    bool        m_usePriorityBoost;
    bool        m_autoRelease;

    Mutex*     m_threadMutex;

    ///////////////////////////////////////////////////////////////////////////////
    // define to not allowed copy
    ///////////////////////////////////////////////////////////////////////////////

private:

    Thread ( const Thread& _other );
    const Thread & operator = ( const Thread & );

}; // end class Thread

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END THREAD_H_1267249574
// #################################################################################

