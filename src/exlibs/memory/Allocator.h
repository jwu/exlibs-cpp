// ======================================================================================
// File         : Allocator.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:19:40 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ALLOCATOR_H_1250525983
#define ALLOCATOR_H_1250525983
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Allocator 
// 
// Purpose: the abstract Allocator class
// 
///////////////////////////////////////////////////////////////////////////////

class Allocator
{
public:
    //
    virtual void* alloc( size_t _size ) = 0;
    virtual void* allocAligned( size_t _size, uint _alignment ) = 0;
    virtual void* realloc( void* _ptr, size_t _new_size ) = 0;
    virtual void* reallocAligned( void* _ptr, size_t _new_size, uint _alignment ) = 0;
    virtual void  free( void* _ptr ) = 0;

protected:
    Allocator() {}
    virtual ~Allocator() {}

}; // end class Allocator

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ALLOCATOR_H_1250525983
// #################################################################################
