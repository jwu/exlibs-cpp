// ======================================================================================
// File         : TDelegate.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:39 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testLibs.h"
#include "exLibs/Pattern/Delegate.h"

///////////////////////////////////////////////////////////////////////////////
// pre-test 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// 
void GFunc0()
{
    printf("call GFunc0\n");
}

// ========================================================
// 
bool GFunc0Ret()
{
    printf("call GFunc0Ret\n");
    return true;
}

// ========================================================
// 
void GFunc1( int _i )
{
    printf("call GFunc1 %d\n", _i);
}

// ========================================================
// 
bool GFunc1Ret( int _i )
{
    printf("call GFunc1Ret %d\n", _i);
    return true;
}


///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( TDelegate, Normal, off )
{
    ex::TDelegate0<void> dgGFunc0(&GFunc0);
    ex::TDelegate0<bool> dgGFunc0Ret(&GFunc0Ret);
    ex::TDelegate1<void,int> dgGFunc1(&GFunc1);
    ex::TDelegate1<bool,int> dgGFunc1Ret(&GFunc1Ret);

    ex::TStaticDelegate1<bool,int> sdg = dgGFunc1Ret.ToStaticDelegate(); 

    dgGFunc0();
    dgGFunc0Ret();
    dgGFunc1(20);
    dgGFunc1Ret(20);
    sdg(20);

    ex::string_t string;
    string = string + "hello";
}
