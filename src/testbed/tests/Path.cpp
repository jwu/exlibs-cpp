// ======================================================================================
// File         : Path.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:54 AM | Saturday,September
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

TEST( Path, normal, off )
{
    const char* filename = "c:/test/test1/test2/test3/test.cpp";

    //
    {
        ex::path_t path1 ("d:\\test\\file.h");
        ex::path_t path2 ("d:/test/file.h");

        CHECK ( path1 == "d:/test/file.h" );
        CHECK ( path2 == "d:/test/file.h" );
        CHECK ( path1 != "D:/Test/File.h" );
        CHECK ( path1 ^= "D:/Test/File.h" );
        CHECK ( path1 == path2 );
    }

    //
    {
        ex::path_t path1 ("d:\\test\\");
        ex::path_t path2 ("d:/test/");
        ex::path_t path3 ("d:\\test");
        ex::path_t path4 ("d:/test");

        CHECK ( path1 == path2 );
        CHECK ( path3 == path4 );
        CHECK ( path1 == "d:/test/" );
        CHECK ( path3 == "d:/test" );
    }

    //
    {
        ex::path_t path1 ("d:/foo//bar//");
        CHECK ( path1 == "d:/foo//bar//" );
        path1.simplify();
        CHECK ( path1 == "d:/foo/bar/" );
    }

    //
    {
        ex::path_t path1 =  ex::path_t().printf( "c:\\%s/%s/%s.h", "Programmes", "win32", "test" );
        CHECK ( path1 == "c:/Programmes/win32/test.h" );
    }

    //
    {
        ex::path_t path1 ( "c:/test1/../test/test2/./test.h" );  
        ex::path_t path2 = path1.getSimplify ();
        CHECK ( path1 != "c:/test/test2/test.h" );
        path1.simplify();
        CHECK ( path1 == "c:/test/test2/test.h" );
        CHECK ( path1 == path2 );
    }

    //
    {
        ex::path_t path1 ( filename );
        ex::path_t::pair_t result;
        result = path1.splitDriver ();

        CHECK ( result.first == "c:" );
        CHECK ( result.second == "/test/test1/test2/test3/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( filename );
        ex::path_t::pair_t result;
        result = path1.split ();

        CHECK ( result.first == "c:/test/test1/test2/test3" );
        CHECK ( result.second == "test.cpp" );

        path1.set ( ex::path_t("test.cpp") );
        result = path1.split ();

        CHECK ( result.first == "test.cpp" );
        CHECK ( result.second == "" );
    }

    //
    {
        ex::path_t path1 ( filename );
        ex::path_t::pair_t result;
        result = path1.splitExt ();

        CHECK ( result.first == "c:/test/test1/test2/test3/test" );
        CHECK ( result.second == "cpp" );
    }

    //
    {
        ex::path_t path1 ( filename );
        ex::path_t path2 = path1.absPath();

        CHECK ( path2 == "c:/test/test1/test2/test3/test.cpp" );

        ex::path_t path3 ( "../test.cpp" );
        path3 = path3.absPath ();

        char c_path[ex::MaxPath];
        ex::getcwd( c_path, int(ex::MaxPath) );
        ex::path_t cwd ( c_path );
        cwd =  cwd.dirName();
        ex::path_t resultPath ("test.cpp");
        resultPath  = cwd + resultPath;

        CHECK ( path3 == resultPath );
    }

    //
    {
        ex::path_t path1 ( filename );
        CHECK ( path1.dirName() == "c:/test/test1/test2/test3" );
        CHECK ( path1.baseName() == "test.cpp" );
        CHECK ( path1.extName() == "cpp" );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( Path, truncate, off )
{
    //
    {
        ex::path_t path1 ( "c:/foo/bar/readme.txt" );
        ex::path_t path2 ( "c:/foo/bar/" );
        path1 -= path2;

        CHECK( path1 == "readme.txt");

        ex::path_t path3 ( "c:/foo/bar/readme.txt" );
        ex::path_t path4 ( "c:/foo/bar" );
        path3 -= path4;

        CHECK( path3 == "readme.txt");
    }

    //
    {
        ex::path_t path1 ( "c:/foo/bar/readme.txt" );
        ex::path_t path2 ( "c:/foo/bar/" );
        ex::path_t path3 = path1 - path2;

        CHECK( path3 == "readme.txt");
    }

    //
    {
        ex::string_t str1 ( "c:/foo/bar/readme.txt" );
        ex::path_t path2 ( "c:/foo/bar/" );
        ex::string_t str3 = str1 - path2;

        CHECK( str3 == "readme.txt");
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( Path, join, off )
{

    // This probably wipes out path so far.  However, it's more
    // complicated if path begins with a drive letter:
    //     1. join('c:', '/a') == 'c:/a'
    //     2. join('c:/', '/a') == 'c:/a'
    //     3. join('c:/a', 'b/c') == 'c:/a/b/c'
    // But
    //     4. join('c:/a', '/b') == '/b'
    //     5. join('c:', 'd:/') = 'd:/'
    //     6. join('c:/', 'd:/') = 'd:/'

    //
    {
        ex::path_t path1 ( "c:" );
        ex::path_t path2 ( "/a/b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "c:/a/b/c/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( "c:/" );
        ex::path_t path2 ( "a/b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "c:/a/b/c/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( "c:/" );
        ex::path_t path2 ( "/a/b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "c:/a/b/c/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( "c:/a" );
        ex::path_t path2 ( "b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "c:/a/b/c/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( "c:/a" );
        ex::path_t path2 ( "/b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "/b/c/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( "c:/a" );
        ex::path_t path2 ( "/b" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "/b" );
    }

    //
    {
        ex::path_t path1 ( "c:" );
        ex::path_t path2 ( "d:/a/b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "d:/a/b/c/test.cpp" );
    }

    //
    {
        ex::path_t path1 ( "c:/" );
        ex::path_t path2 ( "d:/a/b/c/test.cpp" );
        ex::path_t path3 = ex::path_t::join ( path1, path2 ); 

        CHECK ( path3 == "d:/a/b/c/test.cpp" );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( Path, sub, off )
{
    // TODO { 
    // //
    // ex::path_t path1 ( "c:/foo/bar/readme.txt" );
    // ex::path_t path2 ( "c:\\foo\\bar" );
    // path1 -= path2;
    // ex_log("path1 = %s\n", path1.c_str() );
    // } TODO end 
}
