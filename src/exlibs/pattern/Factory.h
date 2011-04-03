// ======================================================================================
// File         : Factory.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:10:17 AM | Tuesday,August
// Description  : 
// ======================================================================================

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// Copyright (c) 2005 by Peter Kuemmel
// This code DOES NOT accompany the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
//
// Code covered by the MIT License
// The authors make no representations about the suitability of this software
// for any purpose. It is provided "as is" without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #################################################################################
#ifndef FACTORY_H_1250525421
#define FACTORY_H_1250525421
// #################################################################################

#if 0
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4702)
//unreachable code if onUnknownType throws an exception
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
// <i>The Factory Method pattern is an object-oriented design pattern.
// Like other creational patterns, it deals with the problem of creating objects
// (products) without specifying the exact class of object that will be created.
// Factory Method, one of the patterns from the Design Patterns book, handles
// this problem by defining a separate method for creating the objects, which
// subclasses can then override to specify the derived type of product that will
// be created.
// <br>
// More generally, the term Factory Method is often used to refer to any method
// whose main purpose is creation of objects.</i>
// <div ALIGN="RIGHT"><a href="http://en.wikipedia.org/wiki/Factory_method_pattern">
// Wikipedia</a></div>
// 
// Loki proposes a generic version of the Factory. Here is a typical use.<br>
// <code><br>
// 1. Factory< int, OBJ_T > aFactory;<br>
// 2. aFactory.reg( 1, createProductNull );<br>
// 3. aFactory.create( 1 ); <br>
// </code><br>
// <br>
// - 1. The declaration<br>
// You want a Factory that produces OBJ_T.<br>
// The client will refer to a creation method through an int.<br>
// - 2.The registration<br>
// The code that will contribute to the Factory will now need to declare its
// ProductCreator by registering them into the Factory.<br>
// A ProductCreator is a just a function that will return the right object. ie <br>
// <code>
// Product* createProductNull()<br>             
// {<br>
//     return new Product<br>
// }<br>
// </code><br>
// - 3. The use<br>
// Now the client can create object by calling the Factory's create method
// with the right identifier. If the ProductCreator were to have arguments
// (<i>ie :Product* createProductParm( int a, int b )</i>)
///////////////////////////////////////////////////////////////////////////////


// #########################
namespace ex { 
// #########################

#if 0
/**
 * \defgroup	FactoryErrorPoliciesGroup Factory Error Policies
 * \ingroup		FactoryGroup
 * \brief		Manages the "Unknown Type" error in an object factory
 * 
 * \class DefaultFactoryError
 * \ingroup		FactoryErrorPoliciesGroup
 * \brief		Default policy that throws an exception		
 * 
 */

    template <typename ID_T, class OBJ_T>
    struct DefaultFactoryError
    {
        struct Exception : public std::exception
        {
            const char* what() const throw() { return "Unknown Type"; }
        };

        static OBJ_T* onUnknownType(ID_T)
        {
            throw Exception();
        }
    };
#endif


///////////////////////////////////////////////////////////////////////////////
// class FactoryImplBase 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

struct FactoryImplBase
{
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
}; // end struct FactoryImplBase


///////////////////////////////////////////////////////////////////////////////
// class FactoryImpl 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// forward decl
// ========================================================

template < typename OBJ_T, typename ID_T, typename TYPE_LIST_T > struct FactoryImpl;

// ========================================================
// 0 param
// ========================================================

template < typename OBJ_T, typename ID_T >
struct FactoryImpl<OBJ_T, ID_T, NullType> : public FactoryImplBase
{
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create( const ID_T& id ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 1 param 
// ========================================================

template < typename OBJ_T, typename ID_T, typename P1 >
struct FactoryImpl<OBJ_T,ID_T, Seq<P1> > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 2 params 
// ========================================================

template < typename OBJ_T, typename ID_T, typename P1,typename P2 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 3 params 
// ========================================================

template < typename OBJ_T, typename ID_T, typename P1,typename P2,typename P3 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 4 params 
// ========================================================

template < typename OBJ_T, typename ID_T, typename P1,typename P2,typename P3,typename P4 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 5 params 
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 6 params 
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 7 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t ) = 0;
}; // end struct FactoryImpl

// ========================================================
// 8 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 9 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9 > > : public FactoryImplBase
{
    typedef typename TypeTraits<P1>::parameter_t param1_t;
    typedef typename TypeTraits<P2>::parameter_t param2_t;
    typedef typename TypeTraits<P3>::parameter_t param3_t;
    typedef typename TypeTraits<P4>::parameter_t param4_t;
    typedef typename TypeTraits<P5>::parameter_t param5_t;
    typedef typename TypeTraits<P6>::parameter_t param6_t;
    typedef typename TypeTraits<P7>::parameter_t param7_t;
    typedef typename TypeTraits<P8>::parameter_t param8_t;
    typedef typename TypeTraits<P9>::parameter_t param9_t;
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param9_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 10 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9,typename P10 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10 > > : public FactoryImplBase
{
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
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param9_t,param10_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 11 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9,typename P10,
           typename P11 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11 > > : public FactoryImplBase
{
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
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param9_t,param10_t,
                                param11_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 12 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9,typename P10,
           typename P11,typename P12 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12 > > : public FactoryImplBase
{
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
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param9_t,param10_t,
                                param11_t,param12_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 13 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9,typename P10,
           typename P11,typename P12,typename P13>
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13 > > : public FactoryImplBase
{
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
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param9_t,param10_t,
                                param11_t,param12_t,param13_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 14 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9,typename P10,
           typename P11,typename P12,typename P13,typename P14>
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14 > > : public FactoryImplBase
{
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
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param8_t,param10_t,
                                param11_t,param12_t,param13_t,param14_t) = 0;
}; // end struct FactoryImpl

// ========================================================
// 15 params
// ========================================================

template < typename OBJ_T, typename ID_T,
           typename P1,typename P2,typename P3,typename P4,typename P5,
           typename P6,typename P7,typename P8,typename P9,typename P10,
           typename P11,typename P12,typename P13,typename P14,typename P15 >
struct FactoryImpl<OBJ_T, ID_T, Seq< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15 > > : public FactoryImplBase
{
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
    virtual ~FactoryImpl() {}
    virtual OBJ_T* create(const ID_T& id,param1_t, param2_t, param3_t, param4_t, param5_t,
                                param6_t, param7_t, param8_t, param9_t,param10_t,
                                param11_t,param12_t,param13_t,param14_t,param15_t ) = 0;
}; // end struct FactoryImpl

///////////////////////////////////////////////////////////////////////////////
// class Factory
// 
// Purpose: 
//  Implements a generic object factory.
//
//  create functions can have up to 15 parameters.
//
//  \par Singleton lifetime when used with Loki::SingletonHolder
//  Because Factory uses internally Functors which inherits from
//  SmallObject you must use the singleton lifetime
//  \code Loki::LongevityLifetime::DieAsSmallObjectChild \endcode
//  Alternatively you could suppress for Functor the inheritance
//  from SmallObject by defining the macro:
// \code LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT \endcode
// 
///////////////////////////////////////////////////////////////////////////////

template
<
    typename ID_T,
    class OBJ_T,
    typename PARAM_LIST_T = NullType,
    typename CREATOR_MAP_T = HashMap<ID_T,Functor<OBJ_T*,PARAM_LIST_T> >
>
class Factory
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    typedef FactoryImpl< OBJ_T, ID_T, PARAM_LIST_T > impl_t;

    //
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

public:

    //
    typedef ID_T id_t;
    typedef OBJ_T object_t;
    typedef Functor<OBJ_T*,PARAM_LIST_T> creator_t;
    typedef CREATOR_MAP_T creator_map_t;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    creator_map_t m_CreatorMap;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    Factory()
        : m_CreatorMap(4096)
    {
    }

    ~Factory()
    {
        m_CreatorMap.clear();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    bool hasRegistered ( const ID_T& _id ) const
    {
        if ( m_CreatorMap.find(_id) != m_CreatorMap.end() )
            return true;
        return false;
    }

    // 
    result_t reg( const ID_T& _id, creator_t _creator )
    {
        Pair<typename creator_map_t::sz_t,result_t> result_pair = m_CreatorMap.insert( _id, _creator );
        return result_pair.second;
    }

    // 
    template < class OBJ_PTR_T, typename MEM_FN_PTR_T >
    result_t reg( const ID_T& _id, const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn )
    {
        creator_t creator( _pObj, _pfn );
        Pair<typename creator_map_t::sz_t,result_t> result_pair = m_CreatorMap.insert( _id, creator );
        return result_pair.second;
    }

    // 
    result_t unreg( const ID_T& _id )
    {
        return m_CreatorMap.erase(_id);
    }

    //
    void ureg_all()
    {
        m_CreatorMap.clear();
        m_CreatorMap.resize(1);
    }

    //
    Array<ID_T> regIDs()
    {
        Array<ID_T> ids;
        typename creator_map_t::iterator iter = m_CreatorMap.begin();
        typename creator_map_t::iterator iterEnd = m_CreatorMap.end();
        for ( ; iter != iterEnd; ++iter )
        {
            ids.push_back( iter.key() );
        }
        return ids;
    }

    //
    static OBJ_T* onUnknownType_StringID( const ID_T& _id )
    {
        ex_error ( "Unknown Type %s", _id.c_str() );
        return NULL;
    }

    //
    static OBJ_T* onUnknownType( const ID_T& _id )
    {
        if ( typeop::IsSameType<string_id_t,ID_T>::Result ||
             typeop::IsSameType<wstring_id_t,ID_T>::Result )
        {
            return onUnknownType_StringID(_id); // NOTE: for better error information.
        }
        else
        {
            ex_error ( "Unknown Type" );
        }
        return NULL;
    }

    // ========================================================
    // create
    // ========================================================


    //
    OBJ_T* create( const ID_T& _id )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)();
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id, 
                         param1_t _p1 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)(_p1);
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id, 
                         param1_t _p1, param2_t _p2 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2 );
        return this->onUnknownType(_id);
    }

    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7  )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7, param8_t _p8 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9 );
        return this->onUnknownType(_id);
    }
    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9,param10_t _p10 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t  _p5,
                         param6_t  _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10,
                         param11_t _p11 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2, param3_t _p3, param4_t _p4, param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7, param8_t _p8, param9_t _p9, param10_t _p10,
                         param11_t _p11, param12_t _p12 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2,  param3_t  _p3, param4_t _p4, param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7,  param8_t  _p8, param9_t _p9, param10_t _p10,
                         param11_t _p11, param12_t _p12, param13_t _p13 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2,  param3_t  _p3,  param4_t  _p4, param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7,  param8_t  _p8,  param9_t  _p9, param10_t _p10,
                         param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2,  param3_t  _p3,  param4_t  _p4,  param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7,  param8_t  _p8,  param9_t  _p9,  param10_t _p10,
                         param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14, param15_t _p15 )
    {
        typename creator_map_t::iterator iter = m_CreatorMap.find(_id);
        if ( iter != m_CreatorMap.end() )
            return (*iter)( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15 );
        return this->onUnknownType(_id);
    }
}; // end class Factory


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t DefaultDestructor ( T* _pObj ) {
    ex_delete (_pObj);
    return EResult::ok;
}

///////////////////////////////////////////////////////////////////////////////
// class FactoryManageDestrct
// 
// Purpose: 
//   This class not just manage construct the object, also manage the destruct
// 
///////////////////////////////////////////////////////////////////////////////

template
<
    typename ID_T,
    class OBJ_T,
    typename PARAM_LIST_T = NullType
>
class FactoryManageDestrct : public Factory< ID_T, 
                                             OBJ_T, 
                                             PARAM_LIST_T, 
                                             HashMap< ID_T, 
                                                      Pair< Functor<OBJ_T*,PARAM_LIST_T>,
                                                            Functor<result_t,Seq<OBJ_T*> > 
                                                          > 
                                                    >
                                           >
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    typedef Factory< ID_T, 
                      OBJ_T, 
                      PARAM_LIST_T, 
                      HashMap< ID_T, 
                                    Pair< Functor<OBJ_T*,PARAM_LIST_T>, 
                                           Functor<result_t,Seq<OBJ_T*> >
                                         >
                                  >
                    > base_t;
    typedef FactoryManageDestrct<ID_T,OBJ_T,PARAM_LIST_T> self_t;
    typedef typename base_t::impl_t impl_t;

    //
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

public:

    //
    typedef ID_T id_t;
    typedef OBJ_T object_t;
    typedef typename base_t::creator_t creator_t;
    typedef Functor<result_t,Seq<OBJ_T*> > destructor_t;
    typedef Pair<creator_t,destructor_t> pair_t;

    //
    typedef typename base_t::creator_map_t creator_map_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    FactoryManageDestrct()
        : base_t()
    {
    }

    ~FactoryManageDestrct()
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    result_t reg( const ID_T& _id, creator_t _creator, destructor_t _destrctor = DefaultDestructor<OBJ_T> )
    {
        Pair<typename creator_map_t::sz_t,result_t> result_pair = base_t::m_CreatorMap.insert( _id, pair_t(_creator,_destrctor) );
        return result_pair.second;
    }

    // 
    template < class OBJ_PTR_T, typename MEM_FN_PTR_T >
    result_t reg( const ID_T& _id, const OBJ_PTR_T& _pObj, MEM_FN_PTR_T _pfn_create, MEM_FN_PTR_T _pfn_destruct )
    {
        creator_t creator( _pObj, _pfn_create );
        destructor_t destrctor( _pObj, _pfn_destruct );
        Pair<typename creator_map_t::sz_t,result_t> result_pair = base_t::m_CreatorMap.insert( _id, pair_t(creator,destrctor) );
        return result_pair.second;
    }

    // ========================================================
    // create
    // ========================================================

    //
    OBJ_T* create( const ID_T& _id )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first();
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id, 
                         param1_t _p1 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first(_p1);
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id, 
                         param1_t _p1, param2_t _p2 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2 );
        return this->onUnknownType(_id);
    }

    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7  )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7, param8_t _p8 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9 );
        return this->onUnknownType(_id);
    }
    //
    OBJ_T* create( const ID_T& _id,
                         param1_t _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t _p5,
                         param6_t _p6, param7_t _p7, param8_t _p8, param9_t _p9,param10_t _p10 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1, param2_t _p2, param3_t _p3, param4_t _p4, param5_t  _p5,
                         param6_t  _p6, param7_t _p7, param8_t _p8, param9_t _p9, param10_t _p10,
                         param11_t _p11 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2, param3_t _p3, param4_t _p4, param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7, param8_t _p8, param9_t _p9, param10_t _p10,
                         param11_t _p11, param12_t _p12 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2,  param3_t  _p3, param4_t _p4, param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7,  param8_t  _p8, param9_t _p9, param10_t _p10,
                         param11_t _p11, param12_t _p12, param13_t _p13 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2,  param3_t  _p3,  param4_t  _p4, param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7,  param8_t  _p8,  param9_t  _p9, param10_t _p10,
                         param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14 );
        return this->onUnknownType(_id);
    }

    //
    OBJ_T* create( const ID_T& _id,
                         param1_t  _p1,  param2_t  _p2,  param3_t  _p3,  param4_t  _p4,  param5_t  _p5,
                         param6_t  _p6,  param7_t  _p7,  param8_t  _p8,  param9_t  _p9,  param10_t _p10,
                         param11_t _p11, param12_t _p12, param13_t _p13, param14_t _p14, param15_t _p15 )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).first( _p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15 );
        return this->onUnknownType(_id);
    }

    //
    result_t destroy( const ID_T& _id, OBJ_T* _pObject )
    {
        typename creator_map_t::iterator iter = base_t::m_CreatorMap.find(_id);
        if ( iter != base_t::m_CreatorMap.end() )
            return (*iter).second(_pObject);
        this->onUnknownType(_id);
        return EResult::not_found;
    }
}; // end class FactoryManageDestrct




// TODO: need this ?
#if 0
/**
*   \defgroup	CloneFactoryGroup clone Factory
*   \ingroup	FactoriesGroup
*   \brief		Creates a copy from a polymorphic object.
*
*   \class		CloneFactory
*   \ingroup	CloneFactoryGroup
*   \brief		Creates a copy from a polymorphic object.
*/

template
<
    class OBJ_T,
    class ProductCreator =
        OBJ_T* (*)(const OBJ_T*),
    template<typename, class>
        class FactoryErrorPolicy = DefaultFactoryError
>
class CloneFactory
    : public FactoryErrorPolicy<TypeInfo, OBJ_T>
{
public:
    bool reg(const TypeInfo& ti, ProductCreator creator)
    {
        return associations_.insert(
            typename IdToProductMap::value_type(ti, creator)).second != 0;
    }

    bool unreg(const TypeInfo& id)
    {
        return associations_.erase(id) != 0;
    }

    OBJ_T* create(const OBJ_T* model)
    {
        if (model == NULL)
        {
            return NULL;
        }

        typename IdToProductMap::iterator i = 
            associations_.find(typeid(*model));
            
        if (i != associations_.end())
        {
            return (i->second)(model);
        }
        return this->onUnknownType(typeid(*model));
    }

private:
    typedef AssocVector<TypeInfo, ProductCreator> IdToProductMap;
    IdToProductMap associations_;
};
#endif
        
// #########################
} // end namespace ex 
// #########################


#if 0
#ifdef _MSC_VER
#pragma warning( pop )
#endif
#endif

// #################################################################################
#endif // END FACTORY_H_1250525421
// #################################################################################

