// ======================================================================================
// File         : config.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:14:51 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CONFIG_H_1250525252
#define CONFIG_H_1250525252
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
//  User Config Block
//  In this area user can change the value to order his own version.
///////////////////////////////////////////////////////////////////////////////


// ------------------------------------------------------------------
// Desc: Inline function debug
//  by default, we enable inline function debug in debug mode.
// ------------------------------------------------------------------

#ifdef EX_DEBUG
    #define EX_USE_FORCEINLINE 0
#elif defined (EX_RELEASE)
    #define EX_USE_FORCEINLINE 1
#endif

// ------------------------------------------------------------------
// Desc: Enable exception code or not
// ------------------------------------------------------------------

#ifndef EX_USE_EXCEPTIONS
    #define EX_USE_EXCEPTIONS 1
#endif

// ------------------------------------------------------------------ 
// Desc: Enable multi-thread code or not 
// ------------------------------------------------------------------ 

#ifndef EX_USE_MULTI_THREAD
    #define EX_USE_MULTI_THREAD 1
#endif

///////////////////////////////////////////////////////////////////////////////
// memory configurations 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: System Memory Alignment
// ------------------------------------------------------------------

#define EX_DEFAULT_ALIGNMENT 16

// ------------------------------------------------------------------
// Desc: Set if use system memory alloc
// NOTE: EX_USE_SYSTEM_MEMORY == 1 has same effect as
//          EX_USE_MEMORY_MANAGER = 0 
//          EX_DBG_WITH_CRT = 1 
// ------------------------------------------------------------------

#define EX_USE_SYSTEM_MEMORY 0

// ------------------------------------------------------------------
// Desc: Set if use memory manager or not
// ------------------------------------------------------------------

#define EX_USE_MEMORY_MANAGER 1

// ------------------------------------------------------------------
// Desc: Set if use crt memory debug with memory manager
// ------------------------------------------------------------------

#define EX_DBG_WITH_CRT 0

// ------------------------------------------------------------------
// Desc: Set the default allocator
// ------------------------------------------------------------------

#define EX_ALLOCATOR ::ex::Allocator_dl283
// #define EX_ALLOCATOR ::ex::Allocator_sys

// ------------------------------------------------------------------ 
// Desc: 
// deprecate using CRC, other hash method are good, and not waste of memory
// NOTE: the disadvantage to EX_USE_CRC_TABLE, is you add more 1-kbytes long table 
// NOTE: the disadvantage to EX_USE_CRC_TABLE_FAST, is you add more 4-kbytes long table 
// ------------------------------------------------------------------ 

#define EX_USE_CRC_TABLE 0
#define EX_USE_CRC_TABLE_FAST 0

///////////////////////////////////////////////////////////////////////////////
//  math configurations
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Set the default float precision for math calculation such as compare
// ------------------------------------------------------------------

#define EX_FLOAT_EPS 1e-06f

// ------------------------------------------------------------------
// Desc: Set the default double precision for math calculation such as compare
// ------------------------------------------------------------------

#define EX_DOUBLE_EPS 1e-08

///////////////////////////////////////////////////////////////////////////////
// ext-lib defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: Set if use qt or not
// ------------------------------------------------------------------ 

#ifdef __EX_USE_QT
    #define EX_USE_QT 1
#else
    #define EX_USE_QT 0
#endif

// ------------------------------------------------------------------ 
// Desc: Set if use qt or not
// ------------------------------------------------------------------ 

#ifdef __EX_USE_SDL
    #define EX_USE_SDL 1
#else
    #define EX_USE_SDL 0
#endif

// ------------------------------------------------------------------ 
// Desc: Set if use lua or not 
// ------------------------------------------------------------------ 

#ifdef __EX_USE_LUA
    #define EX_USE_LUA 1
#else
    #define EX_USE_LUA 0
#endif

///////////////////////////////////////////////////////////////////////////////
// after configuration ( some deps define should be reset here ) 
///////////////////////////////////////////////////////////////////////////////

#if EX_DBG_WITH_CRT
    #undef EX_ALLOCATOR
    #define EX_ALLOCATOR ::ex::Allocator_sys
#endif 

#ifdef EX_RELEASE
    #ifdef EX_USE_MEMORY_MANAGER
        #undef EX_USE_MEMORY_MANAGER
    #endif
    #define EX_USE_MEMORY_MANAGER 0
#endif

// #################################################################################
#endif // END CONFIG_H_1250525252
// #################################################################################

