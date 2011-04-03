// ======================================================================================
// File         : to_str.hpp
// Author       : Wu Jie 
// Last Change  : 09/23/2009 | 21:51:18 PM | Wednesday,September
// Description  : 
// ======================================================================================

// ------------------------------------------------------------------ 
// Desc: Flags 
// ------------------------------------------------------------------ 

const uint dec = 0x01 << 0;
const uint hex = 0x01 << 1;

///////////////////////////////////////////////////////////////////////////////
// to_str
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private { 
// #########################

    // ------------------------------------------------------------------
    // Desc: ptr_to_str 
    // ------------------------------------------------------------------

    // true
    template < uint FLAGS, typename T >
    string_t ptr_to_str( const T _obj, intToType<true> ) 
    { 
        if ( FLAGS == (dec|hex) )
            return string_t().printf( "%lu(%#.8lX)",uint32((size_t)_obj),uint32((size_t)_obj) ); 
        else if ( FLAGS == dec )
            return string_t().printf( "%lu",uint32((size_t)_obj) ); 
        else if ( FLAGS == hex )
            return string_t().printf( "%#.8lX",uint32((size_t)_obj) ); 

        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        return string_t().printf( "%lu(%#.8lX)",uint32((size_t)_obj),uint32((size_t)_obj) ); 
    }

    // false
    template < uint FLAGS, typename T >
    string_t ptr_to_str( const T _obj, intToType<false> ) { return "dummy function"; }

    // ------------------------------------------------------------------
    // Desc: obj_to_str
    // ------------------------------------------------------------------

    // NOTE: in template function below, const T& obj,
    // instead of write "obj.Func<FLAGS>()" we write "obj.template Func<FLAGS>()";
    // Since obj is dependent, we are not expecting Func to be a template so it parses
    // as a non template and then errors out as a<0 () is invalid for anything
    // except a template.

    // true
    template < uint FLAGS, typename T >
    string_t obj_to_str( const T& _obj, intToType<true> ) { return _obj.template to_str< FLAGS > (); }

    // false
    template < uint FLAGS, typename T >
    string_t obj_to_str( const T& _obj, intToType<false> ) { return "dummy function"; }

// #########################
} // end namespace _private 
// #########################

// ========================================================
// general
// ========================================================

template < uint FLAGS, typename T >
INLINE string_t to_str( const T& _obj ) 
{
    if ( TypeTraits<T>::isPointer )
        return _private::ptr_to_str<FLAGS,T>( _obj, intToType< TypeTraits<T>::isPointer >() );
    else
        return _private::obj_to_str<FLAGS,T>( _obj, intToType< TypeTraits<T>::isPointer!=true >() );
}

// ========================================================
// atomic
// ========================================================

// ------------------------------------------------------------------ 
// Desc: bool
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( bool _obj )           
{
    string_t strValue; 

    //
    if ( _obj )
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

// ------------------------------------------------------------------ 
// Desc: uint8
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( uint8 _obj )           
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%hhu(%#.2hhX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%hhu",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.2hhX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%hhu(%#.2hhX)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: int8
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( int8 _obj )            
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%hhd(%#.2hhX)",_obj,(uint8)_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%hhd",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.2hhX",(uint8)_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%hhd(%#.2hhX)",_obj,(uint8)_obj); 
}

// ------------------------------------------------------------------ 
// Desc: uint16
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( uint16 _obj )          
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%hu(%#.4hX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%hu",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.4hX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%hu(%#.4hX)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: int16
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( int16 _obj )           
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%hd(%#.4hX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%hd",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.4hX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%hd(%#.4hX)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: uint32
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( uint32 _obj )          
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%lu(%#.8lX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%lu",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.8lX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%lu(%#.8lX)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: int32
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( int32 _obj )           
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%ld(%#.8lX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%ld",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.8lX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%ld(%#.8lX)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: uint64
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( uint64 _obj )          
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%llu(%#.16llX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%llu",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.16llX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%llu(%#.16llX)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: int64
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( int64 _obj )           
{ 
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%lld(%#.16llX)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%lld",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.16llX",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%lld(%#.16llX)",_obj,_obj); 
}

// DISABLE { 
// // ------------------------------------------------------------------ 
// // Desc: uint 
// // ------------------------------------------------------------------ 

// template < uint FLAGS >
// INLINE string_t to_str ( uint _obj )            
// {
//     if ( FLAGS == (dec|hex) )
//         return string_t().printf("%lu(%#.8lX)",_obj,_obj); 
//     else if ( FLAGS == dec )
//         return string_t().printf("%lu",_obj); 
//     else if ( FLAGS == hex )
//         return string_t().printf("%#.8lX",_obj); 

//     ex_assert ( false, "FLAGS = %i not found!", FLAGS );
//     return string_t().printf("%lu(%#.8lX)",_obj,_obj); 
// }

// // ------------------------------------------------------------------ 
// // Desc: int
// // ------------------------------------------------------------------ 

// template < uint FLAGS >
// INLINE string_t to_str ( int _obj )             
// {
//     if ( FLAGS == (dec|hex) )
//         return string_t().printf("%ld(%#.8lX)",_obj,_obj); 
//     else if ( FLAGS == dec )
//         return string_t().printf("%ld",_obj); 
//     else if ( FLAGS == hex )
//         return string_t().printf("%#.8lX",_obj); 

//     ex_assert ( false, "FLAGS = %i not found!", FLAGS );
//     return string_t().printf("%ld(%#.8lX)",_obj,_obj); 
// }
// } DISABLE end 

// ------------------------------------------------------------------ 
// Desc: float
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( float _obj )           
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%f(%#.8A)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%f",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.8A",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%f(%#.8A)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: double 
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( double _obj )          
{
    if ( FLAGS == (dec|hex) )
        return string_t().printf("%f(%#.16A)",_obj,_obj); 
    else if ( FLAGS == dec )
        return string_t().printf("%f",_obj); 
    else if ( FLAGS == hex )
        return string_t().printf("%#.16A",_obj); 

    ex_assert ( false, "FLAGS = %i not found!", FLAGS );
    return string_t().printf("%f(%#.16A)",_obj,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: const char* 
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( const char* _obj )     
{
    return _obj; 
}

// ------------------------------------------------------------------ 
// Desc: const wchar* 
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( const wchar* _obj )    
{
    char* utf8 = (char*)ex_stack_malloc( ex::str::len(_obj) * sizeof(wchar) );
    utf16_to_utf8( _obj, utf8 );
    string_t str;
    str.assign(utf8); 
    return str;
}

// ------------------------------------------------------------------ 
// Desc: string_t 
// ------------------------------------------------------------------ 

template < uint FLAGS >
INLINE string_t to_str ( const string_t& _obj ) 
{
    return _obj; 
}

///////////////////////////////////////////////////////////////////////////////
// get_str
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// atomic
// ========================================================

// ------------------------------------------------------------------ 
// Desc: uint8 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( uint8 _obj, String<char,TAllocator_T>* _pString )           
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%hhu(%#.2hhX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%hhu",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.2hhX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%hhu(%#.2hhX)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: int8 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( int8 _obj, String<char,TAllocator_T>* _pString )            
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%hhd(%#.2hhX)",_obj,(uint8)_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%hhd",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.2hhX",(uint8)_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%hhd(%#.2hhX)",_obj,(uint8)_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: uint16 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( uint16 _obj, String<char,TAllocator_T>* _pString )          
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%hu(%#.4hX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%hu",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.4hX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%hu(%#.4hX)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: int16 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( int16 _obj, String<char,TAllocator_T>* _pString )           
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%hd(%#.4hX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%hd",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.4hX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%hd(%#.4hX)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: uint32 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( uint32 _obj, String<char,TAllocator_T>* _pString )          
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%lu(%#.8lX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%lu",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.8lX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%lu(%#.8lX)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: int32 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( int32 _obj, String<char,TAllocator_T>* _pString )           
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%ld(%#.8lX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%ld",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.8lX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%ld(%#.8lX)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: uint64 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( uint64 _obj, String<char,TAllocator_T>* _pString )          
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%llu(%#.16llX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%llu",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.16llX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%llu(%#.16llX)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: int64 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( int64 _obj, String<char,TAllocator_T>* _pString )           
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%lld(%#.16llX)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%lld",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.16llX",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%lld(%#.16llX)",_obj,_obj); 
    }
}

// DISABLE { 
// // ------------------------------------------------------------------ 
// // Desc: uint 
// // ------------------------------------------------------------------ 

// template < uint FLAGS, template <class> class TAllocator_T >
// INLINE void get_str ( uint _obj, String<char,TAllocator_T>* _pString )            
// {
//     if ( FLAGS == (dec|hex) )
//         _pString->printf("%lu(%#.8lX)",_obj,_obj); 
//     else if ( FLAGS == dec )
//         _pString->printf("%lu",_obj); 
//     else if ( FLAGS == hex )
//         _pString->printf("%#.8lX",_obj); 
//     else
//     {
//         ex_assert ( false, "FLAGS = %i not found!", FLAGS );
//         _pString->printf("%lu(%#.8lX)",_obj,_obj); 
//     }
// }

// // ------------------------------------------------------------------ 
// // Desc: int 
// // ------------------------------------------------------------------ 

// template < uint FLAGS, template <class> class TAllocator_T >
// INLINE void get_str ( int _obj, String<char,TAllocator_T>* _pString )             
// {
//     if ( FLAGS == (dec|hex) )
//         _pString->printf("%ld(%#.8lX)",_obj,_obj); 
//     else if ( FLAGS == dec )
//         _pString->printf("%ld",_obj); 
//     else if ( FLAGS == hex )
//         _pString->printf("%#.8lX",_obj); 
//     else
//     {
//         ex_assert ( false, "FLAGS = %i not found!", FLAGS );
//         _pString->printf("%ld(%#.8lX)",_obj,_obj); 
//     }
// }
// } DISABLE end 

// ------------------------------------------------------------------ 
// Desc: float 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( float _obj, String<char,TAllocator_T>* _pString )           
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%f(%#.8A)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%f",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.8A",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%f(%#.8A)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: double
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( double _obj, String<char,TAllocator_T>* _pString )          
{
    if ( FLAGS == (dec|hex) )
        _pString->printf("%f(%#.16A)",_obj,_obj); 
    else if ( FLAGS == dec )
        _pString->printf("%f",_obj); 
    else if ( FLAGS == hex )
        _pString->printf("%#.16A",_obj); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf("%f(%#.16A)",_obj,_obj); 
    }
}

// ------------------------------------------------------------------ 
// Desc: char 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( char _obj, String<char,TAllocator_T>* _pString )            
{
    _pString->assign(1,_obj); 
}

// ------------------------------------------------------------------ 
// Desc: const char* 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( const char* _obj, String<char,TAllocator_T>* _pString )     
{
    _pString->assign(_obj); 
}

// ------------------------------------------------------------------ 
// Desc: const wchar* 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( const wchar* _obj, String<char,TAllocator_T>* _pString )    
{
    char* utf8 = (char*)ex_stack_malloc( ex::str::len(_obj) * sizeof(wchar) );
    utf16_to_utf8( _obj, utf8 );
    _pString->assign(utf8); 
}

// ------------------------------------------------------------------ 
// Desc: const void* 
// ------------------------------------------------------------------ 

template < uint FLAGS, template <class> class TAllocator_T >
INLINE void get_str ( const void* _obj, String<char,TAllocator_T>* _pString ) 
{
    if ( FLAGS == (dec|hex) )
        _pString->printf( "%lu(%#.8lX)", uint32((size_t)_obj), uint32((size_t)_obj) ); 
    else if ( FLAGS == dec )
        _pString->printf( "%lu", uint32((size_t)_obj) ); 
    else if ( FLAGS == hex )
        _pString->printf( "%#.8lX", uint32((size_t)_obj) ); 
    else
    {
        ex_assert ( false, "FLAGS = %i not found!", FLAGS );
        _pString->printf( "%lu(%#.8lX)", uint32((size_t)_obj), uint32((size_t)_obj) ); 
    }
}

