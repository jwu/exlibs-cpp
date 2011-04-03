// ======================================================================================
// File         : allocator_helpers.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:28:47 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ALLOCATOR_HELPERS_H_1281767329
#define ALLOCATOR_HELPERS_H_1281767329
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "meta/typeop.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// struct AllocatorHelper 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename CAllocator_T >
struct AllocatorHelper
{
    //
    AllocatorHelper()
    {
        // assert the CAllocator_T must public from Allocator.
        ex_static_assert( (EX_IS_SUPERSUB_CLASS( Allocator, CAllocator_T ) || typeop::IsSameType<CAllocator_T,NullType>::Result), "CAllocator_T must inherits from Allocator" );
    }
}; // end AllocatorHelper


///////////////////////////////////////////////////////////////////////////////
// class Managed 
// 
// Purpose: 
//  useage e.g. Managed<Allocator_sys>::TAllocator
// 
///////////////////////////////////////////////////////////////////////////////

template < typename CAllocator_T >
struct Managed : public AllocatorHelper<CAllocator_T>
{
    // typedefs
    typedef Managed<CAllocator_T> self_t;
    typedef AllocatorHelper<CAllocator_T> base_t;
    typedef size_t sz_t;

    // real interface
    template < typename T >
    struct TAllocator
    {
        // new,delete
        INLINE static T* New() { return ex_new_use(EX_GP(CAllocator_T)) T; }
        INLINE static void Delete( T* _p ) { ex_delete_use( _p, EX_GP(CAllocator_T) ); }

        // new,delete array
        INLINE static T* NewArray( sz_t _count ) { return ex_new_array_use( T, _count, EX_GP(CAllocator_T) ); }
        INLINE static void DeleteArray( T* _p ) { ex_delete_array_use( _p, EX_GP(CAllocator_T) ); }

        // malloc,realloc,free
        INLINE static T* Malloc( sz_t _count ) { return (T*)ex_malloc_use( _count*sizeof(T), EX_GP(CAllocator_T) ); }
        INLINE static T* Realloc( T* _p, sz_t _count ) { return (T*)ex_realloc_use( _p, _count*sizeof(T), EX_GP(CAllocator_T) ); }
        INLINE static void Free( T* _p ) { ex_free_use( _p, EX_GP(CAllocator_T) ); }
    }; // end struct TAllocator
}; // end struct Managed

///////////////////////////////////////////////////////////////////////////////
// class NoManaged
// 
// Purpose: 
//  useage e.g. NoManaged<Allocator_sys>::TAllocator
//
///////////////////////////////////////////////////////////////////////////////

template < typename CAllocator_T >
struct NoManaged : public AllocatorHelper<CAllocator_T>
{
    // typedefs
    typedef NoManaged<CAllocator_T> self_t;
    typedef AllocatorHelper<CAllocator_T> base_t;
    typedef size_t sz_t;

    // real interface
    template < typename T >
    struct TAllocator
    {
        // new,delete
        INLINE static T* New() { return ex_new_nomng(EX_GP(CAllocator_T)) T; }
        INLINE static void Delete( T* _p ) { ex_delete_nomng( _p, EX_GP(CAllocator_T) ); }

        // new,delete array
        INLINE static T* NewArray( sz_t _count ) { return ex_new_array_nomng( T, _count, EX_GP(CAllocator_T) ); }
        INLINE static void DeleteArray( T* _p ) { ex_delete_array_nomng( _p, EX_GP(CAllocator_T) ); }

        // malloc,realloc,free
        INLINE static T* Malloc( sz_t _count ) { return (T*)ex_malloc_nomng( _count*sizeof(T), EX_GP(CAllocator_T) ); }
        INLINE static T* Realloc( T* _p, sz_t _count ) { return (T*)ex_realloc_nomng( _p, _count*sizeof(T), EX_GP(CAllocator_T) ); }
        INLINE static void Free( T* _p ) { ex_free_nomng( _p, EX_GP(CAllocator_T) ); }
    }; // end struct TAllocator
}; // end struct NoManaged

///////////////////////////////////////////////////////////////////////////////
// specific Allocator_sys for NoManaged
///////////////////////////////////////////////////////////////////////////////

template <>
struct NoManaged<NullType> : public AllocatorHelper<NullType>
{
    // typedefs
    typedef NoManaged<NullType> self_t;
    typedef AllocatorHelper<NullType> base_t;
    typedef size_t sz_t;

    // real interface
    template < typename T >
    struct TAllocator
    {
        // new,delete
        INLINE static T* New() { return new T; }
        INLINE static void Delete( T* _p ) { delete _p; }

        // new,delete array
        INLINE static T* NewArray( sz_t _count ) { return new T[_count]; }
        INLINE static void DeleteArray( T* _p ) { delete [] _p; }

        // malloc,realloc,free
        INLINE static T* Malloc( sz_t _count ) { return (T*)::malloc( sizeof(T) * _count ); }
        INLINE static T* Realloc( T* _p, sz_t _count ) { return (T*)::realloc( _p, _count*sizeof(T) ); }
        INLINE static void Free( T* _p ) { ::free(_p); }
    }; // end struct TAllocator
}; // end struct NoManaged


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ALLOCATOR_HELPERS_H_1281767329
// #################################################################################
