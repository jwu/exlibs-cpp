// ======================================================================================
// File         : Functor.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:42 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// pre-test 
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// class CTestClass1 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class CTestClass1
{

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    CTestClass1() {}
    virtual ~CTestClass1() {}

    ///////////////////////////////////////////////////////////////////////////////
    // public member function 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    float testFunction1 ( ex::uint32 _value )
    {
        printf ( "call CTestClass1::testFunction1\n" );
        return float(_value);
    }

    //
    static ex::int32 testFunction2 ( float _value ) 
    {
        printf ( "call CTestClass1::testFunction2\n" );
        return ex::int32(_value);
    }

    // 
    virtual void testFunction3 ( ex::uint32 _value1, float _value2 )
    {
        printf ( "call CTestClass1::testFunction3\n" );
        printf ( "val1 = %d\n", _value1 );
        printf ( "val2 = %f\n", _value2 );
    }

}; // end class CTestClass1

///////////////////////////////////////////////////////////////////////////////
// class CTestClass2 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class CTestClass2 : public CTestClass1
{

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    CTestClass2() {}
    virtual ~CTestClass2() {}

    ///////////////////////////////////////////////////////////////////////////////
    // public member function 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    float testFunction1 ( ex::uint32 _value )
    {
        printf ( "call CTestClass2::testFunction1\n" );
        return float(_value);
    }

    //
    static ex::int32 testFunction2 ( float _value ) 
    {
        printf ( "call CTestClass2::testFunction2\n" );
        return ex::int32(_value);
    }

    // 
    virtual void testFunction3 ( ex::uint32 _value1, float _value2 )
    {
        printf ( "call CTestClass2::testFunction3\n" );
        printf ( "2xval1 = %d\n", _value1 * 2 );
        printf ( "2xval2 = %f\n", _value2 * 2.0f );
    }

}; // end class CTestClass1


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void testFunction1( bool* pResult )
{
    printf("call testFunction1\n");
    *pResult = true;
}



///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Functor, Normal, off )
{
    // ========================================================
    //
    CTestClass1 ct1;
    CTestClass2 ct2;

    // ========================================================
    // 
    ex::Functor<float,ex::Seq<ex::uint32> > c1f1 ( &ct1, &CTestClass1::testFunction1 );
    ex::Functor<ex::int32,ex::Seq<float> > c1f2 ( &CTestClass1::testFunction2 );
    ex::Functor<void,ex::Seq<ex::uint32,float> > c1f3 ( &ct1, &CTestClass1::testFunction3 );

    ex::Functor<float,ex::Seq<ex::uint32> > c2f1 ( &ct2, &CTestClass2::testFunction1 );
    ex::Functor<ex::int32,ex::Seq<float> > c2f2 ( &CTestClass2::testFunction2 );
    ex::Functor<void,ex::Seq<ex::uint32,float> > c2f3 ( &ct2, &CTestClass2::testFunction3 );

    ex::Functor<void,ex::Seq<bool*> > f1 ( &testFunction1 );

    // ========================================================
    // test judege
    ex::Functor<void,ex::Seq<bool*> > f1_test;
    if ( !f1_test.isValid() )
    {
        printf( "f1_test == NULL\n" );
        f1_test = f1;
    }

    if ( f1_test.isValid() )
    {
        bool bRes;
        f1_test(&bRes);
    }

    f1_test.reset();
    if ( !f1_test.isValid() )
    {
        printf( "f1_test == NULL again\n" );
    }

    // ========================================================
    // test normal
    float r1 = c1f1(20);
    printf ( "result = %f\n", r1 );

    ex::int32 r2 = c1f2(33.23f);
    printf ( "result = %d\n", r2 );

    c1f3( 10, 2.3f );

    float r3 = c2f1(40);
    printf ( "result = %f\n", r3 );

    ex::int32 r4 = c2f2(11.283f);
    printf ( "result = %d\n", r4 );

    c2f3( 10, 2.3f );

    bool r5;
    f1( &r5 );
    printf ( "result = %d\n", ex::int32(r5) );

    // ========================================================
    // test copy
    ex::Functor<float,ex::Seq<ex::uint32> > cf1_copy = c2f1;
    cf1_copy(20);
    ex::Functor<ex::int32,ex::Seq<float> > cf2_copy = c2f2;
    cf2_copy(21.2f);
    ex::Functor<void,ex::Seq<ex::uint32,float> > cf3_copy = c2f3;
    cf3_copy(10,2.3f);

    // ======================================================== 
    // test null object 

    ex::Functor<void,ex::Seq<ex::uint32,float> > null_c1f3 ( (CTestClass1*)NULL, &CTestClass1::testFunction3, true );
    null_c1f3.set_object(&ct1);
    null_c1f3( 10, 2.3f );
    null_c1f3.set_object(&ct2);
    null_c1f3( 10, 2.3f );

    ex::Functor<void,ex::Seq<ex::uint32,float> > null_c2f3 ( (CTestClass2*)NULL, &CTestClass2::testFunction3, true );
    null_c2f3.set_object(&ct1);
    null_c2f3( 10, 2.3f );
    null_c2f3.set_object(&ct2);
    null_c2f3( 10, 2.3f );
}
