// ======================================================================================
// File         : easingCurve.cpp
// Author       : Wu Jie 
// Last Change  : 03/23/2010 | 14:01:01 PM | Tuesday,March
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

TEST( easingCurve, test, off )
{
    ex::curve::linear<float>(0.5f);

    ex::curve::quad<float>::in(0.5f);
    ex::curve::quad<float>::out(0.5f);
    ex::curve::quad<float>::in_out(0.5f);
    ex::curve::quad<float>::out_in(0.5f);

    ex::curve::cubic<float>::in(0.5f);
    ex::curve::cubic<float>::out(0.5f);
    ex::curve::cubic<float>::in_out(0.5f);
    ex::curve::cubic<float>::out_in(0.5f);

    ex::curve::quart<float>::in(0.5f);
    ex::curve::quart<float>::out(0.5f);
    ex::curve::quart<float>::in_out(0.5f);
    ex::curve::quart<float>::out_in(0.5f);

    ex::curve::quint<float>::in(0.5f);
    ex::curve::quint<float>::out(0.5f);
    ex::curve::quint<float>::in_out(0.5f);
    ex::curve::quint<float>::out_in(0.5f);

    ex::curve::sine<float>::in(0.5f);
    ex::curve::sine<float>::out(0.5f);
    ex::curve::sine<float>::in_out(0.5f);
    ex::curve::sine<float>::out_in(0.5f);

    ex::curve::expo<float>::in(0.5f);
    ex::curve::expo<float>::out(0.5f);
    ex::curve::expo<float>::in_out(0.5f);
    ex::curve::expo<float>::out_in(0.5f);

    ex::curve::circ<float>::in(0.5f);
    ex::curve::circ<float>::out(0.5f);
    ex::curve::circ<float>::in_out(0.5f);
    ex::curve::circ<float>::out_in(0.5f);

    ex::curve::elastic<float>::in(0.5f,2.0f,1.0f);
    ex::curve::elastic<float>::out(0.5f,2.0f,1.0f);
    ex::curve::elastic<float>::in_out(0.5f,2.0f,1.0f);
    ex::curve::elastic<float>::out_in(0.5f,2.0f,1.0f);

    ex::curve::back<float>::in(0.5f,2.0f);
    ex::curve::back<float>::out(0.5f,2.0f);
    ex::curve::back<float>::in_out(0.5f,2.0f);
    ex::curve::back<float>::out_in(0.5f,2.0f);

    ex::curve::bounce<float>::in(0.5f,2.0f);
    ex::curve::bounce<float>::out(0.5f,2.0f);
    ex::curve::bounce<float>::in_out(0.5f,2.0f);
    ex::curve::bounce<float>::out_in(0.5f,2.0f);
}


