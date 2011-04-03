// ======================================================================================
// File         : MemMng.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:11 AM | Saturday,September
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

TEST( MemMng, alloc, off )
{
    const int BUFFER_SIZE = 5;
    const int MAX_COUNT = 256;

    ClassProbe* pBuffer = ex_new_array( ClassProbe, BUFFER_SIZE );
    for ( int i = 0; i < MAX_COUNT; ++i )
    {
        char* pTestBuffer = (char*)ex_malloc( sizeof(char)*BUFFER_SIZE ); 
        ex_free(pTestBuffer);
    }
    ex_delete_array(pBuffer);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( MemMng, leak, off )
{
    const int MAX_COUNT = 2;
    char* pTestBuffer = NULL;
    for ( int i = 0; i < MAX_COUNT; ++i )
    {
        pTestBuffer = (char*)ex_malloc( sizeof(char) ); 
    }
}
