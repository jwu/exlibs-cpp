// ======================================================================================
// File         : Mutex.cpp
// Author       : Wu Jie 
// Last Change  : 03/01/2010 | 01:25:45 AM | Monday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Mutex.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Mutex::Mutex ()
    : m_Handle (NULL)
{
    m_Handle = CreateMutex ( NULL, FALSE, NULL );
    if ( m_Handle == NULL ) 
    {
        ex_error ( "Couldn't create mutex" );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Mutex::~Mutex ()
{
    if ( m_Handle )
    {
        CloseHandle (m_Handle);
        m_Handle = NULL;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Mutex::Lock ()
{
    if ( m_Handle == NULL )
    {
        ex_warning ( "NULL handle, pls create mutex handle first." );
        return EResult::lock_failed;
    }
	if ( WaitForSingleObject( m_Handle, INFINITE ) == WAIT_FAILED ) 
    {
        ex_error ( "Couldn't wait on mutex" );
        return EResult::lock_failed;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Mutex::Unlock ()
{
    if ( m_Handle == NULL )
    {
        ex_warning ( "NULL handle, pls create mutex handle first." );
        return EResult::lock_failed;
    }
	if ( ReleaseMutex (m_Handle) == FALSE ) 
    {
        ex_error ( "Couldn't release mutex") ;
        return EResult::lock_failed;
	}
    return EResult::ok;
}

// ######################### 
} // end namespace ex 
// ######################### 

