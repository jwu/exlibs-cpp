// ======================================================================================
// File         : external.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:15:00 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EXTERNAL_H_1250525286
#define EXTERNAL_H_1250525286
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// platform include
///////////////////////////////////////////////////////////////////////////////

#if (EX_PLATFORM == EX_PS3) // ps3 

    #include <stdlib.h>
    #include <unistd.h>

    #include <timer.h> // time api
    #include <sys_time.h> // time api
    #include <cell/cell_fs.h> // file
    #include <sys/ppu_thread.h> // thread
    #include <vectormath/cpp/vectormath_aos.h> // vec_float4 math

    // stl container
    #include <pair> 
    #include <multiset>
    #include <multimap>

#elif (EX_PLATFORM == EX_WIN32) // win32

    // if use memory manager and in debug version
    #if ( EX_USE_SYSTEM_MEMORY || (EX_USE_MEMORY_MANAGER && EX_DBG_WITH_CRT) ) && defined (EX_DEBUG)
        #define _CRTDBG_MAP_ALLOC
        // #define _CRTDBG_MAP_ALLOC_NEW // not really helpful!

        #include <stdlib.h>
        #include <crtdbg.h>
    #else
        #include <malloc.h> 
    #endif

    //
    #include <windows.h>
    #include <io.h>
    #include <direct.h>
    #include <process.h>
    #include <sys/stat.h>
    #include <sys/utime.h>
    #include <errno.h>

    // to use the sse intrins in gcc, please add -msse compile flag in makefile of this project
    #include <xmmintrin.h>  // for type __m128

#elif (EX_PLATFORM == EX_XENON) // xenon

    #include <malloc.h> 
    #include <io.h>

#elif (EX_PLATFORM == EX_LINUX) // linux

    #include <malloc.h> 
    #include <io.h>
    #include <endian.h>    /* attempt to define endianness */

    // to use the sse intrins in gcc, please add -msse compile flag in makefile of this project
    #include <xmmintrin.h>  // for type __m128

    // stl container
    #include <pair> 
    #include <multiset>
    #include <multimap>

#endif

///////////////////////////////////////////////////////////////////////////////
// compiler include
///////////////////////////////////////////////////////////////////////////////

#if ( EX_COMPILER == EX_MSVC ) // msvc

    #include <utility> // for std::pair
    #include <xmemory> // for std::allocator
    #include <hash_set>
    #include <xstring>
    #include <string>

#elif ( EX_COMPILER == EX_GCC ) // gcc

    #include <stdint.h>
    // #include <ext/hash_set>
    // #include <bits/basic_string.h>
    #include <bits/stl_algobase.h>
    #include <bits/stl_algo.h>

    #ifndef CHAR_BIT
    #define CHAR_BIT __CHAR_BIT__
    #endif

#endif

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h> 
#include <wchar.h>
#include <new>
#include <math.h>

// stl
// container
#include <list>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>

// iterator
#include <iterator>

///////////////////////////////////////////////////////////////////////////////
// exlibs only ext includes 
// NOTE: the section below include only in exlibs
///////////////////////////////////////////////////////////////////////////////

#ifdef __EX_LIBS

// SDL
#include <SDL/include/SDL.h>

///////////////////////////////////////////////////////////////////////////////
// link static lib for win32
///////////////////////////////////////////////////////////////////////////////

// UNUSED { 
// #if (EX_PLATFORM == EX_WIN32) // win32
//     #pragma comment( lib, "../../ext/expat/lib/libexpatMT.lib" )

//     // DISABLE: disable yaml { 
//     // #ifdef EX_DEBUG
//     //     #pragma comment( lib, "../../ext/libyaml/lib/yaml_d.lib" )
//     // #else
//     //     #pragma comment( lib, "../../ext/libyaml/lib/yaml.lib" )
//     // #endif
//     // } DISABLE end 
// #endif
// } UNUSED end 

#endif

// #################################################################################
#endif // END EXTERNAL_H_1250525286
// #################################################################################
