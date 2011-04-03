// ======================================================================================
// File         : FromString.hpp
// Author       : Wu Jie 
// Last Change  : 09/23/2009 | 21:52:43 PM | Wednesday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// from_str
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private { 
// #########################

    // ------------------------------------------------------------------
    // Desc: T_ObjFromString
    // ------------------------------------------------------------------

    // true
    template < typename T >
    void T_ObjFromString( const char* _str, T* _pObj, intToType<true> ) { return _pObj->FromString(_str); }

    // false
    template < typename T >
    void T_ObjFromString( const char* _str, T* _pObj, intToType<false> ) {}

// #########################
} // end namespace _private 
// #########################

// ========================================================
// general
// ========================================================

template < typename T >
INLINE void from_str( const char* _str, T* _pObj ) 
{
    if ( TypeTraits<T>::isPointer )
        ex_assert ( false, "type can't be a pointer." );
    else
        _private::T_ObjFromString<T>( _str, _pObj, intToType< TypeTraits<T>::isPointer!=true >() );
}

// ========================================================
// atomic
// ========================================================

// ------------------------------------------------------------------ 
// Desc: bool
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, bool* _pObj )           
{
    if ( str::icmp ( _str, "true" ) == 0 )
    {
        *_pObj = true; 
    }
    else if ( str::icmp ( _str, "false" ) == 0 )
    {
        *_pObj = false; 
    }
    else
    {
        *_pObj = (str::ato<int> ( _str ) != 0);
    }
}

// ------------------------------------------------------------------ 
// Desc: char
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, char* _pObj )           
{
    *_pObj = str::ato<char> (_str);
}

// ------------------------------------------------------------------ 
// Desc: uint8
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, uint8* _pObj )           
{
    *_pObj = str::ato<uint8> (_str);
}

// ------------------------------------------------------------------ 
// Desc: int8
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, int8* _pObj )           
{
    *_pObj = str::ato<int8> (_str);
}

// ------------------------------------------------------------------ 
// Desc: uint16
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, uint16* _pObj )           
{
    *_pObj = str::ato<uint16> (_str);
}

// ------------------------------------------------------------------ 
// Desc: int16
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, int16* _pObj )           
{
    *_pObj = str::ato<int16> (_str);
}

// ------------------------------------------------------------------ 
// Desc: uint32
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, uint32* _pObj )           
{
    *_pObj = str::ato<uint32> (_str);
}

// ------------------------------------------------------------------ 
// Desc: int32
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, int32* _pObj )           
{
    *_pObj = str::ato<int32> (_str);
}

// ------------------------------------------------------------------ 
// Desc: uint64
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, uint64* _pObj )           
{
    *_pObj = str::ato<uint64> (_str);
}

// ------------------------------------------------------------------ 
// Desc: int64
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, int64* _pObj )           
{ 
    *_pObj = str::ato<int64> (_str);
}

// DISABLE { 
// // ------------------------------------------------------------------ 
// // Desc: uint 
// // ------------------------------------------------------------------ 

// template <>
// INLINE void from_str ( const char* _str, uint* _pObj )           
// {
//     *_pObj = str::ato<uint> (_str);
// }

// // ------------------------------------------------------------------ 
// // Desc: int
// // ------------------------------------------------------------------ 

// template <>
// INLINE void from_str ( const char* _str, int* _pObj )           
// {
//     *_pObj = str::ato<int> (_str);
// }
// } DISABLE end 

// ------------------------------------------------------------------ 
// Desc: float
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, float* _pObj )           
{
    *_pObj = str::ato<float> (_str);
}

// ------------------------------------------------------------------ 
// Desc: double 
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, double* _pObj )           
{
    *_pObj = str::ato<double> (_str);
}

// ------------------------------------------------------------------ 
// Desc: const char* 
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, const char** _pObj )     
{
    *_pObj = _str;
}

// ------------------------------------------------------------------ 
// Desc: const wchar* 
// ------------------------------------------------------------------ 

template <>
INLINE void from_str ( const char* _str, const wchar** _pObj )     
{
    utf8_to_utf16(_str, const_cast<wchar*>(*_pObj)); 
}
