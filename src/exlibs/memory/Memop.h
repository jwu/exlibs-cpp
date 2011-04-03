// ======================================================================================
// File         : Memop.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:20:24 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMOP_H_1250526026
#define MEMOP_H_1250526026
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Memop
// 
// Purpose: 
//  Customize the memory method by yourself in rewriting all the member functions.
//  The default one is obey the system memory allocate/deallocate rules.
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Memop
{
public:
    //
    INLINE void* operator new ( size_t _size )
    {
        return malloc(_size);
    }

    //
    INLINE void* operator new ( size_t _size, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line )
    {
        return malloc(_size);
    }

    //
    INLINE void* operator new [] ( size_t _size )
    {
        return malloc(_size);
    }

    //
    INLINE void* operator new [] ( size_t _size, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line )
    {
        return malloc(_size);
    }

    //
    INLINE void* operator new ( size_t _size, Allocator* _pAllocator )
    {
        return malloc(_size);
    }

    //
    INLINE void* operator new [] ( size_t _size, Allocator* _pAllocator )
    {
        return malloc(_size);
    }

    //
    INLINE void operator delete ( void* _ptr )
    {
        free(_ptr);
    }

    //
    INLINE void operator delete [] ( void* _ptr )
    {
        free(_ptr);
    }

    // { these are dummy functions
    INLINE void operator delete ( void* _ptr, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line ) {}
    INLINE void operator delete [] ( void* _ptr, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line ) {}

    INLINE void operator delete ( void* _ptr, Allocator* _pAllocator ) {}
    INLINE void operator delete [] ( void* _ptr, Allocator* _pAllocator ) {}
    // }
}; // end class Memop

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END MEMOP_H_1250526026
// #################################################################################
