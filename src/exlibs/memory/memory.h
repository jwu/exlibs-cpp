// ======================================================================================
// File         : memory.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 10:27:30 AM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMORY_H_1250524250
#define MEMORY_H_1250524250
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "StackAllocator.h"

// #########################
namespace ex {
// #########################

///////////////////////////////////////////////////////////////////////////////
// private function declarations
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private {
// #########################

    ///////////////////////////////////////////////////////////////////////////////
    // for malloc 
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // Malloc
    // ========================================================

    EX_LIBS_DLL void* Malloc( size_t _size, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line, EMemop::Enum _memopType );

    // ========================================================
    // MallocNomng
    // ========================================================

    EX_LIBS_DLL void* MallocNomng( size_t _size, Allocator* _pAllocator );

    ///////////////////////////////////////////////////////////////////////////////
    // for realloc 
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // Realloc
    // ========================================================

    EX_LIBS_DLL void* Realloc( void* _ptr, size_t _size, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line, EMemop::Enum _memopType );

    // ========================================================
    // ReallocNomng
    // ========================================================

    EX_LIBS_DLL void* ReallocNomng( void* _ptr, size_t _size, Allocator* _pAllocator );

    ///////////////////////////////////////////////////////////////////////////////
    // for free 
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // free
    // ========================================================

    EX_LIBS_DLL void free( void* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line, EMemop::Enum _memopType );

    // ========================================================
    // FreeNomng
    // ========================================================

    EX_LIBS_DLL void FreeNomng( void* _ptr, Allocator* _pAllocator );

    ///////////////////////////////////////////////////////////////////////////////
    // for new array 
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // NewArray
    // ========================================================

    template <typename T> INLINE T* NewArray( size_t _count, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line );

    // ========================================================
    // NewArrayNomng
    // ========================================================

    template <typename T> INLINE T* NewArrayNomng ( size_t _count, Allocator* _pAllocator );

    ///////////////////////////////////////////////////////////////////////////////
    // for delete 
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // Delete
    // ========================================================

    template <typename T> INLINE void Delete( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line );

    // ========================================================
    // DeleteNomng
    // ========================================================

    template <typename T> INLINE void DeleteNomng( T* _ptr, Allocator* _pAllocator );

    // ========================================================
    // DeleteArray
    // ========================================================

    template <typename T> INLINE void DeleteArray( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line );

    // ========================================================
    // DeleteArrayNomng
    // ========================================================

    template <typename T> INLINE void DeleteArrayNomng( T* _ptr, Allocator* _pAllocator );

    ///////////////////////////////////////////////////////////////////////////////
    // for placement delete
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // CallDestructor
    // ========================================================

    template<class T> INLINE void CallDestructor( T* _ptr );

    ///////////////////////////////////////////////////////////////////////////////
    // for stack malloc & free 
    ///////////////////////////////////////////////////////////////////////////////

    // ========================================================
    // StackMalloc
    // ========================================================

    EX_LIBS_DLL void* StackMalloc( size_t _size );

    // ========================================================
    // StackFree
    // ========================================================

    EX_LIBS_DLL void StackFree( size_t _size );

    ///////////////////////////////////////////////////////////////////////////////
    // class StackMarker 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class StackMarker
    {
    public:
        StackMarker( size_t _size )
            : size(_size)
        {
        }

        ~StackMarker()
        {
            ex::_private::StackFree(size);
        }

        size_t  size;
    }; // end class StackMarker

// #########################
} // end namespace _private
// #########################

// ######################### 
namespace mem { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// common memory operations 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// memset
// ========================================================

INLINE void* set( void* _ptr, int _pattern, size_t _size );

// ========================================================
// memzero
// ========================================================

INLINE void* zero( void* _ptr, size_t _size );

// ========================================================
// memcpy
// ========================================================

INLINE void* cpy( void* _p_to, const void* _p_from, size_t _size );

// ========================================================
// memmove
// ========================================================

INLINE void* move( void* _p_to, const void* _p_from, size_t _size );

// ========================================================
// mem swap
// ========================================================

INLINE void swap( void* _p1, void* _p2, size_t _size );

// ######################### 
} // end namespace mem 
// ######################### 


// ========================================================
// value swap
// ========================================================

template < class T > INLINE void value_swap( T& _a, T& _b );

// ========================================================
// list item swap
// ========================================================

template < class T > INLINE void list_swap( T _list[], int _idx1, int _idx2 );

// #########################
} // end namespace ex
// #########################

///////////////////////////////////////////////////////////////////////////////
// global namespace function declaration & define 
///////////////////////////////////////////////////////////////////////////////

// -----------------------------------
#if EX_USE_SYSTEM_MEMORY
// -----------------------------------

    // malloc
    #define ex_malloc_nomng( size, p_allocator )                            malloc(size)
    #define ex_malloc( size )                                               malloc(size)
    #define ex_malloc_use( size, p_allocator )                              malloc(size)
    #define ex_malloc_tag( size, tag )                                      malloc(size)
    #define ex_malloc_tag_use( size, p_allocator, tag )                     malloc(size)

    // realloc
    #define ex_realloc_nomng( ptr, size, p_allocator )                      realloc(ptr,size)
    #define ex_realloc( ptr, size )                                         realloc(ptr,size)
    #define ex_realloc_use( ptr, size, p_allocator )                        realloc(ptr,size)
    #define ex_realloc_tag( ptr, size, tag )                                realloc(ptr,size)
    #define ex_realloc_tag_use( ptr, size, p_allocator, tag )               realloc(ptr,size)

    // free
    #define ex_free_nomng( ptr, p_allocator )                               free(ptr)
    #define ex_free( ptr )                                                  free(ptr)
    #define ex_free_use( ptr, p_allocator )                                 free(ptr)

    // new
    #define ex_new_nomng( p_allocator )                                     new
    #define ex_new                                                          new
    #define ex_new_use( p_allocator )                                       new
    #define ex_new_tag( tag )                                               new
    #define ex_new_tag_use( p_allocator, tag )                              new

    // new array
    #define ex_new_array_nomng( class_name, count, p_allocator )            new class_name[count]
    #define ex_new_array( class_name, count )                               new class_name[count]
    #define ex_new_array_use( class_name, count, p_allocator )              new class_name[count]
    #define ex_new_array_tag( class_name, count, tag )                      new class_name[count]
    #define ex_new_array_tag_use( class_name, count, p_allocator, tag )     new class_name[count]
    
    // delete
    #define ex_delete_nomng( ptr, p_allocator )                             delete ptr
    #define ex_delete( ptr )                                                delete ptr
    #define ex_delete_use( ptr, p_allocator )                               delete ptr

    // delete array
    #define ex_delete_array_nomng( ptr, p_allocator )                       delete [] ptr
    #define ex_delete_array( ptr )                                          delete [] ptr
    #define ex_delete_array_use( ptr, p_allocator )                         delete [] ptr

// -----------------------------------
#else // use managed memory
// -----------------------------------

///////////////////////////////////////////////////////////////////////////////
// malloc
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// ex_malloc_... 
// ========================================================

#define ex_malloc_nomng( size, p_allocator )                ::ex::_private::MallocNomng( size, p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_malloc( size )                               ::ex::_private::Malloc( size, EX_GP(EX_ALLOCATOR), "Default", __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_malloc )
    #define ex_malloc_use( size, p_allocator )              ::ex::_private::Malloc( size, p_allocator, "Default", __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_malloc )
    #define ex_malloc_tag( size, tag )                      ::ex::_private::Malloc( size, EX_GP(EX_ALLOCATOR), tag, __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_malloc ) 
    #define ex_malloc_tag_use( size, p_allocator, tag )     ::ex::_private::Malloc( size, p_allocator, tag, __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_malloc )         
#else
    #define ex_malloc( size )                               ex_malloc_nomng( size, EX_GP(EX_ALLOCATOR) )
    #define ex_malloc_use( size, p_allocator )              ex_malloc_nomng( size, p_allocator )
    #define ex_malloc_tag( size, tag )                      ex_malloc_nomng( size, EX_GP(EX_ALLOCATOR) )
    #define ex_malloc_tag_use( size, p_allocator, tag )     ex_malloc_nomng( size, p_allocator )
#endif

///////////////////////////////////////////////////////////////////////////////
// realloc
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// if use default allocator, set allocator = NULL (ex_malloc(size,NULL))
// ========================================================

#define ex_realloc_nomng( ptr, size, p_allocator )              ::ex::_private::ReallocNomng( ptr, size, p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_realloc( ptr, size )                             ::ex::_private::Realloc( ptr, size, EX_GP(EX_ALLOCATOR), "Default", __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_realloc )
    #define ex_realloc_use( ptr, size, p_allocator )            ::ex::_private::Realloc( ptr, size, p_allocator, "Default", __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_realloc )
    #define ex_realloc_tag( ptr, size, tag )                    ::ex::_private::Realloc( ptr, size, EX_GP(EX_ALLOCATOR), tag, __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_realloc )
    #define ex_realloc_tag_use( ptr, size, p_allocator, tag )   ::ex::_private::Realloc( ptr, size, p_allocator, tag, __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_realloc )
#else
    #define ex_realloc( ptr, size )                             ex_realloc_nomng( ptr, size, EX_GP(EX_ALLOCATOR) )
    #define ex_realloc_use( ptr, size, p_allocator )            ex_realloc_nomng( ptr, size, p_allocator )
    #define ex_realloc_tag( ptr, size, tag )                    ex_realloc_nomng( ptr, size, EX_GP(EX_ALLOCATOR) ) 
    #define ex_realloc_tag_use( ptr, size, p_allocator, tag )   ex_realloc_nomng( ptr, size, p_allocator )         
#endif


///////////////////////////////////////////////////////////////////////////////
// free
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// free
// ========================================================

#define ex_free_nomng( ptr, p_allocator )                   ::ex::_private::FreeNomng( ptr, p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_free( ptr )                                  ::ex::_private::free( ptr, NULL, __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_free )
    #define ex_free_use( ptr, p_allocator )                 ::ex::_private::free( ptr, p_allocator, __FILE__, __FUNCTION__, __LINE__, ::ex::EMemop::c_free )
#else
    #define ex_free( ptr )                                  ex_free_nomng( ptr, EX_GP(EX_ALLOCATOR) )
    #define ex_free_use( ptr, p_allocator )                 ex_free_nomng( ptr, p_allocator )
#endif

// ======================================================== 
// safe free 
// ======================================================== 

// ex_safe_free_nomng
#define ex_safe_free_nomng( ptr, p_allocator ) \
    if ( ptr ) { \
        ex_free_nomng(ptr,p_allocator); \
        ptr = NULL; \
    }

// ex_safe_free
#define ex_safe_free( ptr ) \
    if ( ptr ) { \
        ex_free(ptr); \
        ptr = NULL; \
    }

// ex_safe_free_use
#define ex_safe_free_use( ptr, p_allocator ) \
    if ( ptr ) { \
        ex_free_use(ptr); \
        ptr = NULL; \
    }

///////////////////////////////////////////////////////////////////////////////
// new
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// new
// ========================================================

#define ex_new_nomng(p_allocator)               new( p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_new                              new( EX_GP(EX_ALLOCATOR), "Default", __FILE__, __FUNCTION__, __LINE__ )
    #define ex_new_use(p_allocator)             new( p_allocator, "Default", __FILE__, __FUNCTION__, __LINE__ )
    #define ex_new_tag( tag )                   new( EX_GP(EX_ALLOCATOR), tag, __FILE__, __FUNCTION__, __LINE__ )
    #define ex_new_tag_use( p_allocator, tag )  new( p_allocator, tag, __FILE__, __FUNCTION__, __LINE__ )
#else
    #define ex_new                              ex_new_nomng( EX_GP(EX_ALLOCATOR) )
    #define ex_new_use(p_allocator)             ex_new_nomng( p_allocator )
    #define ex_new_tag( tag )                   ex_new_nomng( EX_GP(EX_ALLOCATOR) ) 
    #define ex_new_tag_use( p_allocator, tag )  ex_new_nomng( p_allocator )         
#endif

// ========================================================
// From the C++ Standard, Sectionn 3.7.3.1 paragraph 1:
//      An allocation function shall be a class member function or a global function; 
//      a program is ill-formed if an allocation function is declared in a namespace scope other than the global scope or declared static in global scope.
// This is why we don't put operator new/delete into namesapce _private
// ========================================================


// manage ver.
EX_LIBS_DLL void* operator new ( size_t _size, ex::Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line );
// nomanage ver.
EX_LIBS_DLL void* operator new ( size_t _size, ex::Allocator* _pAllocator );


// ========================================================
// new array
// ========================================================

#define ex_new_array_nomng( class_name, count, p_allocator )            ::ex::_private::NewArrayNomng<class_name>( count, p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_new_array( class_name, count )                           ::ex::_private::NewArray<class_name>( count, EX_GP(EX_ALLOCATOR), "Default", __FILE__, __FUNCTION__, __LINE__ )
    #define ex_new_array_use( class_name, count, p_allocator )          ::ex::_private::NewArray<class_name>( count, p_allocator, "Default", __FILE__, __FUNCTION__, __LINE__ )
    #define ex_new_array_tag( class_name, count, tag )                  ::ex::_private::NewArray<class_name>( count, EX_GP(EX_ALLOCATOR), tag, __FILE__, __FUNCTION__, __LINE__ )
    #define ex_new_array_tag_use( class_name, count, p_allocator, tag ) ::ex::_private::NewArray<class_name>( count, p_allocator, tag, __FILE__, __FUNCTION__, __LINE__ )
#else
    #define ex_new_array( class_name, count )                           ex_new_array_nomng( class_name, count, EX_GP(EX_ALLOCATOR) )
    #define ex_new_array_use( class_name, count, p_allocator )          ex_new_array_nomng( class_name, count, p_allocator )
    #define ex_new_array_tag( class_name, count, tag )                  ex_new_array_nomng( class_name, count, EX_GP(EX_ALLOCATOR) ) 
    #define ex_new_array_tag_use( class_name, count, p_allocator, tag ) ex_new_array_nomng( class_name, count, p_allocator )         
#endif


///////////////////////////////////////////////////////////////////////////////
// delete
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// dummy delete
// ========================================================

// DUMMY: this is dummy function { 
INLINE void operator delete ( void* _ptr, ex::Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line ) {}
INLINE void operator delete ( void* _ptr, ex::Allocator* _pAllocator ) {}
// } DUMMY end 

// ========================================================
// delete
// ========================================================

#define ex_delete_nomng( ptr, p_allocator )             ::ex::_private::DeleteNomng( ptr, p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_delete( ptr )                            ::ex::_private::Delete( ptr, NULL, __FILE__, __FUNCTION__, __LINE__ )
    #define ex_delete_use( ptr, p_allocator )           ::ex::_private::Delete( ptr, p_allocator, __FILE__, __FUNCTION__, __LINE__ )
#else
    #define ex_delete( ptr )                            ex_delete_nomng( ptr, EX_GP(EX_ALLOCATOR) )
    #define ex_delete_use( ptr, p_allocator )           ex_delete_nomng( ptr, p_allocator )
#endif

// ========================================================
// delete array
// ========================================================

#define ex_delete_array_nomng( ptr, p_allocator )           ::ex::_private::DeleteArrayNomng( ptr, p_allocator )

#if EX_USE_MEMORY_MANAGER
    #define ex_delete_array( ptr )                          ::ex::_private::DeleteArray( ptr, NULL, __FILE__, __FUNCTION__, __LINE__ )
    #define ex_delete_array_use( ptr, p_allocator )         ::ex::_private::DeleteArray( ptr, p_allocator, __FILE__, __FUNCTION__, __LINE__ )
#else
    #define ex_delete_array( ptr )                          ex_delete_array_nomng( ptr, EX_GP(EX_ALLOCATOR) )
    #define ex_delete_array_use( ptr, p_allocator )         ex_delete_array_nomng( ptr, p_allocator )
#endif

// ======================================================== 
// safe delete 
// ======================================================== 

// ex_safe_delete_nomng
#define ex_safe_delete_nomng( ptr, p_allocator ) \
    if ( ptr ) { \
        ex_delete_nomng(ptr,p_allocator); \
        ptr = NULL; \
    }

// ex_safe_delete
#define ex_safe_delete( ptr ) \
    if ( ptr ) { \
        ex_delete(ptr); \
        ptr = NULL; \
    }

// ex_safe_delete_use
#define ex_safe_delete_use( ptr, p_allocator ) \
    if ( ptr ) { \
        ex_delete_use(ptr,p_allocator); \
        ptr = NULL; \
    }

// ex_safe_delete_array_nomng
#define ex_safe_delete_array_nomng( ptr, p_allocator ) \
    if ( ptr ) { \
        ex_delete_array_nomng(ptr,p_allocator); \
        ptr = NULL; \
    }

// ex_safe_delete_array
#define ex_safe_delete_array( ptr ) \
    if ( ptr ) { \
        ex_delete_array(ptr); \
        ptr = NULL; \
    }

// ex_safe_delete_array_use
#define ex_safe_delete_array_use( ptr, p_allocator ) \
    if ( ptr ) { \
        ex_delete_array_use(ptr,p_allocator); \
        ptr = NULL; \
    }

// -----------------------------------
#endif // end if EX_USE_SYSTEM_MEMORY
// -----------------------------------

///////////////////////////////////////////////////////////////////////////////
// placement new
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// placement new
// ========================================================

#define ex_new_in(p_address)                new(p_address)
#define ex_new_at(p_address,idx)            new(p_address,idx)

///////////////////////////////////////////////////////////////////////////////
// placement delete
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// placement delete
// ========================================================

#define ex_delete_in(p_address)             ::ex::_private::CallDestructor(p_address)

///////////////////////////////////////////////////////////////////////////////
// stack malloc
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// stack malloc
// ========================================================

#define ex_stack_malloc(size)               ::ex::_private::StackMalloc(size); ::ex::_private::StackMarker(size)

///////////////////////////////////////////////////////////////////////////////
//  Implement
///////////////////////////////////////////////////////////////////////////////

#include "memory.hpp"

// #################################################################################
#endif // END MEMORY_H_1250524250
// #################################################################################
