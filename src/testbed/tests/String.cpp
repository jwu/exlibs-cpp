// ======================================================================================
// File         : String.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:21:04 AM | Saturday,September
// Description  : 
// ======================================================================================

// TODO: make it better

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

TEST( String, op_sub_eq, off )
{
    ex::string_t str1 ("Hello_World_This_is_Wu_Jie");
    ex::string_t str2 ("Hello World This is Wu Jie.");

    str1 -= "This";
    ex_log("str1 = %s\n", str1.c_str());
    CHECK( str1 == "Hello_World__is_Wu_Jie" );

    str2 -= "this";
    ex_log("str2 = %s\n", str2.c_str());
    CHECK( str2 == "Hello World This is Wu Jie." );

    str2 -= "Wu Jie";
    ex_log("str2 = %s\n", str2.c_str());
    CHECK( str2 == "Hello World This is ." );

    str2 -= "Hello";
    ex_log("str2 = %s\n", str2.c_str());
    CHECK( str2 == " World This is ." );

    str2 -= "This i";
    ex_log("str2 = %s\n", str2.c_str());
    CHECK( str2 == " World s ." );

    EX_HW_BREAK();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( String, op_sub, off )
{
    ex::string_t str ("Hello World This is Wu Jie.");
    ex::string_t result;

    result = str - "this";
    ex_log("result = %s\n", result.c_str());
    CHECK( result == "Hello World This is Wu Jie." );

    result = str - "Wu Jie";
    ex_log("result = %s\n", result.c_str());
    CHECK( result == "Hello World This is ." );

    result = str - "Hello";
    ex_log("result = %s\n", result.c_str());
    CHECK( result == " World This is Wu Jie." );

    result = str - "This i";
    ex_log("result = %s\n", str.c_str());
    CHECK( result == "Hello World s Wu Jie." );

    EX_HW_BREAK();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( String, normal, off )
{
	const char* str = "THIS::IS::A::TEST";

    {
        ex::string_t str1;
        ex::string_t str2("");
        ex::string_t str3("");

        CHECK( str1 == ex::string_t::null );
        CHECK( str2 == str3 );
        CHECK( str1 == str2 );
    }

    {
        ex::string_t str1(str);
		ex::string_t str2 = str1.left( str1.findFirstOf("::") );
		ex::string_t str3 = str1.right( str1.findFirstOf("::")+strlen("::") );

        printf ("str1: %s\n", str1.c_str());
        printf ("str2: %s\n", str2.c_str());
        printf ("str3: %s\n", str3.c_str());
    }

    {
        ex::string_t str1(str);
        ex::string_t str2(str, 3);

        const char* str_1 = str1.c_str();
        const char* str_2 = str2.c_str();
        printf ("str_1: %d", ex::str::len(str_1));
        printf ("str_2: %d", ex::str::len(str_2));

        char str_3[1024];
        ex::mem::set( str_3, 1, sizeof(char)*1024 );
        ex::str::ncpy( str_3, 1024, str, ex::str::len(str)+1 );

        printf ("str_1: %s", str_1);
        printf ("str_2: %s", str_2);
        printf ("str_3: %s", str_3);
    }

    {
        char test[5] = { 'h', 'e', 'l', 'l', 'o' };
        const char* test2 = "hello";
        printf ( "len:%d, str:%s\n", ex::str::len(test2), test2 );

        ex::string_t strTest ( test, 5 );
        printf ( "len:%d, str:%s\n", strTest.size(), strTest.c_str() );
    }
}
