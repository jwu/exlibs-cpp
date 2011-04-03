// ======================================================================================
// File         : HashMap.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:45 AM | Saturday,September
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

TEST( HashMap, insert, off )
{
    typedef ex::HashMap<int,ClassProbe> ClassProbeHashMap_t;
    {
        ClassProbeHashMap_t hashmap;
        hashmap.insert(0,ClassProbe("0"));
        hashmap.insert(1,ClassProbe("1"));
        hashmap.insert(2,ClassProbe("2"));	
        hashmap.insert(3,ClassProbe("3"));
        hashmap.insert(4,ClassProbe("4"));
        hashmap.insert(5,ClassProbe("5"));

        printf("%s", hashmap.to_str<ex::dec>().c_str() );

        hashmap.insert(6,ClassProbe("6"));
        hashmap.insert(7,ClassProbe("7"));
        hashmap.insert(8,ClassProbe("8"));
        hashmap.insert(9,ClassProbe("9"));
        hashmap.insert(10,ClassProbe("10"));
        hashmap.insert(11,ClassProbe("11"));
        hashmap.insert(12,ClassProbe("12"));
        hashmap.insert(13,ClassProbe("13"));
        hashmap.insert(14,ClassProbe("14"));
        hashmap.insert(15,ClassProbe("15"));
        hashmap.insert(16,ClassProbe("16"));

    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( HashMultiMap, insert, off )
{
    typedef ex::HashMultiMap<int,ClassProbe> ClassProbeHashMultiMap_t;
    {
        ClassProbeHashMultiMap_t hashmap;
        hashmap.insert(0,ClassProbe("0"));
        hashmap.insert(0,ClassProbe("55"));
        hashmap.insert(1,ClassProbe("1"));
        hashmap.insert(2,ClassProbe("2"));	
        hashmap.insert(3,ClassProbe("3"));
        hashmap.insert(4,ClassProbe("4"));
        hashmap.insert(5,ClassProbe("5"));

        printf("%s", hashmap.to_str<ex::dec>().c_str() );

        hashmap.insert(6,ClassProbe("6"));
        hashmap.insert(7,ClassProbe("7"));
        hashmap.insert(8,ClassProbe("8"));
        hashmap.insert(9,ClassProbe("9"));
        hashmap.insert(10,ClassProbe("10"));
        hashmap.insert(11,ClassProbe("11"));
        hashmap.insert(12,ClassProbe("12"));
        hashmap.insert(13,ClassProbe("13"));
        hashmap.insert(14,ClassProbe("14"));
        hashmap.insert(15,ClassProbe("15"));
        hashmap.insert(16,ClassProbe("16"));

        printf("%s", hashmap.to_str<ex::dec>().c_str() );
    }
}
