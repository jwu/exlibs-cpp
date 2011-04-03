// ======================================================================================
// File         : constants.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:14:53 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CONSTANTS_H_1250525264
#define CONSTANTS_H_1250525264
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

static const int       IndexNone = -1;
static const int       MaxFunctionName = 256;
static const size_t    PtrSize = sizeof(void*);
static const uint32    DefaultCRC = 0xfffffffful;

///////////////////////////////////////////////////////////////////////////////
// platform depends
///////////////////////////////////////////////////////////////////////////////

#if ( EX_PLATFORM == EX_WIN32 )
    static const uint32    MaxPath = MAX_PATH;
#elif ( EX_PLATFORM == EX_LINUX )
    // static const uint32    MaxPath = MAX_PATH;
#elif ( EX_PLATFORM == EX_XENON )
    // static const uint32    MaxPath = MAX_PATH;
#elif ( EX_PLATFORM == EX_PS3 )
    // static const uint32    MaxPath = MAX_PATH;
#endif

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END CONSTANTS_H_1250525264
// #################################################################################

