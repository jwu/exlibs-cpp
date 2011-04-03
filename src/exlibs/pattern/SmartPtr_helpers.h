// ======================================================================================
// File         : SmartPtr_helpers.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 10:56:06 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SMARTPTR_HELPERS_H_1281840972
#define SMARTPTR_HELPERS_H_1281840972
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// struct OwnerShipHelper 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct OwnerShipHelper
{
    //
    OwnerShipHelper()
    {
    }
}; // end SManagedPolicy

///////////////////////////////////////////////////////////////////////////////
// class RefCounted 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class RefCounted : public OwnerShipHelper<T> 
{
public:
    typedef RefCounted<T> self_t;
    typedef T*             ptr_t;
    typedef const T*       const_ptr_t;

    //
    enum { DestructiveCopy = false };

    ///////////////////////////////////////////////////////////////////////////////
    // member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    RefCounted() 
        : m_pCount(NULL)
    {
        m_pCount = ex_new uint32(0);
        ex_assert( m_pCount, "m_pCount not allocated" );
        *m_pCount = 1;
    }

    //
    RefCounted( const self_t& _copy ) 
        : m_pCount(_copy.m_pCount)
    {}
    
    // MWCW lacks template friends, hence the following kludge
    template < typename OTHER_T >
    RefCounted( const RefCounted<OTHER_T>& _rhs ) 
        : m_pCount( reinterpret_cast<const self_t&>(_rhs).m_pCount )
    {
    }

    //
    INLINE ptr_t clone( const ptr_t& _ptr )
    {
        ++(*m_pCount);
        return _ptr;
    }

    //
    INLINE bool release( const ptr_t& _ptr )
    {
        --(*m_pCount);
        if ( *m_pCount == 0 )
        {
            ex_delete (m_pCount);
            m_pCount = NULL;
            return true;
        }
        return false;
    }

    //
    INLINE void swap( self_t& _rhs ) { ex::value_swap( m_pCount, _rhs.m_pCount ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string += to_str<FLAGS>(*m_pCount); 
        return string;
    }


    ///////////////////////////////////////////////////////////////////////////////
    // protected member function 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    INLINE uint32 count ( const ptr_t& _ptr ) const 
    { 
        EX_UNUSED(_ptr);
        return *m_pCount; 
    }

    //
    void incRef () { ++(*m_pCount); }
    void decRef () { --(*m_pCount); }

    ///////////////////////////////////////////////////////////////////////////////
    // member data 
    ///////////////////////////////////////////////////////////////////////////////

private:

    uint32* m_pCount;

}; // end class RefCounted 

///////////////////////////////////////////////////////////////////////////////
// class COMRefCounted 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class COMRefCounted : public OwnerShipHelper<T>
{
public:
    typedef COMRefCounted<T> self_t;
    typedef T*                ptr_t;
    typedef const T*          const_ptr_t;

    //
    enum { DestructiveCopy = false };

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    COMRefCounted()
    {
    }

    //
    template <class OTHER_T>
    COMRefCounted( const COMRefCounted<OTHER_T>& ) {}

    //
    static ptr_t clone( const ptr_t& _ptr )
    {
        if( _ptr != NULL )
            _ptr->AddRef();
        return _ptr;
    }

    //
    static bool release( const ptr_t& _ptr )
    { 
        if( _ptr != NULL ) 
            _ptr->release(); 
        return false; 
    }

    //
    static void swap( self_t& ) {}

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string += "no information";
        return string;
    }

}; // end class COMRefCounted

///////////////////////////////////////////////////////////////////////////////
// class SelfRefCounted 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class SelfRefCounted : public OwnerShipHelper<T>
{
public:
    typedef SelfRefCounted<T> self_t;
    typedef T*                ptr_t;
    typedef const T*          const_ptr_t;

    //
    enum { DestructiveCopy = false };

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    SelfRefCounted()
    {
    }

    //
    template <class OTHER_T>
    SelfRefCounted( const SelfRefCounted<OTHER_T>& ) {}

    //
    static ptr_t clone( const ptr_t& _ptr )
    {
        if( _ptr != NULL )
            _ptr->incRef();
        return _ptr;
    }

    //
    static bool release( const ptr_t& _ptr )
    { 
        if( _ptr != NULL ) 
        {
            _ptr->decRef(); 
            if ( _ptr->RefCount () == 0 )
            {
                return true;
            }
        }
        return false; 
    }

    //
    static void swap( self_t& ) {}

    ///////////////////////////////////////////////////////////////////////////////
    // protected member
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    INLINE uint32 count ( const ptr_t& _ptr ) const { return _ptr->RefCount(); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string += "no information";
        return string;
    }

}; // end class SelfRefCounted

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END SMARTPTR_HELPERS_H_1281840972
// #################################################################################
