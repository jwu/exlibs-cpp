// ======================================================================================
// File         : Math.cpp
// Author       : Wu Jie 
// Last Change  : 03/23/2010 | 17:41:41 PM | Tuesday,March
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

TEST( mathop, test, off )
{
    float result = ex::mathop::lerp ( 0.5f, 1.0f, 2.0f );
    ex_log("the lerp result is %f\n", result);

    ex::vec2f_t result2 = ex::mathop::lerp ( 0.5f, ex::vec2f_t(0.0f,2.0f), ex::vec2f_t(2.0f, 4.0f) );
    ex_log("the lerp result is %s\n", result2.to_str<ex::dec>().c_str() );

    EX_HW_BREAK();
}

