// ======================================================================================
// File         : property_helpers.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 15:37:49 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTY_HELPERS_H_1281857871
#define PROPERTY_HELPERS_H_1281857871
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// PropertyEqualSelector
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// 0: others
template < typename T >
bool PropertyEqualSelector( T* _lhs, T* _rhs, intToType<0> ) {
    return false;
}

// 1: atomic || string || enum
// generic
template < typename T >
bool PropertyEqualSelector( T* _lhs, T* _rhs, intToType<1> ) {
    return ex::mathop::is_equal<T> ( *_lhs, *_rhs );
}

// const char*
template <>
INLINE bool PropertyEqualSelector( const char* _lhs, const char* _rhs, intToType<1> ) {
    return ex::str::cmp(_lhs,_rhs) == 0;
}

///////////////////////////////////////////////////////////////////////////////
// class PropertyGetSet
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// PropertyGetSet<T>
// ======================================================== 

template < typename T >
class PropertyGetSet
{
public:

    INLINE void operator () ( T* _pResult, T* _pValue ) const
    {
        *_pResult = *_pValue;
        // BUG: this will have memory-violation if the T is CEngineObject.
        // if user write CEngineObject engObj; spInstance->Get(&engObj);
    }
}; // end class PropertyGetSet

// ======================================================== 
// PropertyGetSet<T[SIZE]>
// ======================================================== 

template < typename T, uint SIZE >
class PropertyGetSet<T[SIZE]>
{
public:

    INLINE void operator () ( T (*_pResult)[SIZE], T (*_pValue)[SIZE] ) const
    {
        typedef T static_array_t[SIZE];
        ex::mem::cpy ( _pResult, _pValue, SIZE );
    }
}; // end class PropertyGetSet<T[SIZE]>

// ======================================================== 
// PropertyGetSet<const char*>
// ======================================================== 

template <>
class PropertyGetSet<const char*>
{
public:

    INLINE void operator () ( const char** _pResult, const char** _pValue ) const
    {
        // this hack is co-respond with
        // .../serialization/XmlSerializeNode.cpp(603): result_t XmlSerializeNode::getAttr ( const char* _key, const char** _pValue ) const
        // .../serialization/BinarySerializeNode.cpp(635): result_t BinarySerializeNode::getAttr ( const char* _key, const char** _pValue ) const
        string_id_t sid (*_pValue);
        *_pResult = sid.c_str();
    }
}; // end class PropertyGetSet<const char*>

///////////////////////////////////////////////////////////////////////////////
// class PropertyMinMax
// 
// Purpose: 
//  the general PropertyMinMax won't do anything because if the type not defined
//  any opeartor >, < it will lead to compile error.
// 
///////////////////////////////////////////////////////////////////////////////

// ======================================================== 
// PropertyMinMax<T>
// ======================================================== 

template < typename T >
class PropertyMinMax
{
public:
    INLINE void operator () ( T** _pResult, T* _pValue, T* _pMin, T* _pMax ) const
    {
        EX_UNUSED (_pMin);
        EX_UNUSED (_pMax);
        *_pResult = _pValue;
    }
}; // end class PropertyMinMax

// ======================================================== 
// int8
// ======================================================== 

template <>
class PropertyMinMax<int8>
{
public:
    INLINE void operator () ( int8** _pResult, int8* _pValue, int8* _pMin, int8* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<int8>

// ======================================================== 
// uint8 
// ======================================================== 

template <>
class PropertyMinMax<uint8>
{
public:
    INLINE void operator () ( uint8** _pResult, uint8* _pValue, uint8* _pMin, uint8* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<uint8>

// ======================================================== 
// int16 
// ======================================================== 

template <>
class PropertyMinMax<int16>
{
public:
    INLINE void operator () ( int16** _pResult, int16* _pValue, int16* _pMin, int16* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<int16>

// ======================================================== 
// uint16 
// ======================================================== 

template <>
class PropertyMinMax<uint16>
{
public:
    INLINE void operator () ( uint16** _pResult, uint16* _pValue, uint16* _pMin, uint16* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<uint16>

// ======================================================== 
// int32 
// ======================================================== 

template <>
class PropertyMinMax<int32>
{
public:
    INLINE void operator () ( int32** _pResult, int32* _pValue, int32* _pMin, int32* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<int32>

// ======================================================== 
// uint32 
// ======================================================== 

template <>
class PropertyMinMax<uint32>
{
public:
    INLINE void operator () ( uint32** _pResult, uint32* _pValue, uint32* _pMin, uint32* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<uint32>

// ======================================================== 
// int64 
// ======================================================== 

template <>
class PropertyMinMax<int64>
{
public:
    INLINE void operator () ( int64** _pResult, int64* _pValue, int64* _pMin, int64* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<int64>

// ======================================================== 
// uint64 
// ======================================================== 

template <>
class PropertyMinMax<uint64>
{
public:
    INLINE void operator () ( uint64** _pResult, uint64* _pValue, uint64* _pMin, uint64* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<uint64>

// ======================================================== 
// float 
// ======================================================== 

template <>
class PropertyMinMax<float>
{
public:
    INLINE void operator () ( float** _pResult, float* _pValue, float* _pMin, float* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<float>

// ======================================================== 
// double 
// ======================================================== 

template <>
class PropertyMinMax<double>
{
public:
    INLINE void operator () ( double** _pResult, double* _pValue, double* _pMin, double* _pMax ) const
    {
        if ( _pMin && *_pValue < *_pMin )
            *_pResult = _pMin;
        else if ( _pMax && *_pValue > *_pMax )
            *_pResult = _pMax;
        else
            *_pResult = _pValue;
    }
}; // end class PropertyMinMax<double>

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROPERTY_HELPERS_H_1281857871
// #################################################################################
