// ======================================================================================
// File         : Array.cpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 18:01:37 PM | Sunday,August
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

TEST( Array, for, off )
{
    typedef ex::Array<ClassProbe> ClassProbeArray_t;
    {
        ClassProbeArray_t array;
        array.push_back( ClassProbe("01") );
        array.push_back( ClassProbe("02") );
        array.push_back( ClassProbe("03") );
        array.push_back( ClassProbe("04") );
        array.push_back( ClassProbe("05") );
        array.push_back( ClassProbe("06") );
        array.push_back( ClassProbe("07") );
        array.push_back( ClassProbe("08") );
        array.push_back( ClassProbe("09") );
        array.push_back( ClassProbe("10") );

        ClassProbeArray_t::iterator iter = array.begin();
        ClassProbeArray_t::iterator iterEnd = array.end();
        for ( ; iter != iterEnd; ++iter )
        {
            printf ( "%s\n", (*iter).Name );
        }

        ClassProbeArray_t::r_iterator riter = array.rbegin();
        ClassProbeArray_t::r_iterator riterEnd = array.rend();
        for ( ; riter != riterEnd; ++riter )
        {
            printf ( "%s\n", (*riter).Name );
        }

        ClassProbeArray_t::c_iterator const_iter = array.begin();
        ClassProbeArray_t::c_iterator const_iterEnd = array.end();
        for ( ; const_iter != const_iterEnd; ++const_iter )
        {
            printf ( "%s\n", (*const_iter).Name );
        }

        ClassProbeArray_t::c_r_iterator const_riter = array.rbegin();
        ClassProbeArray_t::c_r_iterator const_riterEnd = array.rend();
        for ( ; const_riter != const_riterEnd; ++const_riter )
        {
            printf ( "%s\n", (*const_riter).Name );
        }
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Array, new_in, off )
{
    typedef ex::Array<ClassProbe> ClassProbeArray_t;
    {
        ClassProbeArray_t array;
        ex_new_in(array) ClassProbe("01");
        ex_new_in(array) ClassProbe("02");
        ex_new_in(array) ClassProbe("03");
        ex_new_in(array) ClassProbe("04");
        ex_new_in(array) ClassProbe("05");
        ex_new_in(array) ClassProbe("06");
        ex_new_in(array) ClassProbe("07");
        ex_new_in(array) ClassProbe("08");
        ex_new_in(array) ClassProbe("09");
        ex_new_in(array) ClassProbe("10");
        ex_new_in(array) ClassProbe("11");
        ex_new_in(array) ClassProbe("12");
        ex_new_in(array) ClassProbe("13");
        ex_new_in(array) ClassProbe("14");

        EX_HW_BREAK();
        for ( int i = 0; i < 100; ++i )
            ClassProbe* pProbe = ex_new_in(array) ClassProbe( ex::to_str<ex::dec>(i).c_str() );

        printf( "%s\n", array.to_str<ex::dec>().c_str() );
    }

}
