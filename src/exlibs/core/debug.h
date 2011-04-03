// ======================================================================================
// File         : debug.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 10:24:31 AM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DEBUG_H_1250523621
#define DEBUG_H_1250523621
// #################################################################################

// ------------------------------------------------------------------
// Desc: Enable Assert or not
// Params: SERIOUS
//         NORMAL
//         DISABLE
// ------------------------------------------------------------------

#define SERIOUS 0
#define NORMAL  1
#define DISABLE 2

#ifdef EX_DEBUG
    // #define EX_DEBUG_LEVEL SERIOUS // could be NORMAL
    #define EX_DEBUG_LEVEL NORMAL
#elif defined (EX_RELEASE)
    #define EX_DEBUG_LEVEL DISABLE
#endif

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// function decl
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

EX_LIBS_DLL bool assert_failed ( bool* _pDoAssert, const char* _file_name, const char* _function_name, size_t _line_nr, const char* _expr, ... );
EX_LIBS_DLL bool error_msg ( bool* _pDoAssert, const char* _file_name, const char* _function_name, size_t _line_nr, const char* _expr, ... );
EX_LIBS_DLL bool warning_msg ( bool* _pDoAssert, const char* _file_name, const char* _function_name, size_t _line_nr, const char* _expr, ... );

// ------------------------------------------------------------------ 
// Desc: msg box type 
// ------------------------------------------------------------------ 

#define MSG_BOX_NONE    00
#define MSG_BOX_FAILED  01
#define MSG_BOX_ERROR   02
#define MSG_BOX_WARNING 03

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

EX_LIBS_DLL int message_box ( int _msgType, const char* _caption, const char* _expr,  ... );

///////////////////////////////////////////////////////////////////////////////
// help macors 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Hardware Break
// ------------------------------------------------------------------

#ifdef EX_DEBUG
    #if ( EX_PLATFORM == EX_WIN32 )
        #if ( EX_COMPILER == EX_MSVC )
            #define EX_HW_BREAK()   {__asm {int 3}}
        #elif ( EX_COMPILER == EX_GCC )
            #define EX_HW_BREAK()   {__asm__ __volatile__ ("int3");}
        #endif
    #elif ( EX_PLATFORM == EX_LINUX )
        #define EX_HW_BREAK()   {__asm__ __volatile__ ("int3");}
    #elif ( EX_PLATFORM == EX_XENON )
        #define EX_HW_BREAK()   {__debugbreak();}
    #elif ( EX_PLATFORM == EX_PS3 )
        #define EX_HW_BREAK()   __asm__ volatile ( "tw 31,1,1" ) // found in CELL_SDK samples, found "BREAK" tag to get it.
        // #define EX_HW_BREAK()   snPause // need #include <libsn.h> || use __builtin_snpause() #ifdef __SNC__
    #endif
#else
    #define EX_HW_BREAK() EX_NOOP
#endif

// ------------------------------------------------------------------
// Desc: Debug Break
//  debug break is used in debug mode, support user a way to that his condition be break.
//  We use !! below to ensure that any overloaded operators used to evaluate expr do not end up at operator || 
// ------------------------------------------------------------------

#define EX_HW_BREAK_IF(expr) { if(!!(expr)) EX_HW_BREAK(); }

// ------------------------------------------------------------------ 
// Desc: ex_log, ex_warning, ex_error
// ------------------------------------------------------------------ 

// ======================================================== 
// internal warning/error break macro  
// ======================================================== 

// __EX_ERROR_BREAK
#define __EX_ERROR_BREAK(msg,...) \
	do { \
		static bool s_AskBreak = true; \
		if ( s_AskBreak ) \
		{ \
            if( ::ex::error_msg( &s_AskBreak, __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ ) ) \
			{ \
				EX_HW_BREAK(); \
			} \
		} \
        else \
        { \
            EX_GP(::ex::Log)->logError( __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ ); \
        } \
	} while( false )

// __EX_WARNING_BREAK
#define __EX_WARNING_BREAK(msg,...) \
	do { \
		static bool s_AskBreak = true; \
		if ( s_AskBreak ) \
		{ \
            if( ::ex::warning_msg( &s_AskBreak, __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ ) ) \
			{ \
				EX_HW_BREAK(); \
			} \
		} \
        else \
        { \
            EX_GP(::ex::Log)->logWarning( __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ ); \
        } \
	} while( false )

// ======================================================== 
// macro defines 
// ======================================================== 

#define ex_log(msg,...) EX_GP(::ex::Log)->logMsg( msg, ##__VA_ARGS__ )

#if ( EX_DEBUG_LEVEL == SERIOUS )
    #define ex_error(msg,...) __EX_ERROR_BREAK(msg, ##__VA_ARGS__) 
    #define ex_warning(msg,...) __EX_WARNING_BREAK(msg, ##__VA_ARGS__)
#else
    #define ex_error(msg,...) EX_GP(::ex::Log)->logError( __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ )
    #define ex_warning(msg,...) EX_GP(::ex::Log)->logWarning( __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ )
#endif

// ------------------------------------------------------------------ 
// Desc: ex_log_func
// ------------------------------------------------------------------ 

#if ( EX_DEBUG_LEVEL == SERIOUS )
    #define ex_log_func() ex_log ("%s", EX_FUNC_INFO);
#else
    #define ex_log_func()
#endif

// ------------------------------------------------------------------
// Desc: Assert
// ------------------------------------------------------------------

// ========================================================
// internal assert define with break
// ========================================================

// __EX_ASSERT_BREAK
#define __EX_ASSERT_BREAK(expr,msg,...) \
	do { \
		static bool s_DoAssert = true; \
        bool eval = !(expr); \
		if ( s_DoAssert ) \
		{ \
            if( eval && ::ex::assert_failed( &s_DoAssert, __FILE__, __FUNCTION__, __LINE__, #expr" : "msg, ##__VA_ARGS__ ) ) \
			{ \
				EX_HW_BREAK(); \
			} \
		} \
	} while( false )

// __EX_ASSERT_RETURN_BREAK
#define __EX_ASSERT_RETURN_BREAK(expr,ret,msg,...) \
	do { \
		static bool s_DoAssert = true; \
        bool eval = !(expr); \
		if ( s_DoAssert ) \
		{ \
            if( eval && ::ex::assert_failed( &s_DoAssert, __FILE__, __FUNCTION__, __LINE__, #expr" : "msg, ##__VA_ARGS__ ) ) \
			{ \
				EX_HW_BREAK(); \
			} \
		} \
        if ( eval ) \
            return ret; \
	} while( false )

// __EX_ASSERT_EXEC_BREAK
#define __EX_ASSERT_EXEC_BREAK(expr,func,msg,...) \
	do { \
		static bool s_DoAssert = true; \
        bool eval = !(expr); \
        if ( eval ) \
            func; \
		if ( s_DoAssert ) \
		{ \
            if( eval && ::ex::assert_failed( &s_DoAssert, __FILE__, __FUNCTION__, __LINE__, #expr" : "msg, ##__VA_ARGS__ ) ) \
			{ \
				EX_HW_BREAK(); \
			} \
		} \
	} while( false )

// ========================================================
// internal assert define without break
// ========================================================

// #define __EX_ASSERT(expr,msg,...)                           { if(!(expr)) { ::ex::assert_failed( __FILE__, __LINE__, __FUNCTION__, #expr" : "msg, ##__VA_ARGS__ ); } }
// #define __EX_ASSERT_RETURN(expr,ret,msg,...)                { if(!(expr)) { ::ex::assert_failed( __FILE__, __LINE__, __FUNCTION__, #expr" : "msg, ##__VA_ARGS__ ); return ret; } }
// #define __EX_ASSERT_EXEC(expr,func,msg,...)                 { if(!(expr)) { ::ex::assert_failed( __FILE__, __LINE__, __FUNCTION__, #expr" : "msg, ##__VA_ARGS__ ); func; } }

// ========================================================
// define assert with debug level
// ========================================================

#if ( EX_DEBUG_LEVEL == SERIOUS )
    #define ex_assert(expr,msg,...)                     __EX_ASSERT_BREAK(expr, msg, ##__VA_ARGS__)             
    #define ex_assert_slow(expr,msg,...)                __EX_ASSERT_BREAK(expr, msg, ##__VA_ARGS__)
    #define ex_assert_return(expr,ret,msg,...)          __EX_ASSERT_RETURN_BREAK(expr, ret, msg, ##__VA_ARGS__)
    #define ex_assert_exec(expr,func,msg,...)           __EX_ASSERT_EXEC_BREAK(expr, func, msg, ##__VA_ARGS__)
#elif ( EX_DEBUG_LEVEL == NORMAL )
    #define ex_assert(expr,msg,...)                     __EX_ASSERT_BREAK(expr, msg, ##__VA_ARGS__)             
    #define ex_assert_slow(expr,msg,...)                EX_NOOP
    #define ex_assert_return(expr,ret,msg,...)          __EX_ASSERT_RETURN_BREAK(expr, ret, msg, ##__VA_ARGS__)
    #define ex_assert_exec(expr,func,msg,...)           __EX_ASSERT_EXEC_BREAK(expr, func, msg, ##__VA_ARGS__)
#elif ( EX_DEBUG_LEVEL == DISABLE )
    #define ex_assert(expr,msg,...)                     EX_NOOP
    #define ex_assert_slow(expr,msg,...)                EX_NOOP
    #define ex_assert_return(expr,ret,msg,...)          EX_NOOP
    #define ex_assert_exec(expr,func,msg,...)           EX_NOOP
#endif

// ------------------------------------------------------------------ 
// Desc: check
// NOTE: unlike assert, check will run the expr even in release version.
// ------------------------------------------------------------------ 

#if ( EX_DEBUG_LEVEL == SERIOUS )
    #define ex_check(expr,msg,...)              __EX_ASSERT_BREAK(expr, msg, ##__VA_ARGS__)
    #define ex_check_return(expr,ret,msg,...)   __EX_ASSERT_RETURN_BREAK(expr, ret, msg, ##__VA_ARGS__)
    #define ex_check_exec(expr,func,msg,...)    __EX_ASSERT_EXEC_BREAK(expr, func, msg, ##__VA_ARGS__)
#elif ( EX_DEBUG_LEVEL == NORMAL )
    #define ex_check(expr,msg,...)              __EX_ASSERT_BREAK(expr, msg, ##__VA_ARGS__)
    #define ex_check_return(expr,ret,msg,...)   __EX_ASSERT_RETURN_BREAK(expr, ret, msg, ##__VA_ARGS__)
    #define ex_check_exec(expr,func,msg,...)    __EX_ASSERT_EXEC_BREAK(expr, func, msg, ##__VA_ARGS__)
#elif ( EX_DEBUG_LEVEL == DISABLE )
    #define ex_check(expr,msg,...)              (expr)
    #define ex_check_return(expr,ret,msg,...)   { if(!(expr)) { return ret; } }
    #define ex_check_exec(expr,func,msg,...)    { if(!(expr)) { func; } }
#endif

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Wesley Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// NOTE: the different between ex_static_assert and ex_compile_time_assert
//  static assert: can only put in the function define, and only become
//                 effective when this function been compiled
//  compile time assert: can put in any place you want. and will become
//                 effective when this file been compiled
// ------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
// class STATIC_ASSERT_FAILED
// 
// Purpose: Helper structure for the ex_static_assert macro
// 
///////////////////////////////////////////////////////////////////////////////

template<bool> struct STATIC_ASSERT_FAILED;
template<> struct STATIC_ASSERT_FAILED<true> {};

// ------------------------------------------------------------------
// Desc: 
// Invocation: ex_static_assert(expr, msg)
// where:
// expr is a compile-time integral or pointer expression
// msg is a C++ identifier that does not need to be defined
// If expr is zero, msg will appear in a compile-time error message.
// ------------------------------------------------------------------

// #define ex_static_assert(expr, msg) { ::ex::STATIC_ASSERT_FAILED<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 
#define ex_static_assert(expr, msg) { ::ex::STATIC_ASSERT_FAILED<((expr) != 0)> ERROR_STATIC_ASSERT_FAILED; (void)ERROR_STATIC_ASSERT_FAILED; } 

///////////////////////////////////////////////////////////////////////////////
// class COMPILE_TIME_ASSERT_FAILED
// 
// Purpose: Helper structure for the ex_compile_time_assert macro
// 
///////////////////////////////////////////////////////////////////////////////

template<bool> struct COMPILE_TIME_ASSERT_FAILED;
template<> struct COMPILE_TIME_ASSERT_FAILED<true> { enum { value = 1 }; };

// ------------------------------------------------------------------
// Desc: 
// Invocation: ex_compile_time_assert(expr, msg)
// where:
// expr is a compile-time integral or pointer expression
// msg is a C++ identifier that does not need to be defined
// If expr is zero, msg will appear in a compile-time error message.
// ------------------------------------------------------------------

#define ex_compile_time_assert(expr, msg) typedef char compile_time_assert_t_##__LINE__ [::ex::COMPILE_TIME_ASSERT_FAILED<(bool)(expr)>::value]

///////////////////////////////////////////////////////////////////////////////
// data-breakpoint
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: data breakpoint type
// ------------------------------------------------------------------ 

#define DATA_BREAKPOINT_NONE        0
#define DATA_BREAKPOINT_WRITE       1
#define DATA_BREAKPOINT_READ_WRITE  2
#define DATA_BREAKPOINT_EXEC        3

// ------------------------------------------------------------------ 
// Desc: data breakpoint size
// ------------------------------------------------------------------ 

#define DATA_BREAKPOINT_8_BIT   0
#define DATA_BREAKPOINT_16_BIT  1
#define DATA_BREAKPOINT_32_BIT  2
#define DATA_BREAKPOINT_64_BIT  3

// ------------------------------------------------------------------ 
// Desc: SetDataBreakpoint 
// ------------------------------------------------------------------ 

//
EX_LIBS_DLL bool SetDataBreakpoint ( const void* _addr, int _accessType /*DATA_BREAKPOINT_TYPE*/, int _dataSize /*DATA_BREAKPOINT_x_BIT*/ );

//
template < typename T >
bool SetDataBreakpoint ( const T& _data, int _accessType /*DATA_BREAKPOINT_TYPE*/ )
{
    const size_t dataBytes = sizeof(T);
    ex_assert_return ( dataBytes == 1 ||
                       dataBytes == 2 ||
                       dataBytes == 4 ||
                       dataBytes == 8, false, "the dataBytes of T must be 1,2,4,8" );
    int dataSize;
    if (dataBytes == 8)
        dataSize = DATA_BREAKPOINT_64_BIT;
    else if (dataBytes == 4)
        dataSize = DATA_BREAKPOINT_32_BIT;
    else if (dataBytes == 2)
        dataSize = DATA_BREAKPOINT_16_BIT;
    else if (dataBytes == 1)
        dataSize = DATA_BREAKPOINT_8_BIT;
    else
        return false;

    if ( dataBytes != 1 || dataBytes)
    return SetDataBreakpoint( &_data, _accessType, dataBytes );
}

// #########################
} // end namespace ex
// #########################

// #################################################################################
#endif // END DEBUG_H_1250523621
// #################################################################################
