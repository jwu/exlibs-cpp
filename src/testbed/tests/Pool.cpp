// ======================================================================================
// File         : Pool.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:55 AM | Saturday,September
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

TEST( Pool, Pressure, off )
{
    //
    typedef ex::Pool<ClassProbe> ClassProbeArray_t;
    ClassProbeArray_t array;
    ClassProbeArray_t arrayAssign;
    const int max_size = 1024;
    ClassProbeArray_t::sz_t m_IDs[max_size];

    //
    ClassProbeArray_t::iterator  iter;
    ClassProbeArray_t::iterator  iterEnd;

    //
    {
        for ( int i = 0; i < max_size; ++i )
        {
            m_IDs[i] = array.insert_getindex( ClassProbe() );
        }

        //
        for ( int i = 0; i < max_size / 4; ++i )
        {
            array.erase_at(rand()%max_size);
        }
		
        // test copy start here
        arrayAssign = array;

        //
        for ( int i = 0; i < max_size; ++i )
        {
            array.insert_getindex( ClassProbe() );
            array.erase_at(rand()%max_size);
        }

        //
        for ( int i = 0; i < max_size/2; ++i )
        {
            array.insert_getindex( ClassProbe() );
        }

        arrayAssign.resize(0);
        for ( int i = 0; i < max_size; ++i )
        {
            arrayAssign.insert_getindex( ClassProbe() ); 
        }

        //
        for ( int i = 0; i < max_size / 2; ++i )
        {
            arrayAssign.erase_at(rand()%max_size);
        }

        //
        arrayAssign.resize(0);
        for ( int i = 0; i < max_size; ++i )
        {
            arrayAssign.insert_getindex( ClassProbe() );
        }

        //
        for ( int i = 0; i < max_size / 2; ++i )
        {
            arrayAssign.erase_at(rand()%max_size);
        }
    }
}



// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Pool, Copy, off )
{
    //
    typedef ex::Pool<ClassProbe> ClassProbeArray_t;
    ClassProbeArray_t array;
    ClassProbeArray_t arrayAssign;
    const int max_size = 1024;
    ClassProbeArray_t::sz_t m_IDs[max_size];

    //
    ClassProbeArray_t::iterator  iter;
    ClassProbeArray_t::iterator  iterEnd;

    //
    {
        //
        m_IDs[0] = array.insert_getindex( ClassProbe("00") );
        m_IDs[1] = array.insert_getindex( ClassProbe("01") );
        m_IDs[2] = array.insert_getindex( ClassProbe("02") );
        m_IDs[3] = array.insert_getindex( ClassProbe("03") );
        m_IDs[4] = array.insert_getindex( ClassProbe("04") );
        m_IDs[5] = array.insert_getindex( ClassProbe("05") );
        m_IDs[6] = array.insert_getindex( ClassProbe("06") );
        m_IDs[7] = array.insert_getindex( ClassProbe("07") );
        m_IDs[8] = array.insert_getindex( ClassProbe("08") );
        m_IDs[9] = array.insert_getindex( ClassProbe("09") );
        m_IDs[10] = array.insert_getindex( ClassProbe("10") );

        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        //
        array.erase_at(m_IDs[9]);
        array.erase_at(m_IDs[4]);
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        //
        m_IDs[11] = array.insert_getindex( ClassProbe("11") );
        m_IDs[12] = array.insert_getindex( ClassProbe("12") );
        m_IDs[13] = array.insert_getindex( ClassProbe("13") );
        m_IDs[14] = array.insert_getindex( ClassProbe("14") );
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        // test copy start here
        arrayAssign = array;
        ClassProbeArray_t arrayCopy(arrayAssign);

        m_IDs[15] = arrayAssign.insert_getindex( ClassProbe("15") );
        m_IDs[16] = arrayAssign.insert_getindex( ClassProbe("16") );
        m_IDs[17] = arrayAssign.insert_getindex( ClassProbe("17") );
        m_IDs[18] = arrayAssign.insert_getindex( ClassProbe("18") );

        ex_log("------------------------\n\n" );
        ex_log("%s\n", arrayAssign.to_str<ex::dec>().c_str() );

        ex_log("------------------------\n\n" );
        ex_log("%s\n", arrayCopy.to_str<ex::dec>().c_str() );

        //
        arrayAssign.resize(0);
        ex_log("------------------------\n\n" );
        ex_log("%s\n", arrayAssign.to_str<ex::dec>().c_str() );

        m_IDs[19] = arrayAssign.insert_getindex( ClassProbe("19") );
        m_IDs[20] = arrayAssign.insert_getindex( ClassProbe("20") );
        m_IDs[21] = arrayAssign.insert_getindex( ClassProbe("21") );
        m_IDs[22] = arrayAssign.insert_getindex( ClassProbe("22") );
        ex_log("------------------------\n\n" );
        ex_log("%s\n", arrayAssign.to_str<ex::dec>().c_str() );

        //
        arrayAssign.resize(1);
        ex_log("------------------------\n\n" );
        ex_log("%s\n", arrayAssign.to_str<ex::dec>().c_str() );

		array = arrayAssign;
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );


        //
        arrayAssign.clear();
        ex_log("------------------------\n\n" );
        ex_log("%s\n", arrayAssign.to_str<ex::dec>().c_str() );
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Pool, iterator, off )
{
    //
    typedef ex::Pool<ClassProbe> ClassProbeArray_t;
    ClassProbeArray_t array;

    {
        //
        array.insert_getindex( ClassProbe("01") );
        array.insert_getindex( ClassProbe("02") );
        array.insert_getindex( ClassProbe("03") );
        array.insert_getindex( ClassProbe("04") );
        array.insert_getindex( ClassProbe("05") );
        array.insert_getindex( ClassProbe("06") );
        array.insert_getindex( ClassProbe("07") );
        array.insert_getindex( ClassProbe("08") );
        array.insert_getindex( ClassProbe("09") );
        array.insert_getindex( ClassProbe("10") );

        //
        ClassProbeArray_t::iterator iter = array.begin();
        ClassProbeArray_t::iterator iterEnd = array.end();
        printf ( "====================================\n" );
        for ( ; iter != iterEnd; ++iter )
        {
            printf ( "%s\n", (*iter).to_str<ex::dec>() );
        }

        //
        printf ( "====================================\n" );
        ClassProbeArray_t::r_iterator riter = array.rbegin();
        ClassProbeArray_t::r_iterator riterEnd = array.rend();
        for ( ; riter != riterEnd; ++riter )
        {
            printf ( "%s\n", (*riter).to_str<ex::dec>() );
        }

        //
        printf ( "====================================\n" );
        ClassProbeArray_t::c_iterator const_iter = array.begin();
        ClassProbeArray_t::c_iterator const_iterEnd = array.end();
        for ( ; const_iter != const_iterEnd; ++const_iter )
        {
            printf ( "%s\n", (*const_iter).to_str<ex::dec>() );
        }

        //
        printf ( "====================================\n" );
        ClassProbeArray_t::c_r_iterator const_riter = array.rbegin();
        ClassProbeArray_t::c_r_iterator const_riterEnd = array.rend();
        for ( ; const_riter != const_riterEnd; ++const_riter )
        {
            printf ( "%s\n", (*const_riter).to_str<ex::dec>() );
        }
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Pool, NormalOperate, off )
{
    //
    typedef ex::Pool<ClassProbe> ClassProbeArray_t;
    ClassProbeArray_t array;

    //
    ClassProbeArray_t::iterator  iter;
    ClassProbeArray_t::iterator  iterEnd;

    //
    {
        //
        array.insert_getindex( ClassProbe("01") );
        array.insert_getindex( ClassProbe("02") );
        array.insert_getindex( ClassProbe("03") );
        array.insert_getindex( ClassProbe("04") );
        array.insert_getindex( ClassProbe("05") );
        array.insert_getindex( ClassProbe("06") );
        array.insert_getindex( ClassProbe("07") );
        array.insert_getindex( ClassProbe("08") );
        array.insert_getindex( ClassProbe("09") );
        array.insert_getindex( ClassProbe("10") );
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        //
        array.erase_at(9);
        array.erase_at(4);
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        //
        array.insert_getindex( ClassProbe("11") );
        array.insert_getindex( ClassProbe("12") );
        array.insert_getindex( ClassProbe("13") );
        array.insert_getindex( ClassProbe("14") );
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        //
        array.resize(0);
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );

        //
        array.clear();
        ex_log("------------------------\n\n" );
        ex_log("%s\n", array.to_str<ex::dec>().c_str() );
    }

}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( Pool, push_at, off )
{
    printf ( "\n==============================\n" );
    printf ( "Test-Pool-push_at\n" );
    printf ( "==============================\n" );

    typedef ex::Pool<ClassProbe> ClassProbePool_t;
    ClassProbePool_t pool;

    pool.push_at( 0, ClassProbe("03") );
    pool.push_at( 20, ClassProbe("00") );
    pool.push_at( 1, ClassProbe("01") );
    pool.push_at( 8, ClassProbe("02") );

    //
    printf ( "pool result: %s \n", pool.to_str<ex::dec>().c_str() );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Pool, insert_getindex, off )
{
    printf ( "\n==============================\n" );
    printf ( "Test-Pool-insert_getindex\n" );
    printf ( "==============================\n" );

    typedef ex::Pool<ClassProbe> ClassProbePool_t;
    ClassProbePool_t pool;

    //
    pool.insert_getindex( ClassProbe("01") );
    pool.insert_getindex( ClassProbe("02") );
    pool.insert_getindex( ClassProbe("03") );
    pool.insert_getindex( ClassProbe("04") );
    pool.insert_getindex( ClassProbe("05") );
    pool.insert_getindex( ClassProbe("06") );
    pool.insert_getindex( ClassProbe("07") );
    pool.insert_getindex( ClassProbe("08") );
    pool.insert_getindex( ClassProbe("09") );
    pool.insert_getindex( ClassProbe("10") );
    pool.insert_getindex( ClassProbe("11") );
    pool.insert_getindex( ClassProbe("12") );

    //
    ClassProbePool_t::iterator iter = pool.begin();
    ClassProbePool_t::iterator iterEnd = pool.end();
    for ( ; iter != iterEnd; ++iter )
    {
        printf("%s\n", (*iter).Name);
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Pool, erase, off )
{
    printf ( "\n==============================\n" );
    printf ( "Test-Pool-erase\n" );
    printf ( "==============================\n" );


    typedef ex::Pool<ClassProbe> ClassProbePool_t;
    ClassProbePool_t pool;
    ClassProbePool_t::iterator iter;
    ClassProbePool_t::iterator iterEnd;

    //
    ex_new_in(pool) ClassProbe("01");
    ex_new_in(pool) ClassProbe("02");
    ex_new_in(pool) ClassProbe("03");
    ex_new_in(pool) ClassProbe("04");
    ex_new_in(pool) ClassProbe("05");
    ex_new_in(pool) ClassProbe("06");
    ex_new_in(pool) ClassProbe("07");
    ex_new_in(pool) ClassProbe("08");
    ex_new_in(pool) ClassProbe("09");
    ex_new_in(pool) ClassProbe("10");
    ex_new_in(pool) ClassProbe("11");
    ex_new_in(pool) ClassProbe("12");
    ex_new_in(pool) ClassProbe("13");
    ex_new_in(pool) ClassProbe("14");

    //
    pool.erase_at(0);
    pool.erase_at(1);
    pool.erase_at(2);

    //
    iter = pool.begin();
    iterEnd = pool.end();
    for ( ; iter != iterEnd; ++iter )
    {
        printf("%s\n", (*iter).Name);
    }

}
