// ======================================================================================
// File         : Thread.cpp
// Author       : Wu Jie 
// Last Change  : 03/01/2010 | 13:16:43 PM | Monday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

class CThread_a : public ex::Thread
{
public:
    virtual ex::result_t run () 
    {
        count = 0;

        while (1)
        {
            ++count;
            if ( count >= 9000000 )
            {
                printf ("hello world in thread_a\n");
                count = 0;
            }
        }
    }
    int count;
}; // end class CThread_a

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Thread, normal, off )
{
    CThread_a thread_a;
    thread_a.start();

    int count = 0;
    ex::result_t eResult = ex::EResult::failed;
    while ( eResult != ex::EResult::ok )
    {
        ++count;
        eResult = thread_a.join(1000);
        if ( count > 2 )
            eResult = thread_a.kill();
    }
}
