// ======================================================================================
// File         : ContainerAllocator.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:13:48 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CONTAINERALLOCATOR_H_1250525608
#define CONTAINERALLOCATOR_H_1250525608
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class ContainerAllocator
// 
// Purpose: the default std-allocator in exUtility
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, template < class > class TAllocator_T >
class ContainerAllocator : public std::allocator<T>
{
public:
    typedef std::allocator<T>                       base_t;
    typedef ContainerAllocator<T, TAllocator_T>    self_t;

    typedef typename base_t::value_type             value_t;
    typedef typename base_t::pointer                ptr_t;
    typedef typename base_t::const_pointer          const_ptr_t;
    typedef typename base_t::reference              ref_t;
    typedef typename base_t::const_reference        const_ref_t;
    typedef typename base_t::size_type              sz_t;
    typedef typename base_t::difference_type        diff_t;

public:
    template < class OTHER_T >
    struct rebind
    {
		// convert an allocator<T> to an allocator <OTHER_T>
        typedef ContainerAllocator<OTHER_T,TAllocator_T> other; 
    }; // end struct rebind

public:
    // construct default allocator (do nothing)
    ContainerAllocator()
    {	
    }

    // construct by copying (do nothing)
    ContainerAllocator( const self_t& )
    {
    }

    // construct from a related allocator (do nothing)
    template< class OTHER_T >
    ContainerAllocator( const ContainerAllocator<OTHER_T,TAllocator_T>& )
    {	
    }

    // assign from a related allocator (do nothing)
    template< class OTHER_T >
    self_t& operator = ( const ContainerAllocator<OTHER_T,TAllocator_T>& )
    {
        return (*this);
    }

    // return address of mutable _val
    ptr_t address( ref_t _val ) const 
    {
        return (&_val); 
    }

    // return address of nonmutable _val
    const_ptr_t address( const_ref_t _val ) const 
    {
        return (&_val); 
    }

    // deallocate object at _ptr, ignore size
    void deallocate( ptr_t _ptr, sz_t )
    {	
        TAllocator_T<T>::Free(_ptr); 
    }

    // allocate array of _count elements
    ptr_t allocate( sz_t _count )
    {	
        return TAllocator_T<T>::Malloc(_count);
    }

    // allocate array of _count elements, ignore hint
    ptr_t allocate( sz_t _count, const void * )
    {	
        return TAllocator_T<T>::Malloc(_count);
    }

    // not in the std::allocator
    ptr_t reallocate( ptr_t _ptr, sz_t _new_count )
    {
        return TAllocator_T<T>::Realloc( _ptr, _new_count );
    }

    // construct object at _ptr with value _val
    void construct( ptr_t _ptr, const T& _val )
    {	
        std::_Construct(_ptr, _val);
    }

    // destroy object at _ptr
    void destroy( ptr_t _ptr )
    {	
        std::_Destroy(_ptr);
    }

    // estimate maximum array size
    sz_t max_size() const
    {	
        sz_t count = (sz_t)(-1) / sizeof (T);
        return (0 < count ? count : 1);
    }
}; // end class ContainerAllocator

///////////////////////////////////////////////////////////////////////////////
// class ContainerAllocator< T, NullType > 
// 
// Purpose: for default allocator, we use default stl alloca memory
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class ContainerAllocator< T, NoManaged<NullType>::TAllocator > : public std::allocator<T>
{
public:
    typedef std::allocator<T>                           base_t;
    typedef ContainerAllocator<T,NoManaged<NullType>::TAllocator>            self_t;

    typedef typename base_t::value_type                 value_t;
    typedef typename base_t::pointer                    ptr_t;
    typedef typename base_t::const_pointer              const_ptr_t;
    typedef typename base_t::reference                  ref_t;
    typedef typename base_t::const_reference            const_ref_t;
    typedef typename base_t::size_type                  sz_t;
    typedef typename base_t::difference_type            diff_t;

public:
    template < class OTHER_T >
    struct rebind
    {
        typedef ContainerAllocator<OTHER_T,NoManaged<NullType>::TAllocator> other; 
    }; // end struct rebind

public:
    // construct default allocator (do nothing)
    ContainerAllocator()
    {	
    }

    // construct by copying (do nothing)
    ContainerAllocator( const self_t& )
    {
    }

    // construct from a related allocator (do nothing)
    template<class OTHER_T>
    ContainerAllocator( const ContainerAllocator<OTHER_T,NoManaged<NullType>::TAllocator>& )
    {	
    }

    // assign from a related allocator (do nothing)
    template<class OTHER_T>
    self_t& operator = ( const ContainerAllocator<OTHER_T,NoManaged<NullType>::TAllocator>& )
    {
        return (*this);
    }

    // return address of mutable _val
    ptr_t address(ref_t _val) const 
    {
        return (&_val); 
    }

    // return address of nonmutable _val
    const_ptr_t address(const_ref_t _val) const 
    {
        return (&_val); 
    }

    // deallocate object at _ptr, ignore size
    void deallocate( ptr_t _ptr, sz_t _dummy )
    {	
        base_t::deallocate( _ptr, _dummy );
    }

    // allocate array of _count elements
    ptr_t allocate( sz_t _count )
    {	
        return base_t::allocate(_count);
    }

    // allocate array of _count elements, ignore hint
    ptr_t allocate( sz_t _count, const void * )
    {	
        return base_t::allocate(_count);
    }

    // not in the std::allocator
    ptr_t reallocate( ptr_t _ptr, sz_t _new_count ) 
    {
        ptr_t pData = base_t::allocate(_new_count); 
        if ( _ptr )
        {
            memcpy( pData, _ptr, _new_count );
            base_t::deallocate( _ptr, 0/*a dummy value*/ ); 
        }
        return pData;
    }

    // construct object at _ptr with value _val
    void construct( ptr_t _ptr, const T& _val )
    {	
        base_t::construct(_ptr,_val);
    }

    // destroy object at _ptr
    void destroy( ptr_t _ptr )
    {	
        base_t::destroy(_ptr);
    }

    // estimate maximum array size
    sz_t max_size() const
    {	
        sz_t count = (sz_t)(-1) / sizeof (T);
        return (0 < count ? count : 1);
    }
}; // end class ContainerAllocator<T,NoManaged<NullType>::TAllocator > 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END CONTAINERALLOCATOR_H_1250525608
// #################################################################################
