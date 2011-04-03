// ======================================================================================
// File         : fsys.cpp
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 13:11:53 PM | Tuesday,April
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

TEST( fsys, normal, off )
{
    const char* main_repo_path = "e:/project/dev/exlibs/sln/vc8/_build/msvc/Win32/Debug_dll/bin/res";
    ex::core_t::config()->set ("main_repo", "string", main_repo_path, true );
    ex::fsys::register_ftype ( ex::string_id_t("test"), ex::string_id_t("CTestResource") );
    ex::fsys::register_ftype ( ex::string_id_t("cpy"), ex::string_id_t("CScriptResource") );
    ex::fsys::register_ftype ( ex::string_id_t("tex"), ex::string_id_t("CTexture2DResource") );
    ex::fsys::register_ftype ( ex::string_id_t("txt"), ex::string_id_t("text") );

    ex::fsys::register_ftype ( ex::string_id_t("btx"), ex::string_id_t("bin_texture") );
    ex::fsys::register_ftype ( ex::string_id_t("bpy"), ex::string_id_t("bin_script") );

    ex::uint count = 0;

    // 2-device mount
    {
        // mount 1
        count = ex::fsys::explore ( ex::core_t::config()->get<const char*>("main_repo"), "repo_01" );
        // mount 2
        count = ex::fsys::explore ( ex::path_t("e:/project/release/projects/1.2/test.resource"), "repo_02" );

        ex::fsys::debug_show ();

        // switch
        ex::fsys::mount( ex::string_id_t("repo_02"), ex::string_id_t("repo_01") );
        ex::fsys::debug_show ();

        ex::fsys::unmount( ex::string_id_t("repo_01") );
        ex::fsys::debug_show ();

        // unmount repo_02
        ex::fsys::unmount( ex::string_id_t("repo_02") );
        ex::fsys::debug_show ();
    }

    // 3-device mount
    {
        // mount 1
        count = ex::fsys::explore ( ex::core_t::config()->get<const char*>("main_repo"), "repo_01" );
        // mount 2
        count = ex::fsys::explore ( ex::path_t("e:/project/release/projects/1.2/test.resource"), "repo_02" );
        // mount 3
        count = ex::fsys::explore ( ex::path_t("e:/project/release/projects/1.2/backup"), "repo_03" );

        ex::fsys::debug_show ();

        // switch
        ex::fsys::mount( ex::string_id_t("repo_02"), ex::string_id_t("repo_01") );
        ex::fsys::debug_show ();

        ex::fsys::unmount( ex::string_id_t("repo_01") );
        ex::fsys::debug_show ();

        // unmount repo_02
        ex::fsys::unmount( ex::string_id_t("repo_02") );
        ex::fsys::debug_show ();

        // unmount repo_03
        ex::fsys::unmount( ex::string_id_t("repo_03") );
        ex::fsys::debug_show ();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( fsys, glob, off )
{
    ex::fsys::register_ftype ( ex::string_id_t("test"), ex::string_id_t("CTestResource") );
    ex::fsys::register_ftype ( ex::string_id_t("cpy"), ex::string_id_t("CScriptResource") );
    ex::fsys::register_ftype ( ex::string_id_t("tex"), ex::string_id_t("CTexture2DResource") );
    ex::fsys::register_ftype ( ex::string_id_t("txt"), ex::string_id_t("text") );

    ex::fsys::register_ftype ( ex::string_id_t("btx"), ex::string_id_t("bin_texture") );
    ex::fsys::register_ftype ( ex::string_id_t("bpy"), ex::string_id_t("bin_script") );

    ex::uint count = 0;

    // 2-device mount
    {
        // mount
        count = ex::fsys::explore ( ex::core_t::config()->get<const char*>("main_repo"), "repo_01" );
        count = ex::fsys::explore ( ex::core_t::config()->get<const char*>("builtin_repo"), "repo_02" );
        // count = ex::fsys::explore ( ex::path_t("e:/project/release/projects/1.2/test.resource"), "repo_02" );

        ex::fsys::debug_show ();

        ex::Array<ex::r_path_t> result;
        result.clear();
        ex::fsys::glob ( ex::r_path_t( "main://textures/misc" ), &result );
        ex_log("glob result: %s\n", result.to_str<ex::dec>().c_str() );

        // TODO { 
        // result.clear();
        // ex::fsys::globDirs ( ex::r_path_t( "" ), &result );
        // ex_log("glob result: %s\n", result.to_str<ex::dec>().c_str() );
        // } TODO end 
    }
}

