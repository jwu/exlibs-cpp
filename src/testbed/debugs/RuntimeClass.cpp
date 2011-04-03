// ======================================================================================
// File         : RuntimeClass.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:15 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#include "RuntimeClass.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( RuntimeClass, Debug, off )
{
    // ex::RuntimeClass baseClass;
    ex::CClassA selfClass;  

    if ( ex::CClassA::isA<ex::TextFile>() )
        printf ( "static check pass\n" );

    if ( selfClass.isA( ex::RuntimeClass::classID() ) )
        printf ( "runtime check pass\n" );

#if 0
    if ( selfClass.IsChildOf( baseClass ) )
        printf ( "runtime base check pass\n" );
#endif

}
