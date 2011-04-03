// ======================================================================================
// File         : SmartPtr.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:22:10 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SMARTPTR_H_1250526133
#define SMARTPTR_H_1250526133
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "SmartPtr_helpers.h"

///////////////////////////////////////////////////////////////////////////////
// temp helper macros 
///////////////////////////////////////////////////////////////////////////////

// other template
#define TEMPLATE_OTHER_DECL template < typename OTHER_T, \
                                       template <class> class TOwnerShip_OTHER_T, \
                                       void (*OTHER_PFN) ( void* ) >
#define TEMPLATE_OTHER_SMART_PTR SmartPtr< OTHER_T, TOwnerShip_OTHER_T, OTHER_PFN >

// compare template
#define TEMPLATE_COMPARE_DECL template < typename T, \
                                         template <class> class TOwnerShip_T, \
                                         void (*PFN) ( void* ), \
                                         typename U >
#define TEMPLATE_SMART_PTR SmartPtr< T, TOwnerShip_T, PFN >

// #########################
namespace ex { 
// #########################

// fwd-decl
template < typename T, template <class> class TOwnerShip_T > class WeakPtr;

// dummy function, nothing to do.
namespace _private { INLINE void default_delete ( void* _ptr ) { (void)_ptr; } }

///////////////////////////////////////////////////////////////////////////////
// class SmartPtr 
// 
// Purpose: 
//  swap nor only swap count, also release the old smart ptr by destroy temp smart_ptr
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T,
           template <class> class TOwnerShip_T = RefCounted, 
           void (*PFN) ( void* ) = _private::default_delete
           > 
class SmartPtr : public TOwnerShip_T<T>
{
    template < typename U,
               template <class> class TOwnerShip_U > friend class WeakPtr;

    ///////////////////////////////////////////////////////////////////////////////
    // member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T*  m_pPointee;

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef T* ptr_t;
    typedef const T* const_ptr_t;
    typedef ptr_t& ptr_ref_t; // T* &
    typedef const ptr_t& const_ptr_ref_t; // T* const &, not miss understand as const T* const &
    typedef T& ref_t;
    typedef const T& const_ref_t;
    typedef SmartPtr< T, TOwnerShip_T, PFN > self_t;
    typedef TOwnerShip_T<T> owner_ship_t;
    typedef typename typeop::Select<owner_ship_t::DestructiveCopy, self_t, const self_t >::result_t copy_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    SmartPtr()
        : m_pPointee (NULL)
    {
        ConstructStaticAsserts();
    }

    // 
    // NOTE: some times, we need to set const pointer * into the smart pointer ( for example: this pointer in a const function )
    //       at this situation, just set const_cast<ptr_t>(_const_ptr) in it. 
    explicit SmartPtr( ptr_t _ptr ) 
        : m_pPointee (_ptr)
    {
        ConstructStaticAsserts();
    }

    //
    SmartPtr( copy_t& _copy ) 
        : owner_ship_t(_copy),
          m_pPointee(NULL)
    {
        ConstructStaticAsserts();
        m_pPointee = owner_ship_t::clone( _copy.ptr_ref() );
    }

    // const other-copy
    TEMPLATE_OTHER_DECL
    SmartPtr( const TEMPLATE_OTHER_SMART_PTR& _other )
        : owner_ship_t( _other ) 
    { 
        ConstructStaticAsserts();
        m_pPointee = owner_ship_t::clone( _other.ptr_ref() ); 
    }

    // non-const other-copy
    TEMPLATE_OTHER_DECL
    SmartPtr( TEMPLATE_OTHER_SMART_PTR& _other )
        : owner_ship_t( _other ) 
    { 
        ConstructStaticAsserts();
        m_pPointee = owner_ship_t::clone( _other.ptr_ref() ); 
    }

    // const weak-ptr copy
    SmartPtr( const WeakPtr<T,TOwnerShip_T>& _weakPtr )
        : owner_ship_t( _weakPtr ) 
    {
        ConstructStaticAsserts();
        m_pPointee = owner_ship_t::clone( _weakPtr.ptr_ref() );
    }

    // weak-ptr copy
    SmartPtr( WeakPtr<T,TOwnerShip_T>& _weakPtr )
        : owner_ship_t( _weakPtr ) 
    {
        ConstructStaticAsserts();
        m_pPointee = owner_ship_t::clone( _weakPtr.ptr_ref() );
    }

    // operator = 
    SmartPtr& operator = ( copy_t& _copy )
    {
        SmartPtr temp(_copy);
        temp.swap(*this);
        return *this;
    }

    // operator = const-other 
    TEMPLATE_OTHER_DECL
    SmartPtr& operator = ( const TEMPLATE_OTHER_SMART_PTR& _other )
    {
        SmartPtr temp(_other);
        temp.swap(*this);
        return *this;
    }

    // operator = non-const-other
    TEMPLATE_OTHER_DECL
    SmartPtr& operator = ( TEMPLATE_OTHER_SMART_PTR& _other )
    {
        SmartPtr temp(_other);
        temp.swap(*this);
        return *this;
    }

    // operator = weak-ptr
    SmartPtr& operator = ( WeakPtr<T,TOwnerShip_T>& _weakPtr )
    {
        SmartPtr temp(_weakPtr);
        temp.swap(*this);
        return *this;
    }

    // operator = const weak-ptr
    SmartPtr& operator = ( const WeakPtr<T,TOwnerShip_T>& _weakPtr )
    {
        SmartPtr temp(_weakPtr);
        temp.swap(*this);
        return *this;
    }

    //
    void swap( self_t& _rhs )
    {
        ex::value_swap( m_pPointee, _rhs.m_pPointee );
        owner_ship_t::swap(_rhs);
    }

    //
    ~SmartPtr()
    {
        if ( owner_ship_t::release( (*this).ptr_ref() ) )
        {
            if ( m_pPointee ) // NOTE: we don't delete empty pointer, and exec callback function
            { 
                // if the PFN we give is default_delete, use ex_delete. 
                // NOTE: ex_delete can't delete void*, that's whay we can't wrap it in default_delete directly.
                if ( PFN == _private::default_delete ) 
                    ex_delete(m_pPointee);
                else  // if we have callback function, use it to handle pointer delete.
                    (*PFN) ( m_pPointee ); 
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // def-ref methods
    ///////////////////////////////////////////////////////////////////////////////

    // some times we need to call ~SmartPtr manually, use this instead of sp.~SmartPtr() which will lead to unref release problem
    // m_release == Manual Release / Release Manually
    INLINE void m_release()
    {
        (*this) = self_t();
    }

    //
    ptr_t operator -> ()
    {
        return m_pPointee;
    }

    const_ptr_t operator -> () const
    {
        return m_pPointee;
    }

    // NOTE: the static_cast can only detect if they are inherits relationship, but it doesn't know if down-cast valid
    template < typename CAST_T > CAST_T* cast () { return static_cast<CAST_T*> (m_pPointee); }
    template < typename CAST_T > const CAST_T* cast () const { return static_cast<const CAST_T*> (m_pPointee); }

    // get ptr
    INLINE ptr_t ptr() { return m_pPointee; }
    INLINE const_ptr_t ptr() const { return m_pPointee; }

    // get ptr_ref
    INLINE ptr_ref_t ptr_ref() { return m_pPointee; }
    INLINE const_ptr_ref_t ptr_ref() const { return m_pPointee; }

    ///////////////////////////////////////////////////////////////////////////////
    // compare functions
    ///////////////////////////////////////////////////////////////////////////////

    // Enables "if (!sp) ..."
    bool operator ! () const { return m_pPointee == NULL; }

    // compare with smart-ptr

    // operator ==
    TEMPLATE_OTHER_DECL
    INLINE bool operator == ( const TEMPLATE_OTHER_SMART_PTR& _rhs ) const { return (*this).ptr() == _rhs.ptr(); }

    // operator !=
    TEMPLATE_OTHER_DECL
    INLINE bool operator != ( const TEMPLATE_OTHER_SMART_PTR& _rhs ) const { return !( (*this).ptr() == _rhs.ptr() ); }

    // operator <
    TEMPLATE_OTHER_DECL
    INLINE bool operator < ( const TEMPLATE_OTHER_SMART_PTR& _rhs ) const { return (*this).ptr() < _rhs.ptr(); }

    // operator >
    TEMPLATE_OTHER_DECL
    INLINE bool operator > ( const TEMPLATE_OTHER_SMART_PTR& _rhs ) { return ( _rhs.ptr() < (*this).ptr() ); }

    // operator <=
    TEMPLATE_OTHER_DECL
    INLINE bool operator <= ( const TEMPLATE_OTHER_SMART_PTR& _rhs ) { return !( _rhs.ptr() < (*this).ptr() ); }

    // operator >=
    TEMPLATE_OTHER_DECL
    INLINE bool operator >= ( const TEMPLATE_OTHER_SMART_PTR& _rhs ) { return !( (*this).ptr() < _rhs.ptr() ); }

    // compare with weak-ptr

    // operator ==
    INLINE bool operator == ( const WeakPtr<T,TOwnerShip_T>& _rhs ) const { return (*this).ptr() == _rhs.ptr(); }

    // operator !=
    INLINE bool operator != ( const WeakPtr<T,TOwnerShip_T>& _rhs ) const { return !( (*this).ptr() == _rhs.ptr() ); }

    // operator <
    INLINE bool operator < ( const WeakPtr<T,TOwnerShip_T>& _rhs ) const { return (*this).ptr() < _rhs.ptr(); }

    // operator >
    INLINE bool operator > ( const WeakPtr<T,TOwnerShip_T>& _rhs ) { return ( _rhs.ptr() < (*this).ptr() ); }

    // operator <=
    INLINE bool operator <= ( const WeakPtr<T,TOwnerShip_T>& _rhs ) { return !( _rhs.ptr() < (*this).ptr() ); }

    // operator >=
    INLINE bool operator >= ( const WeakPtr<T,TOwnerShip_T>& _rhs ) { return !( (*this).ptr() < _rhs.ptr() ); }

private:
    // Helper for enabling 'if (sp)'
    struct SpToBool
    {
        SpToBool(int) {}
        void ValidPtr() {}
    }; // end strcut SpToBool
    typedef void (SpToBool::*sp_to_bool_t)();

public:
    // enable 'if (sp)'
    operator sp_to_bool_t () const { return !((*this).ptr()) ? NULL : &SpToBool::ValidPtr; }

private:
    // Helper for disallowing automatic conversion
    struct DisallowSpToPtr
    {
        DisallowSpToPtr(ptr_t) {}
    }; // 

public:        
    operator DisallowSpToPtr() const { return (*this).ptr(); }

    ///////////////////////////////////////////////////////////////////////////////
    // private member functions 
    ///////////////////////////////////////////////////////////////////////////////

private:

    //
    INLINE void ConstructStaticAsserts()
    {
        ex_static_assert( EX_IS_SUPERSUB_CLASS( OwnerShipHelper<T>, TOwnerShip_T<T> ), "TOwnerShip_T must inherits from OwnerShipHelper" );
    }

    // disable dereference
    ref_t operator*()
    {
        ex_static_assert( false, "Not allow use dereference" );
        ex_warning ( "dereference is not allowed" );
        return *this;
    }

    const_ref_t operator*() const
    {
        ex_static_assert( false, "Not allow use dereference" );
        ex_warning ( "dereference is not allowed" );
        return *this;
    }

}; // end class SmartPtr

///////////////////////////////////////////////////////////////////////////////
// free comparison operators for class template SmartPtr
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: sp == p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator == ( const TEMPLATE_SMART_PTR& _sp, U* _p ) { return _sp.ptr() == _p; }

// ------------------------------------------------------------------
// Desc: p == sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator == ( U* _p, const TEMPLATE_SMART_PTR& _sp ) { return _sp.ptr() == _p; }

// ------------------------------------------------------------------
// Desc: sp != p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator != ( const TEMPLATE_SMART_PTR& _sp, U* _p ) { return !( _sp.ptr() == _p ); }
    
// ------------------------------------------------------------------
// Desc: p != sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator != ( U* _p, const TEMPLATE_SMART_PTR& _sp ) { return _sp.ptr() != _p; }

// ------------------------------------------------------------------
// Desc: sp < p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator < ( const TEMPLATE_SMART_PTR& _sp, U* _p ) { return _sp.ptr() < _p; }

// ------------------------------------------------------------------
// Desc: p < sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator < ( U* _p, const TEMPLATE_SMART_PTR& _sp ) { return _sp.ptr() < _p; }

// ------------------------------------------------------------------
// Desc: sp > p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator > ( const TEMPLATE_SMART_PTR& _sp, U* _p ) { return _p < _sp.ptr(); } 

// ------------------------------------------------------------------
// Desc: p > sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator > ( U* _p, const TEMPLATE_SMART_PTR& _sp ) { return _sp.ptr() < _p; }
  
// ------------------------------------------------------------------
// Desc: sp <= p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
inline bool operator <= ( const TEMPLATE_SMART_PTR& _sp, U* _p ) { return !( _p < _sp.ptr() ); }
        
// ------------------------------------------------------------------
// Desc: operator<= for _lhs = raw pointer, _rhs = SmartPtr
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator <= ( U* _p, const TEMPLATE_SMART_PTR& _sp ) { return !( _sp.ptr() < _p ); }

// ------------------------------------------------------------------
// Desc: sp >= p 
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator >= ( const TEMPLATE_SMART_PTR& _sp, U* _p ) { return !( _sp.ptr() < _p ); }
        
// ------------------------------------------------------------------
// Desc: p >= sp 
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator>=( U* _p, const TEMPLATE_SMART_PTR& _sp ) { return !( _p < _sp.ptr() ); }

#if 0
////////////////////////////////////////////////////////////////////////////////
///  specialization of std::less for SmartPtr
///  \ingroup SmartPointerGroup
////////////////////////////////////////////////////////////////////////////////

namespace std
{
    template
    <
        typename T,
        template <class> class OP,
        class CP,
        template <class> class KP,
        template <class> class SP,
        template <class> class CNP
    >
    struct less< Loki::SmartPtr<T, OP, CP, KP, SP, CNP > >
        : public binary_function<Loki::SmartPtr<T, OP, CP, KP, SP, CNP >,
            Loki::SmartPtr<T, OP, CP, KP, SP, CNP >, bool>
    {
        bool operator()(const Loki::SmartPtr<T, OP, CP, KP, SP, CNP >& _lhs,
            const Loki::SmartPtr<T, OP, CP, KP, SP, CNP >& _rhs) const
        { return less<T*>()(GetImpl(_lhs), GetImpl(_rhs)); }
    };
}
#endif

// #########################
} // end namespace ex 
// #########################

///////////////////////////////////////////////////////////////////////////////
// undef temp macros 
///////////////////////////////////////////////////////////////////////////////

#undef TEMPLATE_OTHER_DECL
#undef TEMPLATE_OTHER_SMART_PTR
#undef TEMPLATE_COMPARE_DECL
#undef TEMPLATE_SMART_PTR

// #################################################################################
#endif // END SMARTPTR_H_1250526133
// #################################################################################

