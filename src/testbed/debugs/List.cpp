// ======================================================================================
// File         : List.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:47 AM | Saturday,September
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

TEST( List, erase, off )
{
    typedef ex::List<ClassProbe> CClassProbeList_t; 

    {
        CClassProbeList_t list;
        list.push_back( ClassProbe("01") );
        list.push_back( ClassProbe("02") );
        list.push_back( ClassProbe("03") );
        list.push_back( ClassProbe("04") );
        list.push_back( ClassProbe("05") );
        list.push_back( ClassProbe("06") );
        list.push_back( ClassProbe("07") );
        list.push_back( ClassProbe("08") );
        list.push_back( ClassProbe("09") );
        list.push_back( ClassProbe("10") );
        list.push_back( ClassProbe("11") );
        list.push_back( ClassProbe("12") );
        list.push_back( ClassProbe("13") );
        list.push_back( ClassProbe("14") );
        list.push_back( ClassProbe("15") );
        list.push_back( ClassProbe("16") );
        list.push_back( ClassProbe("17") );
        list.push_back( ClassProbe("18") );
        list.push_back( ClassProbe("19") );
        list.push_back( ClassProbe("20") );

        printf( "%s\n", list.to_str<ex::dec>().c_str() );

        CClassProbeList_t::iterator iter = list.begin();
        CClassProbeList_t::iterator iterEnd = list.end();
        while( iter != iterEnd )
        {
            iter = list.erase(iter); 
        }

        printf( "%s\n", list.to_str<ex::dec>().c_str() );

    }


}

