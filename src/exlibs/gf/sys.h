// ======================================================================================
// File         : System.h
// Author       : Wu Jie 
// Last Change  : 07/03/2009 | 17:17:33 PM | Friday,July
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SYSTEM_H_1257668883
#define SYSTEM_H_1257668883
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// NOTE: when use getcwd(NULL,0), you need to be responsible for the free. 
// ------------------------------------------------------------------ 

// ======================================================== 
// char
// ======================================================== 

INLINE char* getcwd ( char* _pBuffer, int _maxLen )
{
#if ( EX_PLATFORM == EX_WIN32 ) 
    return ::_getcwd( _pBuffer, _maxLen );
#else
    return ::__getcwd( _pBuffer, _maxLen );
#endif
}

// ======================================================== 
// wchar
// ======================================================== 

INLINE wchar* getcwd ( wchar* _pBuffer, int _maxLen )
{
#if ( EX_PLATFORM == EX_WIN32 ) 
    return (wchar*)::_wgetcwd( (wchar_t*)_pBuffer, _maxLen );
#else
    // TODO:
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// ======================================================== 
// char 
// ======================================================== 

INLINE char* getenv ( const char* _varName )  
{
    return ::getenv( _varName );
}

// ======================================================== 
// wchar 
// ======================================================== 

INLINE wchar* getenv ( const wchar* _varName )  
{
    return (wchar*)::_wgetenv( (const wchar_t*)_varName );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// ======================================================== 
// char 
// ======================================================== 

INLINE void putenv ( const char* _varName )  
{
    ::putenv( _varName );
}

// ======================================================== 
// wchar 
// ======================================================== 

INLINE void putenv ( const wchar* _varName )  
{
    ::_wputenv( (const wchar_t*)_varName );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE uint32 cur_threadID ()
{
#if ( EX_PLATFORM == EX_WIN32 )
    return (uint32)GetCurrentThreadId();
#else
    ex_assert ( false, "todo" );
#endif
}

// ------------------------------------------------------------------
// Desc: CpuCycle
// ------------------------------------------------------------------

INLINE uint64 cpu_cycle()
{
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return uint64(counter.QuadPart);
#else
	uint64 counter;
	__asm__ __volatile__( "mftb %0" : "=r" (counter) );
	return counter;
#endif
}

// ------------------------------------------------------------------
// Desc: cpu_freq
// ------------------------------------------------------------------

INLINE uint64 cpu_freq()
{
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return uint64(freq.QuadPart);    
#elif (EX_PLATFORM == EX_PS3 )
    return sys_time_get_timebase_frequency();
#else
    ex_warning( "please define a default frequency for other platform" );
	return 0;
#endif
}

// ------------------------------------------------------------------
// Desc: sleep
// ------------------------------------------------------------------

INLINE void sleep( uint32 _milli_seconds )
{
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    ::Sleep(_milli_seconds);
#elif (EX_PLATFORM == EX_PS3) 
    sys_timer_usleep( _milli_seconds * 1000 );
#else
    ex_warning( "please define a default frequency for other platform" );
#endif
}

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END SYSTEM_H_1257668883
// #################################################################################


