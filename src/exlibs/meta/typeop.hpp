// ======================================================================================
// File         : Typeop.hpp
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:09:26 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TYPEOP_HPP_1250525368
#define TYPEOP_HPP_1250525368
// #################################################################################

// #########################
namespace ex { 
// #########################

// ######################### 
namespace typeop { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// type_name
///////////////////////////////////////////////////////////////////////////////

template < type_name T > INLINE const string_id_t& type_name ( const T& _val ) { return T::type_name(); }

// DISABLE: these function are disabled, pls use TypeTraits<T>::type_name instead { 
// NOTE: partical specialize not support for template function.

///////////////////////////////////////////////////////////////////////////////
// non-static array
///////////////////////////////////////////////////////////////////////////////

// // 
// template < type_name T > INLINE const string_id_t& type_name () { return T::type_name(); }

// // atomic
// template <> INLINE const string_id_t& type_name<bool> () { static const string_id_t strID("bool"); return strID; }
// template <> INLINE const string_id_t& type_name<int> () { static const string_id_t strID("int"); return strID; }
// template <> INLINE const string_id_t& type_name<uint> () { static const string_id_t strID("uint"); return strID; }

// template <> INLINE const string_id_t& type_name<int8> () { static const string_id_t strID("int8"); return strID; }
// template <> INLINE const string_id_t& type_name<int16> () { static const string_id_t strID("int16"); return strID; }
// template <> INLINE const string_id_t& type_name<int32> () { static const string_id_t strID("int32"); return strID; }
// template <> INLINE const string_id_t& type_name<int64> () { static const string_id_t strID("int64"); return strID; }
// template <> INLINE const string_id_t& type_name<uint8> () { static const string_id_t strID("uint8"); return strID; }
// template <> INLINE const string_id_t& type_name<uint16> () { static const string_id_t strID("uint16"); return strID; }
// template <> INLINE const string_id_t& type_name<uint32> () { static const string_id_t strID("uint32"); return strID; }
// template <> INLINE const string_id_t& type_name<uint64> () { static const string_id_t strID("uint64"); return strID; }
// template <> INLINE const string_id_t& type_name<float> () { static const string_id_t strID("float"); return strID; }
// template <> INLINE const string_id_t& type_name<double> () { static const string_id_t strID("double"); return strID; }

// // string
// template <> INLINE const string_id_t& type_name<char> () { static const string_id_t strID("char"); return strID; }
// template <> INLINE const string_id_t& type_name<wchar> () { static const string_id_t strID("wchar"); return strID; }
// template <> INLINE const string_id_t& type_name<const char*> () { static const string_id_t strID("c_str"); return strID; }
// template <> INLINE const string_id_t& type_name<const wchar*> () { static const string_id_t strID("w_str"); return strID; }

// ///////////////////////////////////////////////////////////////////////////////
// // static array
// ///////////////////////////////////////////////////////////////////////////////

// template < typename T, uint SIZE >
// INLINE const string_id_t& type_name () { static const string_id_t strID( type_name<T>().c_str() + "[" + to_str<dec>(SIZE) + "]" ); return strID; }

// template <,uint SIZE> INLINE const string_id_t& type_name<char[SIZE]> () { static const string_id_t strID("char" + "[" + to_str<dec>(SIZE) + "]"); return strID; }

// // atomic
// template <uint SIZE> INLINE const string_id_t& type_name<bool[SIZE]> () { static const string_id_t strID("bool" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<int[SIZE]> () { static const string_id_t strID("int" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<uint[SIZE]> () { static const string_id_t strID("uint" + "[" + to_str<dec>(SIZE) + "]"); return strID; }

// template <uint SIZE> INLINE const string_id_t& type_name<int8[SIZE]> () { static const string_id_t strID("int8" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<int16[SIZE]> () { static const string_id_t strID("int16" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<int32[SIZE]> () { static const string_id_t strID("int32" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<int64[SIZE]> () { static const string_id_t strID("int64" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<uint8[SIZE]> () { static const string_id_t strID("uint8" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<uint16[SIZE]> () { static const string_id_t strID("uint16" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<uint32[SIZE]> () { static const string_id_t strID("uint32" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<uint64[SIZE]> () { static const string_id_t strID("uint64" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<float[SIZE]> () { static const string_id_t strID("float" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// template <uint SIZE> INLINE const string_id_t& type_name<double[SIZE]> () { static const string_id_t strID("double" + "[" + to_str<dec>(SIZE) + "]"); return strID; }
// } DISABLE end 

// ######################### 
} // end namespace typeop 
// ######################### 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END TYPEOP_HPP_1250525368
// #################################################################################
