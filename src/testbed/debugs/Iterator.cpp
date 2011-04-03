// ======================================================================================
// File         : iterator.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:26 AM | Saturday,September
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

TEST( iterator, erase, off )
{
    // Array
    ex::printf( "Array\n" );
    ex::Array<int> array;
    array.push_back( 1 );
    array.push_back( 2 );
    array.push_back( 3 );
    array.push_back( 4 );
    array.push_back( 5 );
    for ( ex::Array<int>::iterator iter = array.begin(); iter != array.end(); )
    {
        if ( (*iter) != 3 )
        {
            ex::printf( "erase %d\n", (*iter) );
            iter = array.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    for ( ex::Array<int>::iterator iter = array.begin(); iter != array.end(); iter = array.erase(iter) )
    {
        ex::printf( "erase %d\n", (*iter) );
    }
    ex::printf( "\n" );

    // List
    ex::printf( "List\n" );
    ex::List<int> list;
    list.push_back( 1 );
    list.push_back( 2 );
    list.push_back( 3 );
    list.push_back( 4 );
    list.push_back( 5 );
    for ( ex::List<int>::iterator iter = list.begin(); iter != list.end(); )
    {
        if ( (*iter) != 3 )
        {
            ex::printf( "erase %d\n", (*iter) );
            iter = list.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    for ( ex::List<int>::iterator iter = list.begin(); iter != list.end(); iter = list.erase(iter) )
    {
        ex::printf( "erase %d\n", (*iter) );
    }
    ex::printf( "\n" );

    // Map
    ex::printf( "Map\n" );
    ex::Map<int,int> map;
    map.insert( 1, 1 );
#if 0
    map.insert( 2, 2 );
    map.insert( 3, 3 );
    map.insert( 4, 4 );
    map.insert( 5, 5 );
    for ( ex::Map<int,int>::iterator iter = map.begin(); iter != map.end(); )
    {
        if ( (*iter) != 3 )
        {
            ex::printf( "erase %d\n", (*iter) );
            map.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
    for ( ex::Map<int,int>::iterator iter = map.begin(); iter != map.end(); )
    {
        ex::printf( "erase %d\n", (*iter) );
        map.erase(iter++);
    }
    ex::printf( "\n" );
#endif
}
