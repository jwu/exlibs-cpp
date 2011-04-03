// ======================================================================================
// File         : Allocator_dl283.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:19:50 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ALLOCATOR_DL283_H_1250525993
#define ALLOCATOR_DL283_H_1250525993
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "Allocator.h"
#include "pattern/singleton_macro.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Allocator_dl283 
// 
// Purpose: use Doug Lea's malloc 2.8.3 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Allocator_dl283 : public Allocator
{
    ///////////////////////////////////////////////////////////////////////////////
    // singleton decl
    ///////////////////////////////////////////////////////////////////////////////

    EX_DECL_SINGLETON ( Allocator_dl283 );

public:

    Allocator_dl283();
    virtual ~Allocator_dl283();

public:
    //
    virtual void* alloc( size_t _size );
    virtual void* allocAligned( size_t _size, uint _alignment );
    virtual void* realloc( void* _ptr, size_t _new_size );
    virtual void* reallocAligned( void* _ptr, size_t _new_size, uint _alignment );
    virtual void  free( void* _ptr );

}; // end class Allocator_dl283 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ALLOCATOR_DL283_H_1250525993
// #################################################################################
