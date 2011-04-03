// ======================================================================================
// File         : BitArray.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:37 AM | Saturday,September
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

TEST( BitArray, push_back, off )
{
    ex::bit_array_t bitArray;
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(1);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(1);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(1);
    bitArray.push_back(0);
    bitArray.push_back(0);
    bitArray.push_back(0);

    CHECK ( bitArray.size() == 20 );

    ex::bit_array_t::iterator iter = bitArray.begin();
    ex::bit_array_t::iterator iterEnd = bitArray.end();
    for ( ; iter != iterEnd; ++iter )
    {
        printf("%d", bool(*iter));
    }

    // TODO: check value CHECK ( array.size() == 20 );
}

