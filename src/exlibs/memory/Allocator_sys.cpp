// ======================================================================================
// File         : Allocator_sys.cpp
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 01:10:17 AM | Saturday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Allocator_sys.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// member function defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

Allocator_sys::Allocator_sys()
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

Allocator_sys::~Allocator_sys()
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* Allocator_sys::alloc( size_t _size )
{
    return allocAligned( _size, EX_DEFAULT_ALIGNMENT ); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// TODO: align?
void* Allocator_sys::allocAligned( size_t _size, uint _alignment )
{
    return malloc(_size); 
}


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* Allocator_sys::realloc( void* _ptr, size_t _new_size )
{
    return reallocAligned( _ptr, _new_size, EX_DEFAULT_ALIGNMENT ); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// TODO: align?
void* Allocator_sys::reallocAligned( void* _ptr, size_t _new_size, uint _alignment )
{
    return realloc( _ptr, _new_size ); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void Allocator_sys::free( void* _ptr )
{
    free(_ptr); 
}

// #########################
} // end namespace ex 
// #########################

