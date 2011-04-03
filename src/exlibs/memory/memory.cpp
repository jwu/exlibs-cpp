// ======================================================================================
// File         : Memory.cpp
// Author       : Wu Jie 
// Last Change  : 10/19/2008 | 21:58:48 PM | Sunday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "MemMng.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// private defines 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private {
// #########################

    ///////////////////////////////////////////////////////////////////////////////
    // malloc 
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: Malloc
    // ------------------------------------------------------------------

    void* Malloc( size_t _size, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line, EMemop::Enum _memopType )
    {
        return EX_GP(MemMng)->alloc( _size, _pAllocator, _tag, _file_name, _function_name, _line, _memopType );
    }

    // ------------------------------------------------------------------
    // Desc: MallocNomange
    // ------------------------------------------------------------------

    void* MallocNomng( size_t _size, Allocator* _pAllocator ) 
    {
        return _pAllocator->alloc(_size); 
    }

    ///////////////////////////////////////////////////////////////////////////////
    // realloc 
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: Realloc
    // ------------------------------------------------------------------

    void* Realloc( void* _ptr, size_t _size, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line, EMemop::Enum _memopType )
    {
        return EX_GP(MemMng)->realloc( _ptr, _size, _pAllocator, _tag, _file_name, _function_name, _line, _memopType );
    }

    // ------------------------------------------------------------------
    // Desc: ReallocNomng
    // ------------------------------------------------------------------

    void* ReallocNomng( void* _ptr, size_t _size, Allocator* _pAllocator )
    {
        return _pAllocator->realloc( _ptr, _size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // free 
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: free 
    // ------------------------------------------------------------------

    void free( void* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line, EMemop::Enum _memopType )
    {
        EX_GP(MemMng)->free( _ptr, _pAllocator, _file_name, _function_name, _line, _memopType  );
    }

    // ------------------------------------------------------------------
    // Desc: FreeNomng 
    // ------------------------------------------------------------------

    void FreeNomng( void* _ptr, Allocator* _pAllocator )
    {
        _pAllocator->free(_ptr);
    }

    // ------------------------------------------------------------------
    // Desc: StackMalloc
    // ------------------------------------------------------------------

    void* StackMalloc( size_t _size )
    {
        return EX_GP(StackAllocator)->alloc(_size);
    }

    // ------------------------------------------------------------------
    // Desc: StackFree
    // ------------------------------------------------------------------

    void StackFree( size_t _size )
    {
        EX_GP(StackAllocator)->free(_size);
    }

// #########################
} // end namespace _private
// #########################

// #########################
} // end namespace ex 
// #########################

///////////////////////////////////////////////////////////////////////////////
// global defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: placement new debug
// ------------------------------------------------------------------

void* operator new( size_t _size, ex::Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line )
{
    // the code format is come from effective c++ rule-8
    if ( _size == 0 )
    {
        _size = 1;
    }
    while(1)
    {
        // get the allocate result pointer
        void* ptr = NULL;
        ptr = EX_GP(ex::MemMng)->alloc( _size, _pAllocator, _tag, _file_name, _function_name, _line, ex::EMemop::cpp_new );

        // check the result pointer if ok return it,
        if (ptr)
            return ptr;

        // TODO: change std methon and std exception to my own one
        // if failed allocate memory find current error handle function
        std::new_handler global_handler = std::set_new_handler(0);
        std::set_new_handler(global_handler);

        if( global_handler ) (*global_handler)();
        else printf("out of memory\n");
        // TODO: use throw or printf???
        //else                 throw std::bad_alloc();   
    }
}

// ------------------------------------------------------------------
// Desc: placement new nomanage
// ------------------------------------------------------------------

void* operator new( size_t _size, ex::Allocator* _pAllocator )
{
    // the code format is come from effective c++ rule-8
    if ( _size == 0 )
    {
        _size = 1;
    }
    while(1)
    {
        // get the allocate result pointer
        void* ptr = NULL;
        if( _pAllocator )
            ptr = _pAllocator->alloc( _size );
        else
            ptr = ::operator new (_size);

        // check the result pointer if ok return it,
        if (ptr)
            return ptr;

        // TODO: change std methon and std exception to my own one
        // if failed allocate memory find current error handle function
        std::new_handler global_handler = std::set_new_handler(0);
        std::set_new_handler(global_handler);

        if( global_handler ) (*global_handler)();
        else printf("out of memory\n");
        // TODO: use throw or printf???
        //else                 throw std::bad_alloc();   
    }
}

