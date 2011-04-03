// ======================================================================================
// File         : StrConvertor.hpp
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:26:19 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef STRCONVERTOR_HPP_1250526383
#define STRCONVERTOR_HPP_1250526383
// #################################################################################

// #########################
namespace ex { 
// #########################

// #########################
namespace _private {
// #########################

// ------------------------------------------------------------------
// Desc: TStrConvertor constructor char*
// ------------------------------------------------------------------

template <typename CHAR_TYPE_TO, uint32 SIZE>
INLINE TStrConvertor<CHAR_TYPE_TO, SIZE>::TStrConvertor( const char* _str )
{
    ex_static_assert( (TTypeTraits<CHAR_TYPE_TO>::IsCharacter), "T is not a character type" );
    if( typeop::IsSameType<CHAR_TYPE_TO,char>::Result ) // no need to convert the string
    {
        // this process have no meaning and just a dummy function here.
        // it just in case some stupid guys call the class 
        ex_warning( "This process should not be involked" );
    }
    else // need to convert the string
    {
        ConvertedString = (CHAR_TYPE_TO*)Convert(_str, (wchar*)Buffer);
    }
}

// ------------------------------------------------------------------
// Desc: TStrConvertor constructor wchar*
// ------------------------------------------------------------------

template <typename CHAR_TYPE_TO, uint32 SIZE>
INLINE TStrConvertor<CHAR_TYPE_TO, SIZE>::TStrConvertor( const wchar* _str )
{
    ex_static_assert( (TTypeTraits<CHAR_TYPE_TO>::IsCharacter), "T is not a character type" );
    if( typeop::IsSameType<CHAR_TYPE_TO,wchar>::Result ) // no need to convert the string
    {
        // this process have no meaning and just a dummy function here.
        // it just in case some stupid guys call the class 
        ex_warning( "This process should not be involked" );
    }
    else // need to convert the string
    {
        ConvertedString = (CHAR_TYPE_TO*)Convert(_str, (char*)Buffer);
    }
}

// ------------------------------------------------------------------
// Desc: TStrConvertor destructor 
// ------------------------------------------------------------------

template <typename CHAR_TYPE_TO, uint32 SIZE>
INLINE TStrConvertor<CHAR_TYPE_TO, SIZE>::~TStrConvertor()
{
    if ( ConvertedString != Buffer && ConvertedString != NULL )
        ex_free_nomanage( ConvertedString, EX_GP(EX_ALLOCATOR) ); // TODO: use fast string allocator
}

// ------------------------------------------------------------------
// Desc: operator CHAR_TYPE_TO
// ------------------------------------------------------------------

template <typename CHAR_TYPE_TO, uint32 SIZE>
INLINE TStrConvertor<CHAR_TYPE_TO, SIZE>::operator CHAR_TYPE_TO* () 
{
    return ConvertedString;
}

// ------------------------------------------------------------------
// Desc: Convert
//  wchar -> char
// ------------------------------------------------------------------

template <typename CHAR_TYPE_TO, uint32 SIZE>
INLINE char* TStrConvertor<CHAR_TYPE_TO, SIZE>::Convert( const wchar* _src, char* _dest )
{
    char* dest = _dest;
    size_t len = ex::str::len(_src)+1;

    if ( len > SIZE )
        dest = (char*)ex_malloc_nomanage( len*sizeof(char), EX_GP(EX_ALLOCATOR) ); // TODO: use fast string allocator

    for ( uint i = 0; i < len; ++i )
#if ( EX_ENDIAN == EX_BIG_ENDIAN )
        dest[i] = _src[i] & 0x00FF;
#else // else if EX_LITTLE_ENDIAN
    dest[i] = _src[i] & 0xFF00;
#endif 

    return dest;
}

// ------------------------------------------------------------------
// Desc: Convert
//  char -> wchar
// ------------------------------------------------------------------

template <typename CHAR_TYPE_TO, uint32 SIZE>
INLINE wchar* TStrConvertor<CHAR_TYPE_TO, SIZE>::Convert( const char* _src, wchar* _dest )
{
    wchar* dest = _dest;
    size_t len = ex::str::len(_src)+1; 

    if ( len > SIZE ) 
        dest = (wchar*)ex_malloc_nomanage( len*sizeof(wchar), EX_GP(EX_ALLOCATOR) ); // TODO: use fast string allocator

    for ( uint i = 0; i < len; ++i )
        dest[i] = _src[i];

    return dest;
}

// #########################
} // end namespace _private
// #########################

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END STRCONVERTOR_HPP_1250526383
// #################################################################################

