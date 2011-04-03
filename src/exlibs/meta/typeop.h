// ======================================================================================
// File         : typeop.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 00:11:42 AM | Sunday,August
// Description  : 
// ======================================================================================

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
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #################################################################################
#ifndef TYPEOP_H_1250525357
#define TYPEOP_H_1250525357
// #################################################################################

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------
// Desc: EmptyType  
//  Used as a class type that doesn't hold anything
//  Useful as a strawman class
// ------------------------------------------------------------------

//
class EmptyType {}; // end class EmptyType
INLINE bool operator == ( const EmptyType&, const EmptyType& ) { return true; }   
INLINE bool operator < ( const EmptyType&, const EmptyType& ) { return false; }
INLINE bool operator > ( const EmptyType&, const EmptyType& ) { return false; }

// ------------------------------------------------------------------
// Desc: NullType 
//  Used as a placeholder for "no type here"
//  Useful as an end marker in typelists 
// ------------------------------------------------------------------

//
class NullType {}; // end class NullType

// ------------------------------------------------------------------ 
// Desc: InvalidType 
//   This is used in TypeTraits, for trying generate a new type from
//   original one, but the type is illegal. for example a reference pointer ==> T&*
// ------------------------------------------------------------------ 

class InvalidType {}; // end class InvalidType

// ------------------------------------------------------------------
// Desc: Converts each integral constant into a unique type
//     Invocation: intToType<v> where v is a compile-time constant integral
//     Defines 'value', an enum that evaluates to v
// ------------------------------------------------------------------

// ========================================================
// intToType
// ========================================================

template < int VALUE >
struct intToType
{
    enum { value = VALUE };
}; // end struct intToType

// ========================================================
// uintToType
// ========================================================

template < uint VALUE >
struct uintToType
{
    enum { value = VALUE };
}; // end struct uintToType

// ------------------------------------------------------------------
// Desc: Converts each type into a unique, insipid type
//     Invocation TypeToType<T> where T is a type
//     Defines the type original_t which maps back to T
// ------------------------------------------------------------------

template < typename T >
struct TypeToType
{
    typedef T original_t;
}; // end struct TypeToType

///////////////////////////////////////////////////////////////////////////////
// namespace typeop functions
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace typeop { 
// ######################### 

// ------------------------------------------------------------------
// Desc: Selects one of two types based upon a boolean constant
//     Invocation: typeop::Select<flag, T, U>::result_t
//     where:
//     flag is a compile-time boolean constant
//     T and U are types
//     Result evaluates to T if flag is true, and to U otherwise.
// ------------------------------------------------------------------

// ========================================================
// general
// ========================================================

template < bool FLAG, typename T, typename U >
struct Select
{
    typedef T result_t;
}; // end struct Select

// ========================================================
// false
// ========================================================

template <typename T, typename U>
struct Select<false, T, U>
{
    typedef U result_t;
}; // end struct Select<false>

// ------------------------------------------------------------------
// Desc: Return true if two given types are the same
//     Invocation: typeop::IsSameType<T, U>::value
//     where:
//     T and U are types
//     Result evaluates to true iff U == T (types equal)
// ------------------------------------------------------------------

// ========================================================
// general
// ========================================================

template < typename T, typename U >
struct IsSameType
{
    enum { Result = false };
}; // end struct IsSameType

// ========================================================
// SAME
// ========================================================

template < typename T >
struct IsSameType<T,T>
{
    enum { Result = true };
}; // end struct IsSameType<T,T>

#if 0
// ------------------------------------------------------------------
// Desc: Return true if the type is atomic type
// ------------------------------------------------------------------

// ========================================================
// General Type 
// ========================================================

template < typename T > struct IsAtomicType { enum { Result = false }; }; // T

// ========================================================
// Special Type
// ========================================================

template <> struct IsAtomicType<int8>   { enum { Result = true }; }; // int8
template <> struct IsAtomicType<int16>  { enum { Result = true }; }; // int16
template <> struct IsAtomicType<int32>  { enum { Result = true }; }; // int32
template <> struct IsAtomicType<int64>  { enum { Result = true }; }; // int64
template <> struct IsAtomicType<uint8>  { enum { Result = true }; }; // uint8
template <> struct IsAtomicType<uint16> { enum { Result = true }; }; // uint16
template <> struct IsAtomicType<uint32> { enum { Result = true }; }; // uint32
template <> struct IsAtomicType<uint64> { enum { Result = true }; }; // uint64
template <> struct IsAtomicType<float>  { enum { Result = true }; }; // float
template <> struct IsAtomicType<double> { enum { Result = true }; }; // double
template <> struct IsAtomicType<char>   { enum { Result = true }; }; // char
template <> struct IsAtomicType<wchar>  { enum { Result = true }; }; // wchar

// ------------------------------------------------------------------
// Desc: return true if the type is a pointer
// ------------------------------------------------------------------

// ========================================================
// General Type 
// ========================================================

template < typename T > struct IsPointer { enum { Result = false }; }; // T

// ========================================================
// Special Type
// ========================================================

template < typename T > struct IsPointer<T*>   { enum { Result = true }; }; // T*

// ------------------------------------------------------------------
// Desc: return true if the type is a void* 
// ------------------------------------------------------------------

// ========================================================
// General Type 
// ========================================================

template < typename T > struct IsVoidPointer { enum { Result = false }; }; // T

// ========================================================
// Special Type
// ========================================================

template <> struct IsVoidPointer<void*>   { enum { Result = true }; }; // void*

// ------------------------------------------------------------------
// Desc: Return true if the type is char/wchar
// ------------------------------------------------------------------

// ========================================================
// General Type
// ========================================================

template < typename T > struct IsCharacterType { enum { Result = false }; }; // T

// ========================================================
// Special Type
// ========================================================

template <> struct IsCharacterType<char>  { enum { Result = true }; }; // char
template <> struct IsCharacterType<wchar> { enum { Result = true }; }; // wchar

// ------------------------------------------------------------------
// Desc: Return true if the type is unsinged type
// ------------------------------------------------------------------

// ========================================================
// Gerneral Type
// ========================================================

template < typename T > struct IsUnsingedType { enum { Result = false }; }; // T

// ========================================================
// Special Type
// ========================================================

template <> struct IsUnsingedType<uint8>  { enum { Result = true }; }; // uint8
template <> struct IsUnsingedType<uint16> { enum { Result = true }; }; // uint16
template <> struct IsUnsingedType<uint32> { enum { Result = true }; }; // uint32
template <> struct IsUnsingedType<uint64> { enum { Result = true }; }; // uint64

// ------------------------------------------------------------------
// Desc: Return true if the type is need construct
// ------------------------------------------------------------------

// ========================================================
// 
// ========================================================

template < typename T > struct TNeedConstruct { enum { Result = ( ( IsAtomicType<T>==false)&&(IsPointer<T>==false) ) }; }; // T
#endif

// ------------------------------------------------------------------
// Desc: This meta-func will help to always return a type even if 
//      the template-parameter is a point
// ------------------------------------------------------------------

template < typename T > struct PointerToType     { typedef T type_t; }; // end struct TPointerToType
template < typename T > struct PointerToType<T*> { typedef T type_t; }; // end struct TPointerToType<T*>
template < typename T > struct PointerToType<T&> { typedef T type_t; }; // end struct TPointerToType<T&>

// ------------------------------------------------------------------
// Desc: This meta-func will help to always return a point even if 
//  the template-parameter is a type
// ------------------------------------------------------------------

template < typename T > struct TypeToPointer     { typedef T* type_t; }; // end struct TTypeToPointer
template < typename T > struct TypeToPointer<T*> { typedef T* type_t; }; // end struct TTypeToPointer<T*>
template < typename T > struct TypeToPointer<T&> { typedef T* type_t; }; // end struct TTypeToPointer<T&>

// ------------------------------------------------------------------
// Desc: ref -> type
// ------------------------------------------------------------------

template < typename T > struct RefToType     { typedef T& type_t; }; // end struct TRefToType
template < typename T > struct RefToType<T*> { typedef T& type_t; }; // end struct TRefToType<T*>
template < typename T > struct RefToType<T&> { typedef T& type_t; }; // end struct TRefToType<T&>

// ------------------------------------------------------------------
// Desc: type -> ref 
// ------------------------------------------------------------------

template < typename T > struct TypeToRef        { typedef T& type_t; }; // end struct TTypeToRef
template < typename T > struct TypeToRef<T*>    { typedef T& type_t; }; // end struct TTypeToRef<T*>
template < typename T > struct TypeToRef<T&>    { typedef T& type_t; }; // end struct TTypeToRef<T&>
template <>             struct TypeToRef<void> { typedef NullType type_t; }; // end struct TTypeToRef<void>

// ------------------------------------------------------------------
// Desc: type -> param 
// ------------------------------------------------------------------

template < typename T > struct TypeToParam          { typedef const T& type_t; }; // end struct TTypeToParam
template < typename T > struct TypeToParam<T&>      { typedef T& type_t; }; // end struct TTypeToParam<T&>
template <>             struct TypeToParam<void>    { typedef NullType type_t; }; // end struct TTypeToParam<void>

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// #########################
namespace _private {
// #########################

    ///////////////////////////////////////////////////////////////////////////////
    // class ConversionHelper 
    //  
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template < typename T, typename U >
    struct ConversionHelper
    {
        struct Big { uint8 dummy[2]; };
        typedef uint8 small_t;
        typedef Big big_t;

        static big_t    Test(...);
        static small_t  Test(U);
        static T        MakeT();
    }; // end struct ConversionHelper

// #########################
} // end namespace _private
// #########################

// ------------------------------------------------------------------
// Desc: 
//     Figures out the conversion relationships between two types
//     Invocations (T and U are types):
//     a) Conversion<T, U>::Exists
//     returns (at compile time) true if there is an implicit conversion from T
//     to U (example: Derived to Base)
//     b) Conversion<T, U>::Exists2Way
//     returns (at compile time) true if there are both conversions from T
//     to U and from U to T (example: int to char and back)
//     c) Conversion<T, U>::IsSameType
//     returns (at compile time) true if T and U represent the same type
//
//     Caveat: might not work if T and U are in a private inheritance hierarchy.
// ------------------------------------------------------------------

// ========================================================
// general 
// ========================================================

template < typename T, typename U >
struct Conversion
{
    typedef ex::typeop::_private::ConversionHelper<T,U> helper_t;
    enum { Exists = sizeof(typename helper_t::small_t) == sizeof((helper_t::Test(helper_t::MakeT()))) };
    enum { Exists2Way = Exists && Conversion<U,T>::Exists };
    enum { IsSameType = false };
}; // end struct Conversion

// ========================================================
// <T,T>
// ========================================================

template < typename T >
struct Conversion<T,T>
{
    enum { Exists = true, Exists2Way = true, IsSameType = true };
}; // end struct Conversion<T,T>

// ========================================================
// <void,T>
// ========================================================

template < typename T >
struct Conversion<void,T>
{
    enum { Exists = false, Exists2Way = false, IsSameType = false };
}; // end struct Conversion<void,T>

// ========================================================
// <T,void>
// ========================================================

template < typename T >
struct Conversion<T,void>
{
    enum { Exists = false, Exists2Way = false, IsSameType = false };
}; // end struct Conversion<T,void>

// ========================================================
// <void,void>
// ========================================================

template <>
struct Conversion<void,void>
{
    enum { Exists = true, Exists2Way = true, IsSameType = true };
}; // end struct Conversion<void,void>


// ------------------------------------------------------------------
// Desc: 
//     Invocation: SuperSubclass<B, D>::value where B and D are types. 
//     Returns true if B is a public base of D, or if B and D are aliases of the 
//     same type.
//
//     Caveat: might not work if T and U are in a private inheritance hierarchy.
// ------------------------------------------------------------------

// ========================================================
// genreal 
// ========================================================

template < typename T, typename U >
struct IsSuperSubClass
{
    enum { Result = ( Conversion<const volatile U*, const volatile T*>::Exists &&
                     !Conversion<const volatile T*, const volatile void*>::IsSameType ) };
      
    // Dummy enum to make sure that both classes are fully defined.
    enum { DontUseWithIncompleteTypes = ( sizeof (T) == sizeof (U) ) };
}; // end struct IsSuperSubClass<T,U>

// ========================================================
// <void,void>
// ========================================================

template <>
struct IsSuperSubClass<void,void> 
{
    enum { Result = false };
}; // end struct IsSuperSubClass<void,void>

// ========================================================
// <void,U>
// ========================================================

template < typename U >
struct IsSuperSubClass<void,U> 
{
    enum { Result = ( Conversion<const volatile U*, const volatile void*>::Exists &&
                     !Conversion<const volatile void*, const volatile void*>::IsSameType ) };
      
    // Dummy enum to make sure that both classes are fully defined.
    enum { DontUseWithIncompleteTypes = ( 0 == sizeof (U) ) };
}; // end struct IsSuperSubClass<void,U>

// ========================================================
// <T,void>
// ========================================================

template <class T>
struct IsSuperSubClass<T,void> 
{
    enum { Result = ( Conversion<const volatile void*, const volatile T*>::Exists &&
                     !Conversion<const volatile T*, const volatile void*>::IsSameType ) };
      
    // Dummy enum to make sure that both classes are fully defined.
    enum { DontUseWithIncompleteTypes = ( sizeof (T) == 0 ) };
}; // end struct IsSuperSubClass<T,void>

// ------------------------------------------------------------------
// Desc: 
//     Invocation: SuperSubclassStrict<B, D>::value where B and D are types. 
//     Returns true if B is a public base of D.
//
//     Caveat: might not work if T and U are in a private inheritance hierarchy.
// ------------------------------------------------------------------

// ========================================================
// general 
// ========================================================

template< typename T, typename U >
struct IsSuperSubClassStrict
{
    enum { Result = ( Conversion<const volatile U*, const volatile T*>::Exists &&
                     !Conversion<const volatile T*, const volatile void*>::IsSameType &&
                     !Conversion<const volatile T*, const volatile U*>::IsSameType ) };
    
    // Dummy enum to make sure that both classes are fully defined.
    enum { DontUseWithIncompleteTypes = ( sizeof (T) == sizeof (U) ) };
};

// ========================================================
// <void,void>
// ========================================================

template<>
struct IsSuperSubClassStrict<void,void> 
{
    enum { Result = false };
}; // end struct IsSuperSubClassStrict<void,void>

// ========================================================
// <void,U>
// ========================================================

template<class U>
struct IsSuperSubClassStrict<void,U> 
{
    enum { Result = ( Conversion<const volatile U*, const volatile void*>::Exists &&
                     !Conversion<const volatile void*, const volatile void*>::IsSameType &&
                     !Conversion<const volatile void*, const volatile U*>::IsSameType ) };
    
    // Dummy enum to make sure that both classes are fully defined.
    enum { DontUseWithIncompleteTypes = ( 0 == sizeof (U) ) };
}; // end struct IsSuperSubClassStrict<void,U>

// ========================================================
// <T,void>
// ========================================================

template<class T>
struct IsSuperSubClassStrict<T,void> 
{
    enum { Result = ( Conversion<const volatile void*, const volatile T*>::Exists &&
                     !Conversion<const volatile T*, const volatile void*>::IsSameType &&
                     !Conversion<const volatile T*, const volatile void*>::IsSameType ) };
    
    // Dummy enum to make sure that both classes are fully defined.
    enum { DontUseWithIncompleteTypes = ( sizeof (T) == 0 ) };
}; // end struct IsSuperSubClassStrict<T,void>

// ######################### 
} // end namespace typeop 
// ######################### 


// #########################
} // end namespace ex 
// #########################

// ------------------------------------------------------------------
// Desc: 
//     Invocation: EX_IS_SUPERSUB_CLASS(B, D) where B and D are types. 
//     Returns true if B is a public base of D, or if B and D are aliases of the 
//     same type.
//
//     Caveat: might not work if T and U are in a private inheritance hierarchy.
//     Deprecated: Use SuperSubclass class template instead.
// ------------------------------------------------------------------

#define EX_IS_SUPERSUB_CLASS(T, U) ::ex::typeop::IsSuperSubClass<T,U>::Result

// ------------------------------------------------------------------
// Desc: 
//     Invocation: EX_IS_SUPERSUB_CLASS_STRICT(B, D) where B and D are types. 
//     Returns true if B is a public base of D.
//
//     Caveat: might not work if T and U are in a private inheritance hierarchy.
//     Deprecated: Use SuperSubclassStrict class template instead.
// ------------------------------------------------------------------

#define EX_IS_SUPERSUB_CLASS_STRICT(T, U) ::ex::typeop::IsSuperSubClassStrict<T,U>::Result

// #################################################################################
#endif // END TYPEOP_H_1250525357
// #################################################################################
