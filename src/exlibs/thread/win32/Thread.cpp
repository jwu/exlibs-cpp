// ======================================================================================
// File         : Thread.cpp
// Author       : Wu Jie 
// Last Change  : 02/27/2010 | 17:58:54 PM | Saturday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Thread.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

static UINT WINAPI ThreadRunCallback ( void* _pThread )
{
    Thread* pThis = static_cast<Thread*>(_pThread);
    pThis->entry();
    return 0; // No error
}		

// ######################### 
} // end namespace _private 
// ######################### 


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Thread::Thread ()
    : m_handle (NULL)
    , m_ID (-1)
    , m_name ("Unknown")
    , m_state (eState_Stopped)
    , m_stackSize (EX_KB(12))
    , m_threadMutex (NULL)
    , m_priority (ePriority_Normal)
    , m_usePriorityBoost (true)
    , m_autoRelease (false)
{
    if ( m_threadMutex == NULL )
        m_threadMutex = ex_new Mutex();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Thread::~Thread ()
{
    ex_assert ( isStopped(), "thread must be stopped before thread-object destroy!" );

    if ( m_threadMutex )
    {
        ex_delete (m_threadMutex);
        m_threadMutex = NULL;
    }
    if ( m_handle )
    {
        CloseHandle (m_handle);
        m_handle = NULL;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Thread::entry ()
{
    this->run();
    m_state = eState_Stopped;

    if ( m_autoRelease )
        ex_delete (this);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Thread::start ()
{
    TAutoLock<Mutex> lock(m_threadMutex);

    // If the thread is already started
    if ( !isStopped() )
    {
        ex_warning ( "Thread(%s) start failed: the thread already started.", m_name.c_str() );
        return EResult::failed;
    }

    // start the thread
    uint threadID; 
    m_handle = (void*) _beginthreadex( 0,                                   // security
                                       m_stackSize,                         // stack size
                                       _private::ThreadRunCallback,
                                       this,                                // ThreadRunCallback arg_list
                                       CREATE_SUSPENDED,                    // create suspended.
                                       &threadID );
    // error creating thread.
    if ( m_handle == NULL )
    {
        ex_error ( "Thread(%s) start failed: the thread can't be create.", m_name.c_str() );
        return EResult::create_failed;
    }
    m_ID = threadID;

    // suspend the thread
    m_state = eState_Paused;
    setPriority ((EPriority)m_priority);
    usePriorityBoost (m_usePriorityBoost);
    setName (m_name);

    // now start the thread
    ex_check_return ( resume (true) == EResult::ok, EResult::failed, "failed to start thread %s", m_name.c_str() );
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Thread::pause ()
{
    TAutoLock<Mutex> lock(m_threadMutex);

    // pre-check
    if ( m_ID == cur_threadID() )
    {
        ex_warning ( "Thread(%s) pause failed: thread cannot pause itself.", m_name.c_str() );
        return EResult::failed;
    }
    if ( m_handle == NULL )
    {
        ex_warning ( "Thread(%s) pause failed: invalid handle", m_name.c_str() );
        return EResult::failed;
    }

    // process
    if( isRunning() || isPaused() )
    {
        SuspendThread(m_handle);         
        m_state = eState_Paused;
    }
    else
    {        
        ex_warning( "Thread(%s) pause failed: trying to pause a non-running thread.", m_name.c_str() );
        return EResult::failed;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Thread::resume ( bool _forceResume )
{
    TAutoLock<Mutex> lock(m_threadMutex);

    // pre-check
    if ( m_ID == cur_threadID() )
    {
        ex_warning ( "Thread(%s) resume failed: cannot resume itself since it is paused!", m_name.c_str() );
        return EResult::failed;
    }
    if ( m_handle == NULL )
    {
        ex_warning ( "Thread(%s) resume failed: invalid handle", m_name.c_str() );
        return EResult::failed;
    }

    if ( !isPaused() )
    {
        ex_warning ( "Thread(%s) resume failed: the thread is not paused.", m_name.c_str() );
        return EResult::failed;
    }

    // process
    DWORD previousCount;
    do
    {
        previousCount = ResumeThread(m_handle);

        // If we force a resume, loop until previousCount is 1 or smaller 
        // (indicates that the thread was resumed)
    } while ( _forceResume && previousCount > 1 );

    // If thread got resumed
    if ( previousCount <= 1 )
    {
        // TODO { 
        // //it is possible that the thread finished between the ResumeThread() and this point. (Win64)
        // //In this case, we must not set the thread running because it will indicate a false state and lead to possible misbehaviors.
        // if (ex::Atomic::Add((S32&)m_state, 0) != Ended)
        //     ex::Atomic::Exchange((S32&)m_state, Running);
        // } TODO end 
        m_state = eState_Running;
        return EResult::ok;
    }

    //
    ex_assert ( _forceResume == false, "force resume should not be failed!" );
    return EResult::failed;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Thread::kill ()
{
    if ( m_handle)
    {
        if ( join (1000) == EResult::failed )
        {
            TerminateThread( m_handle, FALSE );
            ex_warning ( "force kill the thread(%s)", m_name.c_str() );
            if ( m_autoRelease )
                ex_delete (this);
        }
        m_state = eState_Stopped;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Thread::join ( uint32 _timeout )
{
    // On MS platform, this is the correct way of waiting for a thread to end
    DWORD Ret = WaitForSingleObject( m_handle, _timeout == 0 ? INFINITE : _timeout );
    if ( Ret == WAIT_TIMEOUT )
    {
        ex_warning ( "Thread(%s) join failed: Time out!", m_name.c_str() );
        return EResult::failed;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Thread::sleep ( uint32 _milli_seconds )
{
    ex_error ("pls impl it!");
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Thread::setPriority ( EPriority _priority )
{
    if ( m_handle )
    {
        m_priority = (int)_priority;
        SetThreadPriority( m_handle, m_priority );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Thread::usePriorityBoost ( bool _useBoost )
{
    if ( m_handle )
    {
        m_usePriorityBoost = _useBoost;
        SetThreadPriorityBoost( m_handle, m_usePriorityBoost );
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

