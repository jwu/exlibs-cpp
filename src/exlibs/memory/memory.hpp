// ======================================================================================
// File         : memory.hpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 09:34:29 AM | Sunday,August
// Description  : 
// ======================================================================================

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
    // new 
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: NewArrayNomng 
    // ------------------------------------------------------------------

    template < typename T >
        T* NewArrayNomng ( size_t _count, Allocator* _pAllocator )
        {
            if ( EX_IS_SUPERSUB_CLASS( Memop, T) )
            {
                return new T[_count];
            }
            else
            {
                // We must keep the length of the array in front of the array in order
                // to call all destructor when we delete the array (because on the delete call, we don't have the length
                // anymore, unless we store it). This is what c++ does.
                // We'll also need the alig
                uint32 objAlignment = alignof<T>();
                uint32 placeholderSize = 3*sizeof(uint32);
                if( objAlignment > sizeof(uint32) )
                    placeholderSize = EX_ALIGN_ROUND ( objAlignment, placeholderSize );

                // 
                void* pData = NULL;
                pData = ex::_private::MallocNomng( _count*sizeof(T)+placeholderSize, _pAllocator ); 

                ex_assert( pData, "out of memory!" );
                T* pArray = EX_ADD_PTR( T*, pData, placeholderSize );

                // Validate that types requiring special alignment are allocated properly.
                ex_assert( ( EX_PTR_TO_ADDR(pArray) % objAlignment ) == 0, "the address not aligned" );

                // Store some information needed to be able to call destructors properly
                uint32* pHeader = ((uint32*)pArray) - 3;
                pHeader[0] = (uint32)_count;
                pHeader[1] = sizeof(T);
                pHeader[2] = placeholderSize;

                for( uint i = 0; i < _count; ++i )
                    ex_new_in(&pArray[i]) T;

                return (T*)pArray;
            }
        }

    // ------------------------------------------------------------------
    // Desc: NewArray 
    // ------------------------------------------------------------------

    template < typename T >
        T* NewArray ( size_t _count, Allocator* _pAllocator, const char* _tag, const char* _file_name, const char* _function_name, size_t _line )
        {
            if ( EX_IS_SUPERSUB_CLASS( Memop , T) )
            {
                return new T[_count];
            }
            else
            {


                // We must keep the length of the array in front of the array in order
                // to call all destructor when we delete the array (because on the delete call, we don't have the length
                // anymore, unless we store it). This is what c++ does.
                // We'll also need the alig
                uint32 objAlignment = alignof<T>();
                uint32 placeholderSize = 3*sizeof(uint32);
                if( objAlignment > sizeof(uint32) )
                    placeholderSize = EX_ALIGN_ROUND ( objAlignment, placeholderSize );

                // 
                void* pData = ex::_private::Malloc( _count*sizeof(T)+placeholderSize, _pAllocator, _tag, _file_name, _function_name, _line, ex::EMemop::cpp_new_array ); 

                ex_assert( pData, "out of memory!" );
                T* pArray = EX_ADD_PTR( T*, pData, placeholderSize );

                // Validate that types requiring special alignment are allocated properly.
                ex_assert( ( EX_PTR_TO_ADDR(pArray) % objAlignment ) == 0, "" );

                // Store some information needed to be able to call destructors properly
                uint32* pHeader = ((uint32*)pArray) - 3;
                pHeader[0] = (uint32)_count;
                pHeader[1] = sizeof(T);
                pHeader[2] = placeholderSize;

                for( uint i = 0; i < _count; ++i )
                    ex_new_in(&pArray[i]) T;

                return (T*)pArray;
            }
        }

    ///////////////////////////////////////////////////////////////////////////////
    // delete 
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: Delete
    // ------------------------------------------------------------------

    template <typename T>
        void Delete( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line )
        {
            ex_static_assert( !(typeop::IsSameType<T,void>::Result), "T can not be void" );
            if( _ptr )
            {
                if ( EX_IS_SUPERSUB_CLASS( Memop, T) )
                    delete _ptr;
                else
                {
                    _ptr->~T();
                    ex::_private::free( _ptr, _pAllocator, _file_name, _function_name, _line, ex::EMemop::cpp_delete ); 
                }
            }
        }

    // ------------------------------------------------------------------
    // Desc: DeleteNomng
    // ------------------------------------------------------------------

    template <typename T>
        void DeleteNomng( T* _ptr, Allocator* _pAllocator )
        {

            ex_static_assert( !(typeop::IsSameType<T,void>::Result), "T can not be void" );
            if( _ptr )
            {
                if ( EX_IS_SUPERSUB_CLASS( Memop, T) )
                    delete _ptr;
                else
                {
                    _ptr->~T();
                    ex::_private::FreeNomng( _ptr, _pAllocator ); 
                }
            }
        }

    // ------------------------------------------------------------------
    // Desc: DeleteArray
    // ------------------------------------------------------------------

    template < typename T >
        void DeleteArray( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line )
        {
            ex_static_assert( !(typeop::IsSameType<T,void>::Result), "T Can Not Be void" );

            if( _ptr )
            {
                if ( EX_IS_SUPERSUB_CLASS( Memop , T) )
                {
                    delete [] _ptr;
                }
                else
                {
                    // Obtain previously stored information to be able
                    // to call destructors properly on all elements
                    uint32* pHeader = ((uint32*)_ptr) - 3;
                    const uint32 objCount          = pHeader[0];
                    const uint32 objSize           = pHeader[1]; 
                    const uint32 placeholderSize   = pHeader[2];

                    // Call the destructor for each object in the array, from back to front
                    // note, for ->~ because of virtual destructor
                    uintptr_t arrayAddr = EX_PTR_TO_ADDR(_ptr);
                    uintptr_t objAddr = arrayAddr + ( objCount * objSize );
                    while( objAddr != arrayAddr )
                    {
                        objAddr -= objSize;

                        T* pObject = (T*) EX_ADDR_TO_PTR(objAddr);
                        pObject->~T();
                    }

                    //
                    _ptr = EX_SUB_PTR(T*, _ptr, placeholderSize);
                    ex::_private::free( _ptr, _pAllocator, _file_name, _function_name, _line, ex::EMemop::cpp_delete_array ); 
                }
            }
        }

    // ------------------------------------------------------------------
    // Desc: DeleteArrayNomng
    // ------------------------------------------------------------------

    template < typename T >
        void DeleteArrayNomng( T* _ptr, Allocator* _pAllocator )
        {
            ex_static_assert( !(typeop::IsSameType<T,void>::Result), "T can not be void" );

            if( _ptr )
            {
                if ( EX_IS_SUPERSUB_CLASS( Memop , T) )
                {
                    delete [] _ptr;
                }
                else
                {
                    // Obtain previously stored information to be able
                    // to call destructors properly on all elements
                    uint32* pHeader = ((uint32*)_ptr) - 3;
                    const uint32 objCount          = pHeader[0];
                    const uint32 objSize           = pHeader[1]; 
                    const uint32 placeholderSize   = pHeader[2];

                    // Call the destructor for each object in the array, from back to front
                    // note, for ->~ because of virtual destructor
                    uintptr_t arrayAddr = EX_PTR_TO_ADDR(_ptr);
                    uintptr_t objAddr = arrayAddr + ( objCount * objSize );
                    while( objAddr != arrayAddr )
                    {
                        objAddr -= objSize;

                        T* pObject = (T*) EX_ADDR_TO_PTR(objAddr);
                        pObject->~T();
                    }

                    //
                    _ptr = EX_SUB_PTR(T*, _ptr, placeholderSize);
                    ex::_private::FreeNomng( _ptr, _pAllocator ); 
                }
            }
        }

    // ------------------------------------------------------------------
    // Desc: CallDestructor
    // ------------------------------------------------------------------

    template<class T> INLINE void CallDestructor( T* _ptr ) { _ptr->~T(); }

// #########################
} // end namespace _private
// #########################

// ######################### 
namespace mem { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// common memory operations 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: set
// ------------------------------------------------------------------

INLINE void* set( void* _ptr, int _pattern, size_t _size )
{
    return ::memset(_ptr, _pattern, _size);
}

// ------------------------------------------------------------------
// Desc: zero
// ------------------------------------------------------------------

INLINE void* zero( void* _ptr, size_t _size )
{
    return ex::mem::set( _ptr, 0x00, _size );
}

// ------------------------------------------------------------------
// Desc: memcpy
// ------------------------------------------------------------------

INLINE void* cpy( void* _p_to, const void* _p_from, size_t _size )
{
    return ::memcpy( _p_to, _p_from, _size );
}

// ------------------------------------------------------------------
// Desc: memmove
// ------------------------------------------------------------------

INLINE void* move( void* _p_to, const void* _p_from, size_t _size )
{
    return ::memmove( _p_to, _p_from, _size );
}

// ------------------------------------------------------------------
// Desc: mem swap
// ------------------------------------------------------------------

INLINE void swap( void* _p1, void* _p2, size_t _size )
{
    void* pTmp = ex_stack_malloc(EX_ALIGN_ROUND(_size,EX_DEFAULT_ALIGNMENT));

    ex::mem::cpy( pTmp, _p1,  _size );
    ex::mem::cpy( _p1,  _p2,  _size );
    ex::mem::cpy( _p2,  pTmp, _size );
}

// ######################### 
} // end namespace mem 
// ######################### 


// ------------------------------------------------------------------
// Desc: value swap
// ------------------------------------------------------------------

template < class T > INLINE void value_swap( T& _a, T& _b )
{
    T tmp = _a;
    _a = _b;
    _b = tmp;
}

// ------------------------------------------------------------------
// Desc: list item swap
// ------------------------------------------------------------------

template < class T > INLINE void list_swap( T _list[], int _idx1, int _idx2 )
{
    T tmp = _list[_idx1];
    _list[_idx1] = _list[_idx2];
    _list[_idx2] = _list[_idx1];
}

// #########################
} // end namespace ex 
// #########################
