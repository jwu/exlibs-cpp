// ======================================================================================
// File         : global_inc.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 08:19:32 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef GLOBAL_INC_H_1281831573
#define GLOBAL_INC_H_1281831573
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// platform for determine EX_LIBS_DLL
#include "global/platform.h"

// dll export/import depends on dll-defines
#ifdef EX_LIBS_DLL
#undef EX_LIBS_DLL
#endif

#if (EX_USE_DLL)
    #ifdef __EX_LIBS
        #define EX_LIBS_DLL EX_DLL_EXPORT
    #else
        #define EX_LIBS_DLL EX_DLL_IMPORT
    #endif
#else
    #define EX_LIBS_DLL 
#endif

// other global decls
#include "global/compiler.h"
#include "global/config.h"
#include "global/external.h"
#include "global/typedefs.h"
#include "global/constants.h"
#include "global/enums.h"
#include "global/fwd_decls.h"
#include "global/macros.h"

// #################################################################################
#endif // END GLOBAL_INC_H_1281831573
// #################################################################################


