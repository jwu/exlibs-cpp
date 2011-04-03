// ======================================================================================
// File         : Array.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:34 AM | Saturday,September
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

TEST( Array, push_back, off )
{
    //
    ex::Array<int> array;
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array.push_back( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    CHECK ( array.size() == 10 );

    //
    ex::Array<int> array2;
    array2.push_back ( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array2.push_back ( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array2.push_back ( int(ex::mathop::range_rand(0.0f, 2000.0f)) );
    array2.push_back ( array );
    CHECK ( array.size() == 3 );
}

