// ======================================================================================
// File         : TypeTraits.hpp
// Author       : Wu Jie 
// Last Change  : 08/19/2009 | 23:40:33 PM | Wednesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TYPETRAITS_HPP_1250696436
#define TYPETRAITS_HPP_1250696436
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// atomic
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// bool
// ======================================================== 

template <> class TypeTraits<bool> : public _private::TypeTraitsImpl<bool>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("bool"); return strID; }
}; // end class TypeTraits 

// DISABLE { 
// // ======================================================== 
// // int
// // ======================================================== 

// template <> class TypeTraits<int> : public _private::TypeTraitsImpl<int>
// {
// public:
//     static INLINE const string_id_t& type_name () { static const string_id_t strID("int"); return strID; }
// }; // end class TypeTraits 

// // ======================================================== 
// // uint
// // ======================================================== 

// template <> class TypeTraits<uint> : public _private::TypeTraitsImpl<uint>
// {
// public:
//     static INLINE const string_id_t& type_name () { static const string_id_t strID("uint"); return strID; }
// }; // end class TypeTraits 
// } DISABLE end 

// ======================================================== 
// int8
// ======================================================== 

template <> class TypeTraits<int8> : public _private::TypeTraitsImpl<int8>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("int8"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// int16
// ======================================================== 

template <> class TypeTraits<int16> : public _private::TypeTraitsImpl<int16>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("int16"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// int32
// ======================================================== 

template <> class TypeTraits<int32> : public _private::TypeTraitsImpl<int32>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("int32"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// int64
// ======================================================== 

template <> class TypeTraits<int64> : public _private::TypeTraitsImpl<int64>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("int64"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// uint8
// ======================================================== 

template <> class TypeTraits<uint8> : public _private::TypeTraitsImpl<uint8>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("uint8"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// uint16
// ======================================================== 

template <> class TypeTraits<uint16> : public _private::TypeTraitsImpl<uint16>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("uint16"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// uint32
// ======================================================== 

template <> class TypeTraits<uint32> : public _private::TypeTraitsImpl<uint32>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("uint32"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// uint64
// ======================================================== 

template <> class TypeTraits<uint64> : public _private::TypeTraitsImpl<uint64>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("uint64"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// float
// ======================================================== 

template <> class TypeTraits<float> : public _private::TypeTraitsImpl<float>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("float"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// double
// ======================================================== 

template <> class TypeTraits<double> : public _private::TypeTraitsImpl<double>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("double"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// char
// ======================================================== 

template <> class TypeTraits<char> : public _private::TypeTraitsImpl<char>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("char"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// const char*
// ======================================================== 

template <> class TypeTraits<const char*> : public _private::TypeTraitsImpl<const char*>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("c_str"); return strID; }
}; // end class TypeTraits 

// ======================================================== 
// const wchar*
// ======================================================== 

template <> class TypeTraits<const wchar*> : public _private::TypeTraitsImpl<const wchar*>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID("w_str"); return strID; }
}; // end class TypeTraits 

///////////////////////////////////////////////////////////////////////////////
// static array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class TypeTraits<T[SIZE]> 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, uint SIZE >
class TypeTraits<T[SIZE]> : public _private::TypeTraitsImpl<T[SIZE]>
{
public:
    static INLINE const string_id_t& type_name () { static const string_id_t strID( string_t( TypeTraits<T>::type_name().c_str() ) + "[" + to_str<dec>(SIZE) + "]" ); return strID; }
}; // end class TypeTraits 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END TYPETRAITS_HPP_1250696436
// #################################################################################

