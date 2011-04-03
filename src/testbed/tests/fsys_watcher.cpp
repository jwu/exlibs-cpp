// ======================================================================================
// File         : fsys_watcher.cpp
// Author       : Wu Jie 
// Last Change  : 09/07/2010 | 09:53:59 AM | Tuesday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#include "exlibs/file/win32/fsys_watcher.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( fsys_watcher, dir, off )
{
    ex::fsys::watcher::init ();
    ex::fsys::watcher::add_path( ex::wpath_t(W("e:/projects/tools/_res/test/")) );
    for(;;) {
        ex::sleep(1000);
    }
    ex::fsys::watcher::deinit ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( fsys_watcher, file, on )
{
    ex::fsys::watcher::init ();
    ex::fsys::watcher::add_path( ex::wpath_t(W("e:/projects/test_client/Resource/Config/action.bit")) );
    for(;;) {
        ex::sleep(1000);
    }
    ex::fsys::watcher::deinit ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( fsys_watcher, presure, off )
{
    ex::fsys::watcher::init ();

    ex::Array<ex::wpath_t> files;
    ex_log ("prepare watch files.\n");
    ex::futil::globFiles( ex::wpath_t(W("e:/projects/test_client/Resource/Config/Action/")), &files );
    for ( ex::Array<ex::wpath_t>::iterator iter = files.begin(); iter != files.end(); ++iter ) {
        ex::fsys::watcher::add_path( ex::wpath_t(W("e:/projects/test_client/Resource/Config/Action/")) + *iter );
    }
    for(;;) {
        ex_log ("start watch.\n");
        ex::sleep(1000);
    }
    ex::fsys::watcher::deinit ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( fsys_watcher, dir_and_file, off )
{
    ex::fsys::watcher::init ();
    // ex::fsys::watcher::add_path( ex::wpath_t(W("c:/")) );
    ex::fsys::watcher::deinit ();
}
