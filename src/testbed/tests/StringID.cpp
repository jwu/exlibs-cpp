// ======================================================================================
// File         : StringID.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:21:06 AM | Saturday,September
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

TEST( StringID, Normal, off )
{
    printf ( "\n==============================\n" );
    printf ( "StringID Normal Test\n" );
    printf ( "==============================\n" );

    ex::string_id_t str0("zero");
    ex::string_id_t str1("one");
    ex::string_id_t str2("Two");
    ex::string_id_t str3("Three");
    ex::string_id_t str4("Four");
    ex::string_id_t str4_copy("Four");
    ex::string_id_t str5("Five");
    ex::string_id_t str6("Six");
    ex::string_id_t str6_copy("Six");
    ex::string_id_t str7("Seven");
    ex::string_id_t str8("Eight");
    ex::string_id_t str9("Nine");
    ex::string_id_t str10("Ten");

    printf ( "%s\n", ex::to_str<ex::dec>(str0).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str1).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str2).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str3).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str4).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str4_copy).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str5).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str6).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str6_copy).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str7).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str8).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str9).c_str() );
    printf ( "%s\n", ex::to_str<ex::dec>(str10).c_str() );
}
