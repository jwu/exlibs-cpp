// ======================================================================================
// File         : singleton.cpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 00:40:42 AM | Sunday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Singleton.h"

// #########################
namespace ex { 
// #########################

// #########################
namespace _private { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// defines 
///////////////////////////////////////////////////////////////////////////////

//
lifetime_tracker_list_t* g_pLifetimeTrackerList = NULL;

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void OnSingletonDestroy () 
{
    ex_assert( g_pLifetimeTrackerList && !g_pLifetimeTrackerList->empty(), "g_pLifetimeTrackerList not created or is empty" );

    // Pick the element at the top of the stack
    LifetimeTracker* pTop =  g_pLifetimeTrackerList->back(); 

    // remove that object off the stack _before_ deleting pTop
    g_pLifetimeTrackerList->pop_back();

    // destroy the element
    delete pTop;

    // destroy stack when it's emtpy _after_ deleting pTop
    if ( g_pLifetimeTrackerList->empty() )
    {
        delete g_pLifetimeTrackerList;
        g_pLifetimeTrackerList = NULL;
    }
}

// #########################
} // end namespace _private 
// #########################


// #########################
} // end namespace ex 
// #########################

