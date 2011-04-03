// ======================================================================================
// File         : TypeTraits.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:21:11 AM | Saturday,September
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

void test_functions ( ex::TypeTraits<int>::pointer_t _param1 )
{
    *(_param1) = 20;
}


void test_func2 ( int const* _param1 )
{
    printf( "%d\n", (*_param1) );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( TypeTraits, Normal, off )
{
    int i = 0; 

#if 0
    typedef ex::TypeTraits<int*>::const_t const_int_pointer_t;
    const_int_pointer_t pi = &i;
    (*pi) = 20;

    // const int* pii = &i;
    // pii = &i;
    // // (*pii) = 20; // error

    int* const pii = &i;
    // pii = &i; // error
    (*pii) = 20;
#endif

    typedef ex::TypeTraits<int*>::const_pointee_t test_t;
    test_t val = &i;
    // (*val) = 20;
    val = &i;

    typedef ex::TypeTraits<int*&>::non_reference_t test_t2;
    // test_t2 val2 = &i;
    
    //
    printf ( "%d\n", ex::TypeTraits<test_t>::isConst );
    printf ( "%d\n", ex::TypeTraits<test_t>::isPointer );

    printf ( "%d\n", ex::TypeTraits<int>::isReference );
    printf ( "%d\n", ex::TypeTraits<int&>::isReference );
    printf ( "%d\n", ex::TypeTraits<int*>::isPointer );
    printf ( "%d\n", ex::TypeTraits<int>::isPointer );

    printf ( "%d\n", ex::TypeTraits<int&>::isPointer );
}


