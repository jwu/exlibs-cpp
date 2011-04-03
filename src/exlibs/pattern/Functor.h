// ======================================================================================
// File         : Functor.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:10:41 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FUNCTOR_H_1250525443
#define FUNCTOR_H_1250525443
// #################################################################################

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Wesley Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class FunctorImplBase 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private { 
// #########################

template < typename RET_T >
struct FunctorImplBase 
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef RET_T ret_t;
    typedef FunctorImplBase<RET_T> self_t;

    typedef EmptyType param1_t;
    typedef EmptyType param2_t;
    typedef EmptyType param3_t;
    typedef EmptyType param4_t;
    typedef EmptyType param5_t;
    typedef EmptyType param6_t;
    typedef EmptyType param7_t;
    typedef EmptyType param8_t;
    typedef EmptyType param9_t;
    typedef EmptyType param10_t;
    typedef EmptyType param11_t;
    typedef EmptyType param12_t;
    typedef EmptyType param13_t;
    typedef EmptyType param14_t;
    typedef EmptyType param15_t;


    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

    virtual ~FunctorImplBase() {}

}; // end struct FunctorImplBase

///////////////////////////////////////////////////////////////////////////////
// class FunctorImpl
// 
// Purpose: 
// The base class for a hierarchy of functors. The FunctorImpl class is not used
//     directly; rather, the Functor class manages and forwards to a pointer to
//     FunctorImpl
// You may want to derive your own functors from FunctorImpl.
// Specializations of FunctorImpl for up to 15 parameters follow
// 
///////////////////////////////////////////////////////////////////////////////

// fwd decl
template < typename RET_T, class TYPE_LIST_T > class FunctorImpl;

// ========================================================
// Specialization for 0 (zero) parameters
// ========================================================

template < typename RET_T >
class FunctorImpl< RET_T, NullType >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    virtual RET_T operator()() const = 0;
}; // end class

// ========================================================
// Specialization for 1 parameter
// ========================================================

template < typename RET_T, typename P1 >
    class FunctorImpl< RET_T, Seq<P1> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    virtual RET_T operator()(param1_t) const = 0;
}; // end class

// ========================================================
// Specialization for 2 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2 > 
class FunctorImpl< RET_T, Seq<P1, P2> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    virtual RET_T operator()(param1_t, param2_t) const = 0;
}; // end class

// ========================================================
// Specialization for 3 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3 >
class FunctorImpl< RET_T, Seq<P1, P2, P3> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t) const = 0;
}; // end class

// ========================================================
// Specialization for 4 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t) const = 0;
}; // end class

// ========================================================
// Specialization for 5 parameters
// ========================================================

template <typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t) const = 0;
}; // end class

// ========================================================
// Specialization for 6 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t) const = 0;
}; // end class

// ========================================================
// Specialization for 7 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t) const = 0;
}; // end class

// ========================================================
// Specialization for 8 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t) const = 0;
}; // end class

// ========================================================
// Specialization for 9 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t) const = 0;
}; // end class

// ========================================================
// Specialization for 10 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9, typename P10 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    typedef typename TypeTraits<P10>::parameter_t param10_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t, param10_t) const = 0;
}; // end class

// ========================================================
// Specialization for 11 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9, typename P10, 
                           typename P11 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    typedef typename TypeTraits<P10>::parameter_t param10_t;
    typedef typename TypeTraits<P11>::parameter_t param11_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t, param10_t, param11_t) const = 0;
}; // end class

// ========================================================
// Specialization for 12 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9, typename P10, 
                           typename P11, typename P12 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    typedef typename TypeTraits<P10>::parameter_t param10_t;
    typedef typename TypeTraits<P11>::parameter_t param11_t;
    typedef typename TypeTraits<P12>::parameter_t param12_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t, param10_t, param11_t, param12_t) const = 0;
}; // end class

// ========================================================
// Specialization for 13 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9, typename P10, 
                           typename P11, typename P12, typename P13 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    typedef typename TypeTraits<P10>::parameter_t param10_t;
    typedef typename TypeTraits<P11>::parameter_t param11_t;
    typedef typename TypeTraits<P12>::parameter_t param12_t;
    typedef typename TypeTraits<P13>::parameter_t param13_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t, param10_t, param11_t, param12_t, param13_t) const = 0;
}; // end class

// ========================================================
// Specialization for 14 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9, typename P10, 
                           typename P11, typename P12, typename P13, typename P14 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    typedef typename TypeTraits<P10>::parameter_t param10_t;
    typedef typename TypeTraits<P11>::parameter_t param11_t;
    typedef typename TypeTraits<P12>::parameter_t param12_t;
    typedef typename TypeTraits<P13>::parameter_t param13_t;
    typedef typename TypeTraits<P14>::parameter_t param14_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t, param10_t, param11_t, param12_t, param13_t, param14_t) const = 0;
}; // end class

// ========================================================
// Specialization for 15 parameters
// ========================================================

template < typename RET_T, typename P1, typename P2, typename P3, typename P4, typename P5, 
                           typename P6, typename P7, typename P8, typename P9, typename P10, 
                           typename P11, typename P12, typename P13, typename P14, typename P15 >
class FunctorImpl< RET_T, Seq<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15> >
    : public FunctorImplBase<RET_T>
{
public:
    typedef RET_T ret_t;
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    typedef typename TypeTraits<P10>::parameter_t param10_t;
    typedef typename TypeTraits<P11>::parameter_t param11_t;
    typedef typename TypeTraits<P12>::parameter_t param12_t;
    typedef typename TypeTraits<P13>::parameter_t param13_t;
    typedef typename TypeTraits<P14>::parameter_t param14_t;
    typedef typename TypeTraits<P15>::parameter_t param15_t;
    virtual RET_T operator()(param1_t, param2_t, param3_t, param4_t, param5_t, param6_t, 
        param7_t, param8_t, param9_t, param10_t, param11_t, param12_t, param13_t, param14_t,
        param15_t) const = 0;
}; // end class

///////////////////////////////////////////////////////////////////////////////
// class NormalFunctorHandler 
// 
// Purpose: 
// Wraps functors and pointers to functions
// 
///////////////////////////////////////////////////////////////////////////////

template <class BASE_T, typename FN_PTR_T>
class NormalFunctorHandler : public BASE_T::impl_t
{

    ///////////////////////////////////////////////////////////////////////////////
    // private typedefs 
    ///////////////////////////////////////////////////////////////////////////////

private:
    typedef typename BASE_T::impl_t base_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public typdefs
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef typename base_t::ret_t      ret_t;
    typedef typename base_t::param1_t   param1_t;
    typedef typename base_t::param2_t   param2_t;
    typedef typename base_t::param3_t   param3_t;
    typedef typename base_t::param4_t   param4_t;
    typedef typename base_t::param5_t   param5_t;
    typedef typename base_t::param6_t   param6_t;
    typedef typename base_t::param7_t   param7_t;
    typedef typename base_t::param8_t   param8_t;
    typedef typename base_t::param9_t   param9_t;
    typedef typename base_t::param10_t  param10_t;
    typedef typename base_t::param11_t  param11_t;
    typedef typename base_t::param12_t  param12_t;
    typedef typename base_t::param13_t  param13_t;
    typedef typename base_t::param14_t  param14_t;
    typedef typename base_t::param15_t  param15_t;
    
    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    NormalFunctorHandler( const FN_PTR_T& _pfn ) : m_pfn(_pfn) {}
    
    ///////////////////////////////////////////////////////////////////////////////
    // public member function defines 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // operator() implementations for up to 15 arguments

    //
    ret_t operator() () const
    {
        return m_pfn(); 
    }

    //
    ret_t operator() ( param1_t _p1 ) const
    {
        return m_pfn(_p1); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2 ) const
    {
        return m_pfn(_p1, _p2); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3 ) const
    { 
        return m_pfn(_p1, _p2, _p3); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4 ) const
    { 
        return m_pfn(_p1, _p2, _p3, _p4); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5, 
                       param6_t _p6 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7); 
    }
    
    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8 ) const
    { 
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10); 
    }

    //
    ret_t operator()( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                      param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                      param11_t _p11 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14);
    }

    //
    ret_t operator()( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                      param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                      param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14, param15_t _p15 ) const
    {
        return m_pfn(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14, _p15);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // private member data 
    ///////////////////////////////////////////////////////////////////////////////

private:

    FN_PTR_T m_pfn;

}; // end class NormalFunctorHandler

///////////////////////////////////////////////////////////////////////////////
// class MemberFunctorHandler 
// 
// Purpose: 
// Wraps pointers to member functions
// 
///////////////////////////////////////////////////////////////////////////////


template <class BASE_T, typename OBJ_PTR_T, typename MEM_FN_PTR_T> 
class MemberFunctorHandler : public BASE_T::impl_t
{
    ///////////////////////////////////////////////////////////////////////////////
    // private typedefs 
    ///////////////////////////////////////////////////////////////////////////////

private:
    typedef typename BASE_T::impl_t base_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef typename base_t::ret_t      ret_t;
    typedef typename base_t::param1_t   param1_t;
    typedef typename base_t::param2_t   param2_t;
    typedef typename base_t::param3_t   param3_t;
    typedef typename base_t::param4_t   param4_t;
    typedef typename base_t::param5_t   param5_t;
    typedef typename base_t::param6_t   param6_t;
    typedef typename base_t::param7_t   param7_t;
    typedef typename base_t::param8_t   param8_t;
    typedef typename base_t::param9_t   param9_t;
    typedef typename base_t::param10_t  param10_t;
    typedef typename base_t::param11_t  param11_t;
    typedef typename base_t::param12_t  param12_t;
    typedef typename base_t::param13_t  param13_t;
    typedef typename base_t::param14_t  param14_t;
    typedef typename base_t::param15_t  param15_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

    MemberFunctorHandler ( const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn ) 
        : m_pObj(_pObj), 
          m_pfn(_pfn)
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

    // operator() implementations for up to 15 arguments

    //
    ret_t operator() () const
    { 
        return ((*m_pObj).*m_pfn)(); 
    }

    //
    ret_t operator() ( param1_t _p1 ) const
    { 
        return ((*m_pObj).*m_pfn)(_p1); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10); 
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11);
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12);
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13);
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14);
    }

    //
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14, param15_t _p15 ) const
    {
        return ((*m_pObj).*m_pfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14, _p15);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // private member data
    ///////////////////////////////////////////////////////////////////////////////

private:

    OBJ_PTR_T       m_pObj;
    MEM_FN_PTR_T    m_pfn;

}; // end class MemberFunctorHandler


///////////////////////////////////////////////////////////////////////////////
// class FunctorBase 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class FunctorBase
{
public:
    //
    void reset()
    {
        m_functorHandlerInfo.function_info.vtable      = NULL;
        m_functorHandlerInfo.function_info.object      = NULL;
        m_functorHandlerInfo.function_info.function    = NULL;
        m_functorHandlerInfo.function_info.data        = NULL;
    }

    // disable bool test, we don't want to see code like: if ( functor ), use if ( functor.isValid() ) instead
    // operator bool () const { return m_functorHandlerInfo.function_info.vtable != NULL; } 

protected:
    //
    union FunctorHandlerInfo
    {
        struct FunctionInfo
        {
            void* vtable;
            void* object;
            void* function;
            void* data;
            void* hack;
        }; // end struct FunctionInfo 
        FunctionInfo   function_info;
        uint8          data[sizeof(FunctionInfo)];

    }; // end union FunctorHandlerInfo

    //
    FunctorHandlerInfo   m_functorHandlerInfo;

    ///////////////////////////////////////////////////////////////////////////////
    // generics function 
    ///////////////////////////////////////////////////////////////////////////////
public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string = string + "vtable: " + to_str<FLAGS>(m_functorHandlerInfo.function_info.vtable) + "\n";
        string = string + "object: " + to_str<FLAGS>(m_functorHandlerInfo.function_info.object) + "\n";
        string = string + "function: " + to_str<FLAGS>(m_functorHandlerInfo.function_info.function) + "\n";
        string = string + "data: " + to_str<FLAGS>(m_functorHandlerInfo.function_info.data) + "\n";
        return string;
    }

}; // end class FunctorBase 

// #########################
} // end namespace _private 
// #########################

    
///////////////////////////////////////////////////////////////////////////////
// class Functor 
// 
// Purpose: 
//  \ingroup FunctorGroup
//  A generalized functor implementation with value semantics
//
// \par Macro: LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT
// Define 
// \code LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT \endcode
// to avoid static instantiation/delete 
// order problems.
// It often helps against crashes when using static Functors and multi threading.
// Defining also removes problems when unloading Dlls which hosts
// static Functor objects.
//
// \par Macro: LOKI_FUNCTORS_ARE_COMPARABLE
// To enable the operator== define the macro
// \code LOKI_FUNCTORS_ARE_COMPARABLE \endcode
// The macro is disabled by default, because it breaks compiling functor 
// objects  which have no operator== implemented, keep in mind when you enable
// operator==.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename RET_T = void, class TYPE_LIST_T = NullType >
class Functor : public _private::FunctorBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // public typedefes 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef _private::FunctorImpl<RET_T, TYPE_LIST_T> impl_t; // handler will public from this impl
    typedef RET_T ret_t;
    typedef TYPE_LIST_T param_list_t;
    typedef typename impl_t::param1_t param1_t;
    typedef typename impl_t::param2_t param2_t;
    typedef typename impl_t::param3_t param3_t;
    typedef typename impl_t::param4_t param4_t;
    typedef typename impl_t::param5_t param5_t;
    typedef typename impl_t::param6_t param6_t;
    typedef typename impl_t::param7_t param7_t;
    typedef typename impl_t::param8_t param8_t;
    typedef typename impl_t::param9_t param9_t;
    typedef typename impl_t::param10_t param10_t;
    typedef typename impl_t::param11_t param11_t;
    typedef typename impl_t::param12_t param12_t;
    typedef typename impl_t::param13_t param13_t;
    typedef typename impl_t::param14_t param14_t;
    typedef typename impl_t::param15_t param15_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    Functor()
    {
        reset();
    }
    
    Functor( const Functor& _copy ) 
    {
        m_functorHandlerInfo = _copy.m_functorHandlerInfo;
    }
    
    template < typename FN_PTR_T >
    Functor( FN_PTR_T _pfn )
    {
        ex_assert( _pfn, "the _func_ptr can't be NULL" );
        ex_static_assert( sizeof( _private::NormalFunctorHandler< Functor, FN_PTR_T > ) <= sizeof( FunctorHandlerInfo ), "The function can not support functor" );
        ex_new_in ( &m_functorHandlerInfo ) _private::NormalFunctorHandler< Functor, FN_PTR_T >( _pfn );
    }

    template < class OBJ_PTR_T, typename MEM_FN_PTR_T >
    Functor( const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn, bool _noAssert = false )
    {
        ex_assert( _pObj || (!_pObj && _noAssert), "the _pObj can't be NULL" );
        ex_assert( _pfn, "the _pfn can't be NULL" );
        ex_static_assert( sizeof( _private::MemberFunctorHandler< Functor, OBJ_PTR_T, MEM_FN_PTR_T > ) <= sizeof( FunctorHandlerInfo ), "The function can not support functor" );
        ex_new_in ( &m_functorHandlerInfo ) _private::MemberFunctorHandler< Functor, OBJ_PTR_T, MEM_FN_PTR_T >( _pObj, _pfn );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member function defines 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set 
    // ========================================================

    //
    template < class OBJ_PTR_T >
    void set_object( const OBJ_PTR_T& _pObj )
    {
        ex_assert( _pObj, "the _pObj can't be NULL" );
        m_functorHandlerInfo.function_info.object = _pObj;
    }

    //
    template < typename FN_PTR_T >
	void set( FN_PTR_T _pfn )
	{
        ex_assert( _pfn, "the _pfn can't be NULL" );
        ex_static_assert( sizeof( _private::NormalFunctorHandler< Functor, FN_PTR_T > ) <= sizeof( FunctorHandlerInfo ), "The function can not support functor" );
        reset();
        ex_new_in ( &m_functorHandlerInfo ) _private::NormalFunctorHandler< Functor, FN_PTR_T >( _pfn );
	}

    //
    template < class OBJ_PTR_T, typename MEM_FN_PTR_T >
    void set( const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn, bool _noAssert = false )
    {
        ex_assert( _pObj || (!_pObj && _noAssert), "the _pObj can't be NULL" );
        ex_assert( _pfn, "the _pfn can't be NULL" );
        ex_static_assert( sizeof( _private::MemberFunctorHandler< Functor, OBJ_PTR_T, MEM_FN_PTR_T > ) <= sizeof( FunctorHandlerInfo ), "The function can not support functor" );
        reset();
        ex_new_in ( &m_functorHandlerInfo ) _private::MemberFunctorHandler< Functor, OBJ_PTR_T, MEM_FN_PTR_T >( _pObj, _pfn );
    }

    // ========================================================
    // operator =
    // ========================================================

    //
    INLINE Functor& operator = ( const Functor& _copy )
    {
        m_functorHandlerInfo = _copy.m_functorHandlerInfo;
        return *this;
    }

    //
    INLINE Functor& operator = ( int _zero )
    {
        ex_assert( _zero == 0, "" );
        reset();
        return *this;
    }

    //
	template< typename FN_PTR_T >
    INLINE Functor& operator = ( FN_PTR_T _pfn )
    {
        set(_pfn);
        return *this;
    }

    // ========================================================
    // compare 
    // ========================================================

    //
    bool isValid() const
    {
        return m_functorHandlerInfo.function_info.vtable != NULL; 
    }

    //
    bool operator == ( const Functor& _rhs ) const
    {
        return m_functorHandlerInfo.function_info.vtable   == _rhs.m_functorHandlerInfo.function_info.vtable   &&
               m_functorHandlerInfo.function_info.object   == _rhs.m_functorHandlerInfo.function_info.object   &&
               m_functorHandlerInfo.function_info.function == _rhs.m_functorHandlerInfo.function_info.function &&
               m_functorHandlerInfo.function_info.data     == _rhs.m_functorHandlerInfo.function_info.data;
    }

    //
    bool operator != ( const Functor& _rhs ) const
    {
        return m_functorHandlerInfo.function_info.vtable   != _rhs.m_functorHandlerInfo.function_info.vtable   ||
               m_functorHandlerInfo.function_info.object   != _rhs.m_functorHandlerInfo.function_info.object   ||
               m_functorHandlerInfo.function_info.function != _rhs.m_functorHandlerInfo.function_info.function ||
               m_functorHandlerInfo.function_info.data     != _rhs.m_functorHandlerInfo.function_info.data;
    }

    // ========================================================
    // operator() implementations for up to 15 arguments
    // ========================================================

    #define GET_FUNCTOR_IMPL() \
        ex_assert( this->isValid(), "functor is invalid" ); \
        const impl_t* pFunctorImpl = reinterpret_cast< const impl_t* >( &m_functorHandlerInfo ); \

    ret_t operator() () const
    {
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(); 
    }

    ret_t operator() ( param1_t _p1 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2 ) const
    {    
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3 ) const
    {    
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11 ) const
    { 
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11); 
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12 ) const
    {
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12);
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13 ) const
    {
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13);
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14 ) const
    {
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14);
    }
    
    ret_t operator() ( param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                       param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, 
                       param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14, param15_t _p15 ) const
    {
        GET_FUNCTOR_IMPL();
        return (*pFunctorImpl)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14, _p15);
    }

#undef GET_FUNCTOR_IMPL

}; // end class Functor


// TODO: need this?
#if 0
////////////////////////////////////////////////////////////////////////////////
//  
//  BindersFirst and Chainer 
//
////////////////////////////////////////////////////////////////////////////////

namespace _private
{
    template <class Fctor> struct BinderFirstTraits;

    template <typename RET_T, class TYPE_LIST_T, template <class, class> class ThreadingModel>
    struct BinderFirstTraits< Functor<RET_T, TYPE_LIST_T, ThreadingModel> >
    {
        typedef Functor<RET_T, TYPE_LIST_T, ThreadingModel> OriginalFunctor;

        typedef typename TL::erase<TYPE_LIST_T,typename TL::TypeAt<TYPE_LIST_T, 0>::result_t>
                         ::result_t
                param_list_t;

        typedef typename TL::TypeAt<TYPE_LIST_T, 0>::result_t OriginalParm1;

        typedef Functor<RET_T, param_list_t, ThreadingModel> BoundFunctorType;

        typedef typename BoundFunctorType::impl_t impl_t;

    };  


    template<class T>
    struct BinderFirstBoundTypeStorage;

    template<class T>
    struct BinderFirstBoundTypeStorage
    {
        typedef typename TypeTraits<T>::parameter_t RefOrValue;
    };
    
    template <typename RET_T, class TYPE_LIST_T, template <class, class> class ThreadingModel>
    struct BinderFirstBoundTypeStorage< Functor<RET_T, TYPE_LIST_T, ThreadingModel> >
    {
        typedef Functor<RET_T, TYPE_LIST_T, ThreadingModel> OriginalFunctor;
        typedef const typename TypeTraits<OriginalFunctor>::ReferredType RefOrValue;
    };  


} // namespace _private

////////////////////////////////////////////////////////////////////////////////
///  \class BinderFirst
///  
///  \ingroup FunctorGroup
///  Binds the first parameter of a Functor object to a specific value
////////////////////////////////////////////////////////////////////////////////

template <class OriginalFunctor>
class BinderFirst 
    : public _private::BinderFirstTraits<OriginalFunctor>::impl_t
{
    typedef typename _private::BinderFirstTraits<OriginalFunctor>::impl_t base_t;
    typedef typename OriginalFunctor::ret_t ret_t;

    typedef typename OriginalFunctor::param1_t BoundType;

    typedef typename _private::BinderFirstBoundTypeStorage<
                         typename _private::BinderFirstTraits<OriginalFunctor>
                         ::OriginalParm1>
                     ::RefOrValue
            BoundTypeStorage;
                    
    typedef typename OriginalFunctor::param2_t param1_t;
    typedef typename OriginalFunctor::param3_t param2_t;
    typedef typename OriginalFunctor::param4_t param3_t;
    typedef typename OriginalFunctor::param5_t param4_t;
    typedef typename OriginalFunctor::param6_t param5_t;
    typedef typename OriginalFunctor::param7_t param6_t;
    typedef typename OriginalFunctor::param8_t param7_t;
    typedef typename OriginalFunctor::param9_t param8_t;
    typedef typename OriginalFunctor::param10_t param9_t;
    typedef typename OriginalFunctor::param11_t param10_t;
    typedef typename OriginalFunctor::param12_t param11_t;
    typedef typename OriginalFunctor::param13_t param12_t;
    typedef typename OriginalFunctor::param14_t param13_t;
    typedef typename OriginalFunctor::param15_t param14_t;
    typedef EmptyType param15_t;

public:
    
    BinderFirst(const OriginalFunctor& fun, BoundType bound)
    : f_(fun), b_(bound)
    {}

    LOKI_DEFINE_CLONE_FUNCTORIMPL(BinderFirst)

#ifdef LOKI_FUNCTORS_ARE_COMPARABLE
    
    bool operator==(const typename base_t::self_t& rhs) const
    {
        if(typeid(*this) != typeid(rhs))
            return false; // cannot be equal 
        // if this line gives a compiler error, you are using a function object.
        // you need to implement bool MyFnObj::operator == (const MyFnObj&) const;
        return    f_ == ((static_cast<const BinderFirst&> (rhs)).f_) &&
                  b_ == ((static_cast<const BinderFirst&> (rhs)).b_);
    }
#endif

    // operator() implementations for up to 15 arguments
            
    ret_t operator()()
    { return f_(b_); }

    ret_t operator()(param1_t _p1)
    { return f_(b_, _p1); }
    
    ret_t operator()(param1_t _p1, param2_t _p2)
    { return f_(b_, _p1, _p2); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3)
    { return f_(b_, _p1, _p2, _p3); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4)
    { return f_(b_, _p1, _p2, _p3, _p4); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12, param13_t _p13)
    { return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12, param13_t _p13, param14_t _p14)
    {
        return f_(b_, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, 
            _p14);
    }
    
private:
    OriginalFunctor f_;
    BoundTypeStorage b_;
};

////////////////////////////////////////////////////////////////////////////////
///  Binds the first parameter of a Functor object to a specific value
///  \ingroup FunctorGroup
////////////////////////////////////////////////////////////////////////////////

template <class Fctor>
typename _private::BinderFirstTraits<Fctor>::BoundFunctorType
BindFirst(
    const Fctor& fun, 
    typename Fctor::param1_t bound)
{
    typedef typename _private::BinderFirstTraits<Fctor>::BoundFunctorType
        Outgoing;
    
    return Outgoing(std::auto_ptr<typename Outgoing::impl_t>(
        new BinderFirst<Fctor>(fun, bound)));
}

////////////////////////////////////////////////////////////////////////////////
///  \class Chainer
///
///  \ingroup FunctorGroup
///   Chains two functor calls one after another
////////////////////////////////////////////////////////////////////////////////

template <typename Fun1, typename Fun2>
class Chainer : public Fun2::impl_t
{
    typedef Fun2 base_t;

public:
    typedef typename base_t::ret_t ret_t;
    typedef typename base_t::param1_t param1_t;
    typedef typename base_t::param2_t param2_t;
    typedef typename base_t::param3_t param3_t;
    typedef typename base_t::param4_t param4_t;
    typedef typename base_t::param5_t param5_t;
    typedef typename base_t::param6_t param6_t;
    typedef typename base_t::param7_t param7_t;
    typedef typename base_t::param8_t param8_t;
    typedef typename base_t::param9_t param9_t;
    typedef typename base_t::param10_t param10_t;
    typedef typename base_t::param11_t param11_t;
    typedef typename base_t::param12_t param12_t;
    typedef typename base_t::param13_t param13_t;
    typedef typename base_t::param14_t param14_t;
    typedef typename base_t::param15_t param15_t;
    
    Chainer(const Fun1& fun1, const Fun2& fun2) : f1_(fun1), f2_(fun2) {}

    LOKI_DEFINE_CLONE_FUNCTORIMPL(Chainer)

#ifdef LOKI_FUNCTORS_ARE_COMPARABLE
            
    bool operator==(const typename base_t::impl_t::self_t& rhs) const
    {
        if(typeid(*this) != typeid(rhs))
            return false; // cannot be equal 
        // if this line gives a compiler error, you are using a function object.
        // you need to implement bool MyFnObj::operator == (const MyFnObj&) const;
        return    f1_ == ((static_cast<const Chainer&> (rhs)).f2_) &&
                  f2_ == ((static_cast<const Chainer&> (rhs)).f1_);
    }
#endif

    // operator() implementations for up to 15 arguments

    ret_t operator()()
    { return f1_(), f2_(); }

    ret_t operator()(param1_t _p1)
    { return f1_(_p1), f2_(_p1); }
    
    ret_t operator()(param1_t _p1, param2_t _p2)
    { return f1_(_p1, _p2), f2_(_p1, _p2); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3)
    { return f1_(_p1, _p2, _p3), f2_(_p1, _p2, _p3); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4)
    { return f1_(_p1, _p2, _p3, _p4), f2_(_p1, _p2, _p3, _p4); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5)
    { return f1_(_p1, _p2, _p3, _p4, _p5), f2_(_p1, _p2, _p3, _p4, _p5); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6)
    { return f1_(_p1, _p2, _p3, _p4, _p5, _p6), f2_(_p1, _p2, _p3, _p4, _p5, _p6); }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12, param13_t _p13)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12, param13_t _p13, param14_t _p14)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, 
                _p14),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, 
               _p14);
    }
    
    ret_t operator()(param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
        param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10, param11_t _p11,
        param12_t _p12, param13_t _p13, param14_t _p14, param15_t _p15)
    {
        return f1_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, 
                _p14, _p15),
            f2_(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, 
                _p14, _p15);
    }
    
private:
    Fun1 f1_;
    Fun2 f2_;
};

////////////////////////////////////////////////////////////////////////////////
///  Chains two functor calls one after another
///  \ingroup FunctorGroup
////////////////////////////////////////////////////////////////////////////////


template <class Fun1, class Fun2>
Fun2 Chain(
    const Fun1& fun1,
    const Fun2& fun2)
{
    return Fun2(std::auto_ptr<typename Fun2::impl_t>(
        new Chainer<Fun1, Fun2>(fun1, fun2)));
}
#endif

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END FUNCTOR_H_1250525443
// #################################################################################
