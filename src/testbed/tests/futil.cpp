// ======================================================================================
// File         : futil.cpp
// Author       : Wu Jie 
// Last Change  : 04/03/2010 | 00:38:32 AM | Saturday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( futil, normal, off )
{
    ex::path_t rawDataPath = ex::core_t::config()->get<const char*>("RawDataPath");

    // test create "res/test_dir"
    {
        ex::path_t path = rawDataPath + ex::path_t("misc/test_dir");

        // remove dir "./res/test_dir" if exists
        if ( ex::futil::dir::exists ( path ) )
        {
            ex::futil::dir::remove (path);
        }
        CHECK ( !ex::futil::dir::exists(path) );

        // create dir "./res/test_dir"
        ex::futil::dir::mkdir (path);
        CHECK ( ex::futil::dir::exists(path.c_str()) );
    }

    // test create "res/test_dir/foo/bar"
    {
        ex::path_t path = rawDataPath + ex::path_t("misc/test_dir/foo/bar");
        ex::path_t path_foo = rawDataPath + ex::path_t("misc/test_dir/foo");
        ex::path_t path_bar = rawDataPath + ex::path_t("misc/test_dir/foo/bar");

        // remove dir "./res/test_dir/foo/bar" if exists
        if ( ex::futil::dir::exists ( path_bar ) )
        {
            ex::futil::dir::remove (path_bar);
        }
        CHECK ( !ex::futil::dir::exists(path_bar) );
        if ( ex::futil::dir::exists ( path_foo ) )
        {
            ex::futil::dir::remove (path_foo);
        }
        CHECK ( !ex::futil::dir::exists(path_foo) );

        // create dir "./res/test_dir/foo/bar"
        CHECK ( ex::futil::dir::mkdir (path) == ex::EResult::not_found ); // failed 
        CHECK ( ex::futil::dir::mkdirs (path) == ex::EResult::ok ); // success
        CHECK ( ex::futil::dir::exists (path) ); 
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( futil, globFiles, off )
{
    ex::path_t rawDataPath = ex::core_t::config()->get<const char*>("RawDataPath");

    {
        ex::path_t path = rawDataPath + ex::path_t("misc/find");
        ex::Array<ex::path_t> result;

        result.clear();
        CHECK ( ex::futil::glob ( path, &result ) ); 
        ex_log("- glob result -\n" );
        ex_log("%s\n", result.to_str<ex::dec>().c_str() );

        result.clear();
        CHECK ( ex::futil::globFiles ( path, &result ) ); 
        ex_log("- globFiles result -\n" );
        ex_log("%s\n", result.to_str<ex::dec>().c_str() );

        result.clear();
        CHECK ( ex::futil::globDirs ( path, &result ) ); 
        ex_log("- globDirs result -\n" );
        ex_log("%s\n", result.to_str<ex::dec>().c_str() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( futil, copy, off )
{
    CHECK ( ex::futil::dir::copy ( "h:/_Test/swig", "h:/_Test/swig.2" ) == ex::EResult::ok ); 
}
