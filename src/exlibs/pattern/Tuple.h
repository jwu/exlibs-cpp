// ======================================================================================
// File         : Tuple.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:22:22 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TUPLE_H_1250526147
#define TUPLE_H_1250526147
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "Tuple_helpers.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// forward decl
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: Cons forward declaration
// ------------------------------------------------------------------ 

template < class HT, class TT > struct Cons;

// ------------------------------------------------------------------ 
// Desc: Tuple 
// ------------------------------------------------------------------ 

template < class T0 = NullType, class T1 = NullType, class T2 = NullType,
           class T3 = NullType, class T4 = NullType, class T5 = NullType,
           class T6 = NullType, class T7 = NullType, class T8 = NullType,
           class T9 = NullType > class Tuple;

///////////////////////////////////////////////////////////////////////////////
// _private helper functions and classes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: ConstNullType 
// ------------------------------------------------------------------ 

INLINE const NullType ConstNullType () { return NullType(); }

// ------------------------------------------------------------------ 
// Desc: generate error template, referencing to non-existing members 
//       of this template is used to produce compilation errors 
//       intentionally
// ------------------------------------------------------------------ 

template<class T> class GenerateError;

///////////////////////////////////////////////////////////////////////////////
// class GetClass 
// 
// Purpose: Cons getters 
//          called: GetClass<N>::get<RETURN_TYPE>(aTuple)
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// general
// ======================================================== 

template< int N >
struct GetClass 
{
    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template<class RET, class HT, class TT >
    INLINE static RET get ( const Cons<HT, TT>& t ) { return GetClass<N-1>::template get<RET>(t.Tail); }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template<class RET, class HT, class TT >
    INLINE static RET get ( Cons<HT, TT>& t ) { return GetClass<N-1>::template get<RET>(t.Tail); }

}; // end class GetClass

// ======================================================== 
// special 0 
// ======================================================== 

template<>
struct GetClass<0> 
{
    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template<class RET, class HT, class TT>
    INLINE static RET get(const Cons<HT, TT>& t) { return t.Head; }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template<class RET, class HT, class TT>
    INLINE static RET get(Cons<HT, TT>& t) { return t.Head; }

}; // end class GetClass<0>

///////////////////////////////////////////////////////////////////////////////
// class ElementImpl 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// ElementImpl
// ======================================================== 

template<int N, class T, bool isConst>
struct ElementImpl
{
private:
    typedef typename T::tail_t next_t;
public:
    typedef typename ElementImpl<N-1, next_t, isConst>::type_t type_t;
}; // end struct ElementImpl 

// ======================================================== 
// ElementImpl
// ======================================================== 

template<int N, class T>
struct ElementImpl<N, T, true /* isConst */>
{
private:
    typedef typename T::tail_t next_t;
public:
    typedef const typename ElementImpl<N-1, next_t, true>::type_t type_t;
}; // end struct ElementImpl

// ======================================================== 
// ElementImpl<0, T, false>
// ======================================================== 

template<class T>
struct ElementImpl<0, T, false /* isConst */>
{
    typedef typename T::head_t type_t;
}; // end struct ElementImpl

// ======================================================== 
// ElementImpl<0, T, true>
// ======================================================== 

template<class T>
struct ElementImpl<0, T, true /* isConst */>
{
    typedef const typename T::head_t type_t;
}; // end struct ElementImpl

#if 1

///////////////////////////////////////////////////////////////////////////////
// class _private::AccessTraits
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <class T> 
struct AccessTraits 
{
    typedef typename TypeTraits<typename TypeTraits<T>::const_t>::reference_t const_t; 
    typedef typename TypeTraits<T>::reference_t non_const_t; 
    typedef typename TypeTraits<typename TypeTraits<typename TypeTraits<T>::non_volatile_t>::const_t>::reference_t parameter_t;

    // NOTE: about const_t
    //       compare with the version below, we don't write the code as: typedef typename TypeTraits< typename TypeTraits<T>::non_const_t >::reference_t non_const_t; 
    //       because the version below it only specialize the <T&>, which means the <const T&> will go into general specialize, and that means
    //       the "typedef T& non_const_t;" for <const T&> will still be const.

    // NOTE: about parameter_t
    //       compare with the version below, we use non_volatile_t instead of unqualified_t, cause the unqualified_t will 
    //       remove the const qualification, and which will lead the TypeTraits go to specialize <type_t&> instead of <const type_t&> 
    //       The version below don't have problem because it have <T&> specialize process, but we don't have here.

}; // end class _private::AccessTraits

#else

///////////////////////////////////////////////////////////////////////////////
// class _private::AccessTraits
// 
// Purpose: 
//  traits classes for get functions
// access traits lifted from detail namespace to be part of the interface,
// (Joel de Guzman's suggestion). Rationale: get functions are part of the
// interface, so should the way to express their return types be.
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// general
// used as the tuple constructors parameter types
// Rationale: non-reference tuple element types can be cv-qualified.
// It should be possible to initialize such types with temporaries,
// and when binding temporaries to references, the reference must
// be non-volatile and const. 8.5.3. (5)
// ======================================================== 

template <class T> struct AccessTraits 
{
    typedef const T& const_t;
    typedef T& non_const_t;
    typedef const typename TypeTraits<T>::unqualified_t& parameter_t;
}; // end struct AccessTraits

// ======================================================== 
// T&
// ======================================================== 

template <class T> struct AccessTraits<T&> 
{
    typedef T& const_t;
    typedef T& non_const_t;
    typedef T& parameter_t;
}; // end struct AccessTraits<T&>

#endif

///////////////////////////////////////////////////////////////////////////////
// class NonStoreableType & WrapNonStoreableType 
// 
// Purpose: 
//  These helper templates wrap void types and plain function types.
//  The reationale is to allow one to write tuple types with those types
//  as elements, even though it is not possible to instantiate such object.
//  E.g: typedef tuple<void> some_type; // ok
//  but: some_type x; // fails
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// NonStoreableType
// ======================================================== 

template <class T> class NonStoreableType
{
    NonStoreableType();
}; // end class NonStoreableType

// ======================================================== 
// WrapNonStoreableType
// ======================================================== 

// WrapNonStoreableType
template <class T> struct WrapNonStoreableType
{
    typedef typename typeop::Select< TypeTraits<T>::isFunction, NonStoreableType<T>, T >::result_t type_t;
}; // end class WrapNonStoreableType

// WrapNonStoreableType<void>
template <> struct WrapNonStoreableType<void> 
{
    typedef NonStoreableType<void> type_t;
}; // end class WrapNonStoreableType

///////////////////////////////////////////////////////////////////////////////
// class SwallowAssign
// 
// Purpose: 
//  Swallows any assignment   (by Doug Gregor)
// 
///////////////////////////////////////////////////////////////////////////////

struct SwallowAssign 
{
    template<typename T> SwallowAssign const& operator = ( const T& ) const { return *this; }
}; // end struct SwallowAssign

// ######################### 
} // end namespace _private 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// namespace tuple functions
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace tuple { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class Element 
// 
// Purpose: typename tuple::Element<N,T>::type_t gets the type_t of the
//          Nth Element ot T, first Element is at index 0
// 
///////////////////////////////////////////////////////////////////////////////

template<int N, class T>
struct Element: public _private::ElementImpl < N, T, TypeTraits<T>::isConst >
{
}; // end class Element  

///////////////////////////////////////////////////////////////////////////////
// class length 
// 
// Purpose: 
//  templates for finding out the length of the tuple
// 
///////////////////////////////////////////////////////////////////////////////

template< class T > struct length { enum { value = 1 + length<typename T::tail_t>::value }; };
template<> struct length< Tuple<> > { enum { value = 0 }; };
template<> struct length< NullType > { enum { value = 0 }; };

///////////////////////////////////////////////////////////////////////////////
// tuple::get
// Usage: get<N>(aTuple)
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: get function for non-const Cons-lists, returns a reference 
//       to the Element
// ------------------------------------------------------------------ 

template <int N, class HT, class TT>
INLINE 
typename _private::AccessTraits< typename Element<N, Cons<HT, TT> >::type_t >::non_const_t
get ( Cons<HT, TT>& _cons ) 
{
    return _private::GetClass<N>::template get<
                                                typename _private::AccessTraits< typename Element<N, Cons<HT, TT> >::type_t >::non_const_t,
                                                HT,
                                                TT
                                               >(_cons);
}

// ------------------------------------------------------------------ 
// Desc: get function for const Cons-lists, returns a const reference 
//       to the Element. If the Element is a reference, returns the 
//       reference as such (that is, can return a non-const reference)
// ------------------------------------------------------------------ 

template <int N, class HT, class TT>
INLINE 
typename _private::AccessTraits< typename Element<N, Cons<HT, TT> >::type_t >::const_t
get ( const Cons<HT, TT>& _cons ) 
{
    return _private::GetClass<N>::template get<
                                                typename _private::AccessTraits< typename Element<N, Cons<HT, TT> >::type_t >::const_t,
                                                HT,
                                                TT 
                                               >(_cons);
}

// ------------------------------------------------------------------ 
// Desc: 
//  "Ignore" allows tuple positions to be ignored when using "tie".
//
// Usage:
//  char c;
//  tie(tuple::Ignore, c) = std::make_pair(1, 'a');
// ------------------------------------------------------------------ 

_private::SwallowAssign const Ignore = _private::SwallowAssign();

// ######################### 
} // end namespace tuple 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// Cons
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class Cons
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <class HT, class TT>
struct Cons 
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef HT head_t;
    typedef TT tail_t;

    typedef typename _private::WrapNonStoreableType<head_t>::type_t stored_head_t;

    ///////////////////////////////////////////////////////////////////////////////
    // members
    ///////////////////////////////////////////////////////////////////////////////

    stored_head_t Head;
    tail_t Tail;

    ///////////////////////////////////////////////////////////////////////////////
    // public functions
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    typename _private::AccessTraits<stored_head_t>::non_const_t
        GetHead() { return Head; }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    typename _private::AccessTraits<tail_t>::non_const_t
        GetTail() { return Tail; }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    typename _private::AccessTraits<stored_head_t>::const_t
        GetHead() const { return Head; }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    typename _private::AccessTraits<tail_t>::const_t
        GetTail() const { return Tail; }

    ///////////////////////////////////////////////////////////////////////////////
    // consturctor & destructor
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Cons() 
        : Head()
        , Tail() 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // the argument for Head is not strictly needed, but it prevents
    // array type_t elements. This is good, since array type_t elements
    // cannot be supported properly in any case (no assignment,
    // copy works only if the tails are exactly the same type_t, ...)
    // ------------------------------------------------------------------ 

    Cons( typename _private::AccessTraits<stored_head_t>::parameter_t _h,
           const tail_t& _t )
        : Head (_h)
        , Tail (_t) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template < class T1, class T2, class T3, class T4, class T5,
               class T6, class T7, class T8, class T9, class T10 >
    Cons( T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6, T7& _t7, T8& _t8, T9& _t9, T10& _t10 )
        : Head (_t1)
        , Tail (_t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10, _private::ConstNullType())
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template < class T2, class T3, class T4, class T5,
               class T6, class T7, class T8, class T9, class T10 >
    Cons( const NullType& /*_t1*/, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6, T7& _t7, T8& _t8, T9& _t9, T10& _t10 )
        : Head ()
        , Tail (_t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10, _private::ConstNullType())
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class HT2, class TT2>
    Cons( const Cons<HT2, TT2>& _copy ) 
        : Head(_copy.Head)
        , Tail(_copy.Tail) 
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // operator =
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class HT2, class TT2>
    Cons& operator = ( const Cons<HT2, TT2>& _u ) 
    {
        Head = _u.Head; 
        Tail = _u.Tail; 
        return *this;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    //  must define assignment operator explicitly, implicit version is
    //  illformed if HT is a reference (12.8. (12))
    // ------------------------------------------------------------------ 

    Cons& operator = (const Cons& _u) 
    {
        Head = _u.Head; 
        Tail = _u.Tail;  
        return *this;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class T1, class T2>
    Cons& operator = ( const std::pair<T1, T2>& _u ) 
    {
        ex_static_assert( tuple::length<Cons>::value == 2, "the output tuple should have 2 type elment" ); // check length = 2
        Head = _u.first; Tail.Head = _u.second; return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // get
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: get member functions (non-const and const)
    // ------------------------------------------------------------------ 

    template <int N>
    typename _private::AccessTraits< typename tuple::Element<N, Cons<HT, TT> >::type_t >::non_const_t
    get () { return tuple::get<N>(*this); } // delegate to non-member get

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <int N>
    typename _private::AccessTraits< typename tuple::Element<N, Cons<HT, TT> >::type_t >::const_t
    get() const { return tuple::get<N>(*this); } // delegate to non-member get

}; // end class Cons

///////////////////////////////////////////////////////////////////////////////
// class Cons<HT, NullType> 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <class HT>
struct Cons <HT, NullType> 
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef HT head_t;
    typedef NullType tail_t;
    typedef Cons<HT, NullType> self_t;

    typedef typename _private::WrapNonStoreableType<head_t>::type_t stored_head_t;

    ///////////////////////////////////////////////////////////////////////////////
    // members
    ///////////////////////////////////////////////////////////////////////////////

    stored_head_t Head;

    ///////////////////////////////////////////////////////////////////////////////
    // public functions
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    typename _private::AccessTraits<stored_head_t>::non_const_t 
        GetHead() { return Head; }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    NullType GetTail() { return NullType(); }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    typename _private::AccessTraits<stored_head_t>::const_t
        GetHead() const { return Head; }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    const NullType GetTail() const { return NullType(); }

    ///////////////////////////////////////////////////////////////////////////////
    // consturctor & destructor
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Cons() 
        : Head() 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Cons( typename _private::AccessTraits<stored_head_t>::parameter_t _h, 
           const NullType& = NullType() )
        : Head (_h) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template<class T1>
    Cons( T1& _t1, 
           const NullType&, const NullType&, const NullType&,
           const NullType&, const NullType&, const NullType&,
           const NullType&, const NullType&, const NullType& )
        : Head (_t1) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Cons( const NullType&,
           const NullType&, const NullType&, const NullType&,
           const NullType&, const NullType&, const NullType&,
           const NullType&, const NullType&, const NullType& )
        : Head () 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class HT2>
    Cons( const Cons<HT2, NullType>& _u ) 
        : Head (_u.Head) 
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // operator =
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class HT2>
    Cons& operator = ( const Cons<HT2, NullType>& _u ) 
    { 
        Head = _u.Head; 
        return *this;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // must define assignment operator explicitely, implicit version
    // is illformed if HT is a reference
    // ------------------------------------------------------------------ 

    Cons& operator = ( const Cons& _u ) 
    { 
        Head = _u.Head; 
        return *this; 
    }

    ///////////////////////////////////////////////////////////////////////////////
    // get
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <int N>
    typename _private::AccessTraits< typename tuple::Element<N, self_t>::type_t >::non_const_t
    get () { return tuple::get<N>(*this); }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <int N>
    typename _private::AccessTraits< typename tuple::Element<N, self_t>::type_t >::const_t
    get () const { return tuple::get<N>(*this); }

}; // end class Cons

///////////////////////////////////////////////////////////////////////////////
// _private helper functions and classes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class MapTupleToCons 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: Tuple to Cons mapper
// ------------------------------------------------------------------ 

template < class T0, class T1, class T2, class T3, class T4,
           class T5, class T6, class T7, class T8, class T9 >
struct MapTupleToCons
{
    typedef Cons < 
                    T0, 
                    typename MapTupleToCons<T1, T2, T3, T4, T5, T6, T7, T8, T9, NullType>::type_t 
                   > type_t;
}; // end struct MapTupleToCons

// ------------------------------------------------------------------ 
// Desc: The empty tuple is a NullType
// ------------------------------------------------------------------ 

template <>
struct MapTupleToCons < NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType >
{
    typedef NullType type_t;
}; // end struct MapTupleToCons 

// ######################### 
} // end namespace _private 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class Tuple
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class Tuple 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < class T0, class T1, class T2, class T3, class T4,
           class T5, class T6, class T7, class T8, class T9 >

class Tuple : public _private::MapTupleToCons<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_t
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef typename _private::MapTupleToCons<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_t base_t;
    typedef typename base_t::head_t head_t;
    typedef typename base_t::tail_t tail_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // NOTE: _private::AccessTraits<T>::parameter_t takes non-reference types as const T&

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple () {}

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple ( typename _private::AccessTraits<T0>::parameter_t _t0 )
        : base_t( _t0, 
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple ( typename _private::AccessTraits<T0>::parameter_t _t0,
             typename _private::AccessTraits<T1>::parameter_t _t1 )
        : base_t( _t0, _t1, 
                  _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2 )
        : base_t( _t0, _t1, _t2, 
                  _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3 )
        : base_t( _t0, _t1, _t2, _t3, 
                  _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3,
            typename _private::AccessTraits<T4>::parameter_t _t4 )
        : base_t( _t0, _t1, _t2, _t3, _t4, 
                  _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3,
            typename _private::AccessTraits<T4>::parameter_t _t4,
            typename _private::AccessTraits<T5>::parameter_t _t5 )
        : base_t( _t0, _t1, _t2, _t3, _t4, _t5, 
                  _private::ConstNullType(), _private::ConstNullType(),
                  _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3,
            typename _private::AccessTraits<T4>::parameter_t _t4,
            typename _private::AccessTraits<T5>::parameter_t _t5,
            typename _private::AccessTraits<T6>::parameter_t _t6 )
        : base_t( _t0, _t1, _t2, _t3, _t4, _t5, _t6, 
                  _private::ConstNullType(), _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3,
            typename _private::AccessTraits<T4>::parameter_t _t4,
            typename _private::AccessTraits<T5>::parameter_t _t5,
            typename _private::AccessTraits<T6>::parameter_t _t6,
            typename _private::AccessTraits<T7>::parameter_t _t7 )
        : base_t( _t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7, 
                  _private::ConstNullType(), _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3,
            typename _private::AccessTraits<T4>::parameter_t _t4,
            typename _private::AccessTraits<T5>::parameter_t _t5,
            typename _private::AccessTraits<T6>::parameter_t _t6,
            typename _private::AccessTraits<T7>::parameter_t _t7,
            typename _private::AccessTraits<T8>::parameter_t _t8 )
        : base_t( _t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, 
                  _private::ConstNullType() ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    Tuple( typename _private::AccessTraits<T0>::parameter_t _t0,
            typename _private::AccessTraits<T1>::parameter_t _t1,
            typename _private::AccessTraits<T2>::parameter_t _t2,
            typename _private::AccessTraits<T3>::parameter_t _t3,
            typename _private::AccessTraits<T4>::parameter_t _t4,
            typename _private::AccessTraits<T5>::parameter_t _t5,
            typename _private::AccessTraits<T6>::parameter_t _t6,
            typename _private::AccessTraits<T7>::parameter_t _t7,
            typename _private::AccessTraits<T8>::parameter_t _t8,
            typename _private::AccessTraits<T9>::parameter_t _t9 )
        : base_t( _t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9 ) 
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template<class U1, class U2>
    Tuple( const Cons<U1, U2>& _p ) 
        : base_t(_p) 
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // operator =
    ///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class U1, class U2>
    Tuple& operator = ( const Cons<U1, U2>& _k ) 
    {
        base_t::operator = (_k);
        return *this;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    template <class U1, class U2>
    Tuple& operator = ( const Pair<U1, U2>& _k ) 
    {
        ex_static_assert( tuple::length<Tuple>::value == 2, "the output tuple should have 2 type elment" ); // check_length = 2
        this->Head = _k.first;
        this->Tail.Head = _k.second;
        return *this;
    }

}; // end class Tuple

///////////////////////////////////////////////////////////////////////////////
// class Tuple
// 
// Purpose: 
//  The empty Tuple
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class Tuple < NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType > : public NullType
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef NullType base_t;

}; // end class Tuple

///////////////////////////////////////////////////////////////////////////////
// _private helper functions and classes
///////////////////////////////////////////////////////////////////////////////


// ######################### 
namespace _private { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class MakeTupleTraits 
// 
// Purpose: 
// The call_traits for make_tuple
// Honours the ReferenceWrapper class.
//
// Must be instantiated with plain or const plain types (not with references)
//
// from template<class T> foo(const T& t) : MakeTupleTraits<const T>::type_t
// from template<class T> foo(T& t) : MakeTupleTraits<T>::type_t
//
// Conversions:
// T -> T,
// references -> compile_time_error
// ReferenceWrapper<T> -> T&
// const ReferenceWrapper<T> -> T&
// array -> const ref array
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
//  general
// ======================================================== 

template<class T>
struct MakeTupleTraits 
{
    typedef T type_t;

    // commented away, see below  (JJ)
    //  typedef typename IF<
    //  boost::is_function<T>::value,
    //  T&,
    //  T>::RET type_t;

}; // end struct MakeTupleTraits

// ======================================================== 
// The is_function test was there originally for plain function types,
// which can't be stored as such (we must either store them as references or
// pointers). Such a type_t could be formed if make_tuple was called with a
// reference to a function.
// But this would mean that a const qualified function type_t was formed in
// the make_tuple function and hence make_tuple can't take a function
// reference as a parameter, and thus T can't be a function type_t.
// So is_function test was removed.
// (14.8.3. says that type_t deduction fails if a cv-qualified function type_t
// is created. (It only applies for the case of explicitly specifying template
// args, though?)) (JJ)
// ======================================================== 

template<class T>
struct MakeTupleTraits<T&> 
{
    typedef typename _private::GenerateError<T&>::do_not_use_with_reference_type error;
}; // end struct MakeTupleTraits<T&>

// ======================================================== 
// Arrays can't be stored as plain types; convert them to references.
// All arrays are converted to const. This is because make_tuple takes its
// parameters as const T& and thus the knowledge of the potential
// non-constness of actual argument is lost.
// ======================================================== 

template<class T, int n>  
struct MakeTupleTraits <T[n]> 
{
    typedef const T (&type_t)[n];
}; // end struct MakeTupleTraits <T[n]>

// ======================================================== 
// 
// ======================================================== 

template<class T, int n>
struct MakeTupleTraits<const T[n]> 
{
    typedef const T (&type_t)[n];
}; // end struct MakeTupleTraits<const T[n]> 

// ======================================================== 
// 
// ======================================================== 

template<class T, int n>  
struct MakeTupleTraits<volatile T[n]> 
{
    typedef const volatile T (&type_t)[n];
}; // end struct MakeTupleTraits<volatile T[n]> 

// ======================================================== 
// 
// ======================================================== 

template<class T, int n>
struct MakeTupleTraits<const volatile T[n]> 
{
    typedef const volatile T (&type_t)[n];
}; // end struct MakeTupleTraits<const volatile T[n]> 

// ======================================================== 
// 
// ======================================================== 

template<class T>
struct MakeTupleTraits<ReferenceWrapper<T> >
{
    typedef T& type_t;
}; // end struct MakeTupleTraits<ReferenceWrapper<T> > 

// ======================================================== 
// 
// ======================================================== 

template<class T>
struct MakeTupleTraits<const ReferenceWrapper<T> >
{
    typedef T& type_t;
}; // end struct MakeTupleTraits<const ReferenceWrapper<T> > 

///////////////////////////////////////////////////////////////////////////////
// class MakeTupleMapper 
// 
// Purpose: 
//  a helper traits to make the make_tuple functions shorter (Vesa Karvonen's suggestion)
// 
///////////////////////////////////////////////////////////////////////////////

template < 
           class T0 = NullType, class T1 = NullType, class T2 = NullType,
           class T3 = NullType, class T4 = NullType, class T5 = NullType,
           class T6 = NullType, class T7 = NullType, class T8 = NullType,
           class T9 = NullType
         >
struct MakeTupleMapper
{
    typedef Tuple < typename MakeTupleTraits<T0>::type_t,
                     typename MakeTupleTraits<T1>::type_t,
                     typename MakeTupleTraits<T2>::type_t,
                     typename MakeTupleTraits<T3>::type_t,
                     typename MakeTupleTraits<T4>::type_t,
                     typename MakeTupleTraits<T5>::type_t,
                     typename MakeTupleTraits<T6>::type_t,
                     typename MakeTupleTraits<T7>::type_t,
                     typename MakeTupleTraits<T8>::type_t,
                     typename MakeTupleTraits<T9>::type_t > type_t;
}; // end struct MakeTupleMapper

// ######################### 
} // end namespace _private 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// namespace tuple functions
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace tuple { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: MakeTuple 
// ------------------------------------------------------------------ 

// 
INLINE Tuple<> MakeTuple() 
{
    return Tuple<>();
}

// 
template<class T0>
INLINE typename _private::MakeTupleMapper<T0>::type_t
MakeTuple ( const T0& _t0 ) 
{
    typedef typename _private::MakeTupleMapper<T0>::type_t t;
    return t(_t0);
}

//
template<class T0, class T1>
INLINE typename _private::MakeTupleMapper<T0, T1>::type_t
MakeTuple ( const T0& _t0, const T1& _t1 ) 
{
    typedef typename _private::MakeTupleMapper<T0, T1>::type_t t;
    return t(_t0, _t1);
}

//
template<class T0, class T1, class T2>
INLINE typename _private::MakeTupleMapper<T0, T1, T2>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2 ) 
{
    typedef typename _private::MakeTupleMapper<T0, T1, T2>::type_t t;
    return t(_t0, _t1, _t2);
}

//
template<class T0, class T1, class T2, class T3>
INLINE typename _private::MakeTupleMapper<T0, T1, T2, T3>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3 ) 
{
    typedef typename _private::MakeTupleMapper<T0, T1, T2, T3>::type_t t;
    return t(_t0, _t1, _t2, _t3);
}

//
template<class T0, class T1, class T2, class T3, class T4>
INLINE typename _private::MakeTupleMapper<T0, T1, T2, T3, T4>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3,
            const T4& _t4 ) 
{
    typedef typename _private::MakeTupleMapper<T0, T1, T2, T3, T4>::type_t t;
    return t(_t0, _t1, _t2, _t3, _t4);
}

//
template<class T0, class T1, class T2, class T3, class T4, class T5>
INLINE typename _private::MakeTupleMapper<T0, T1, T2, T3, T4, T5>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3,
            const T4& _t4, const T5& _t5 ) 
{
    typedef typename _private::MakeTupleMapper<T0, T1, T2, T3, T4, T5>::type_t t;
    return t(_t0, _t1, _t2, _t3, _t4, _t5);
}

//
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6>
INLINE typename _private::MakeTupleMapper<T0, T1, T2, T3, T4, T5, T6>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3,
            const T4& _t4, const T5& _t5, const T6& _t6 ) 
{
    typedef typename _private::MakeTupleMapper<T0, T1, T2, T3, T4, T5, T6>::type_t t;
    return t(_t0, _t1, _t2, _t3, _t4, _t5, _t6);
}

//
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
INLINE typename _private::MakeTupleMapper<T0, T1, T2, T3, T4, T5, T6, T7>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3,
            const T4& _t4, const T5& _t5, const T6& _t6, const T7& _t7 )
{
    typedef typename _private::MakeTupleMapper <T0, T1, T2, T3, T4, T5, T6, T7>::type_t t;
    return t(_t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
}

//
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
INLINE typename _private::MakeTupleMapper <T0, T1, T2, T3, T4, T5, T6, T7, T8>::type_t
MakeTuple( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3,
           const T4& _t4, const T5& _t5, const T6& _t6, const T7& _t7,
           const T8& _t8 ) 
{
    typedef typename _private::MakeTupleMapper <T0, T1, T2, T3, T4, T5, T6, T7, T8>::type_t t;
    return t(_t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8);
}

//
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
INLINE typename _private::MakeTupleMapper <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_t
MakeTuple ( const T0& _t0, const T1& _t1, const T2& _t2, const T3& _t3,
            const T4& _t4, const T5& _t5, const T6& _t6, const T7& _t7,
            const T8& _t8, const T9& _t9 ) 
{
    typedef typename _private::MakeTupleMapper <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_t t;
    return t(_t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
}

// ------------------------------------------------------------------ 
// Desc: Tie
// ------------------------------------------------------------------ 

//
template<class T1>
INLINE Tuple<T1&> 
Tie(T1& _t1) 
{
    return Tuple<T1&> (_t1);
}

//
template<class T1, class T2>
INLINE Tuple<T1&, T2&> 
Tie(T1& _t1, T2& _t2) 
{
    return Tuple<T1&, T2&> (_t1, _t2);
}

//
template<class T1, class T2, class T3>
INLINE Tuple<T1&, T2&, T3&> 
Tie(T1& _t1, T2& _t2, T3& _t3) 
{
    return Tuple<T1&, T2&, T3&> (_t1, _t2, _t3);
}

//
template<class T1, class T2, class T3, class T4>
INLINE Tuple<T1&, T2&, T3&, T4&> 
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4) 
{
    return Tuple<T1&, T2&, T3&, T4&> (_t1, _t2, _t3, _t4);
}

//
template<class T1, class T2, class T3, class T4, class T5>
INLINE Tuple<T1&, T2&, T3&, T4&, T5&>
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5) 
{
    return Tuple<T1&, T2&, T3&, T4&, T5&> (_t1, _t2, _t3, _t4, _t5);
}

//
template<class T1, class T2, class T3, class T4, class T5, class T6>
INLINE Tuple<T1&, T2&, T3&, T4&, T5&, T6&>
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6) 
{
    return Tuple<T1&, T2&, T3&, T4&, T5&, T6&> (_t1, _t2, _t3, _t4, _t5, _t6);
}

//
template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
INLINE Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&>
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6, T7& _t7) 
{
    return Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&> (_t1, _t2, _t3, _t4, _t5, _t6, _t7);
}

//
template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
INLINE Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&>
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6, T7& _t7, T8& _t8) 
{
    return Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&>
        (_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8);
}

//
template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
INLINE Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&>
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6, T7& _t7, T8& _t8, T9& _t9) 
{
    return Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&>
        (_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
}

//
template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
INLINE Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&>
Tie(T1& _t1, T2& _t2, T3& _t3, T4& _t4, T5& _t5, T6& _t6, T7& _t7, T8& _t8, T9& _t9, T10& _t10) 
{
    return Tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&>
        (_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10);
}

// ######################### 
} // end namespace tuple 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END TUPLE_H_1250526147
// #################################################################################
