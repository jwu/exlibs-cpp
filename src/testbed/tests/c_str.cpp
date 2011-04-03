// ======================================================================================
// File         : c_str.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 13:21:20 PM | Saturday,September
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

TEST( c_str, split, off )
{
    ex::string_id_t strID ( "Hello" );

    ex::Array<ex::string_t> arr;
    ex::str::splitIntoArray ( "::", "a1::a2::a3::a4::", &arr ); 

    ex::Array<ex::string_t> arr2;
    const char* token_list[3] = {":", ",", "|"}; 
    ex::str::splitIntoArray ( token_list, 3, "a1:a2,a3|a4::", &arr2 ); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( c_str, to_str, off )
{
    using namespace ex;
    ex::printf ( "\n==============================\n" );
    ex::printf ( "Test-String-to_str\n" );
    ex::printf ( "==============================\n" );

    ex::uint8   val1    = 8;
    ex::int8    val2    = -8;
    ex::uint16  val3    = 16;
    ex::int16   val4    = -16;
    ex::uint32  val5    = 32;
    ex::int32   val6    = -32;
    ex::uint64  val7    = 64;
    ex::int64   val8    = -64;
    float   val9    = 1.0f;
    double  val10   = 1.0;
    ClassProbe obj = ClassProbe("Test"); 
    ClassProbe* pObj = &obj; 
    const char* cstr = "Test_cstr";
    const wchar* wcstr = W("Test_wcstr");

    ex::printf ( "\n==============================\n" );
    ex::printf ( "DEC\n" );
    ex::printf ( "==============================\n" );

    ex::printf( "%s\n", to_str<ex::dec>(val1).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val2).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val3).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val4).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val5).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val6).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val7).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val8).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val9).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(val10).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(obj).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(pObj).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(cstr).c_str() );
    ex::printf( "%s\n", to_str<ex::dec>(wcstr).c_str() );

    ex::printf ( "\n==============================\n" );
    ex::printf ( "HEX\n" );
    ex::printf ( "==============================\n" );

    ex::printf( "%s\n", to_str<ex::hex>(val1).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val2).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val3).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val4).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val5).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val6).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val7).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val8).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val9).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(val10).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(obj).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(pObj).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(cstr).c_str() );
    ex::printf( "%s\n", to_str<ex::hex>(wcstr).c_str() );

    ex::printf ( "\n==============================\n" );
    ex::printf ( "DEC|HEX\n" );
    ex::printf ( "==============================\n" );

    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val1).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val2).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val3).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val4).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val5).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val6).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val7).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val8).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val9).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(val10).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(obj).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(pObj).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(cstr).c_str() );
    ex::printf( "%s\n", to_str<ex::dec|ex::hex>(wcstr).c_str() );
}
