// ======================================================================================
// File         : exlibs.cpp
// Author       : Wu Jie 
// Last Change  : 08/13/2010 | 23:39:52 PM | Friday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

///////////////////////////////////////////////////////////////////////////////
// compile message 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// define EX_SHOW_COMPILE_MESSAGE
// ========================================================

#if (EX_COMPILER == EX_MSVC)
    #define EX_SHOW_COMPILE_MESSAGE 1
#elif (EX_COMPILER == EX_GCC)
    #define EX_SHOW_COMPILE_MESSAGE 0
#endif

// ========================================================
// define compile message
// ========================================================

#if EX_SHOW_COMPILE_MESSAGE
    // log title
    #pragma message(" ")
    #pragma message("==========================================")
    #pragma message("exlibs predefine log")
    #pragma message("==========================================")
    #pragma message(" ")
    #pragma message("<<<<<<")
    
    // log compiler
    #if (EX_COMPILER == EX_MSVC)
        #pragma message("Compiler ms-vc: "EX_STRING_EXPAND(EX_COMPILER_VER))
    #elif (EX_COMPILER == EX_GCC)
        #pragma message("Compiler gcc: "EX_STRING_EXPAND(EX_COMPILER_VER))
    #else
        #pragma message("Compiler UNKNOWN: ")
    #endif

    // log configuration
    #if defined (EX_DEBUG)
        #pragma message("Configuration: Debug")
    #elif defined (EX_RELEASE)
        #pragma message("Configuration: Release")
    #endif
    
    // log platform
    #if ( EX_PLATFORM == EX_WIN32 )
        #pragma message("Platform: Win32")
    #elif ( EX_PLATFORM == EX_LINUX )
        #pragma message("Platform: Linux")
    #elif ( EX_PLATFORM == EX_XENON )
        #pragma message("Platform: Xenon")
    #elif ( EX_PLATFORM == EX_PS3 )
        #pragma message("Platform: PS3")
    #endif
    #pragma message("Unicode-Platform: "EX_STRING_EXPAND(EX_UNICODE_PLATFORM))
    #pragma message("Use Unicode : "EX_STRING_EXPAND(EX_USE_UNICODE))
    
    // log endian
    #if ( EX_ENDIAN == EX_BIG_ENDIAN )
        #pragma message("Endian: Big")
    #else
        #pragma message("Endian: Little")
    #endif

    // log use dll or not
    #if (EX_USE_DLL == 1)
        #pragma message("TargeType: dll")
    #else
        #pragma message("TargeType: lib")
    #endif

    // log memory configuration
    #if EX_USE_MEMORY_MANAGER
        #pragma message("Enable Memory Manager")
    #else
        #pragma message("Disable Memory Manager")
    #endif

    #pragma message(">>>>>>")
    #pragma message(" ")
#endif
#undef EX_SHOW_COMPILE_MESSAGE
