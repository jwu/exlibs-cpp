// ======================================================================================
// File         : global.h
// Author       : Wu Jie 
// Last Change  : 08/09/2010 | 11:38:21 AM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef GLOBAL_H_1281325103
#define GLOBAL_H_1281325103
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// global includes
///////////////////////////////////////////////////////////////////////////////

#include "widgets/EditorMain.h"

///////////////////////////////////////////////////////////////////////////////
// global defiens
///////////////////////////////////////////////////////////////////////////////

extern EditorMain* g_editor;

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// enums 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: ESingletonLevel for TSingletonHolder in exlibs project 
//  Any project depends on the last project, should inherit the Level
//  NUM from the last one.
//  for example: if a Engine Project depends on exlibs, then
//      ESingletonLevel::Engine_Lowest = ESingletonLevel::exLibs_Lowest
// ------------------------------------------------------------------

namespace ESingletonLevel
{
    enum editor {
        // 
        editor_lv_0 = exlibs_count, 
        editor_lv_1,
        editor_lv_3,
        editor_lv_4,
        editor_lv_5,
        editor_lv_6,
        editor_lv_7,

        // get the total num of the level
        editor_count,         
    }; // end enum exEditor
} // end namespace ESingletonLevel

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END GLOBAL_H_1281325103
// #################################################################################


