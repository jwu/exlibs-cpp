// ======================================================================================
// File         : String.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:51:43 PM | Monday,August
// Description  : String Manipulate functions
// ======================================================================================

// #################################################################################
#ifndef STRING_H_1250524310
#define STRING_H_1250524310
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

// ######################### 
namespace str { 
// ######################### 

// ------------------------------------------------------------------
// Desc: strlen 
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE uint len( const char* _str )
{
    return (uint)::strlen(_str);
}

// ========================================================
// wchar ver
// ========================================================

INLINE uint len( const wchar* _str )
{
    return (uint)::wcslen((const wchar_t*)_str);
}

// ------------------------------------------------------------------
// Desc: strncpy 
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE char* ncpy( char* _dest, uint _dest_count, const char* _src, uint _count )
{
    ex_assert( _dest_count >= _count, "Dest array count must greater or equal than count" );

    char* pResult = ::strncpy( _dest, _src, _count );
    ex_assert_slow( ex::str::len(_dest) <= _count, "the dest str is overflow or the null terminator wasn't been copied" );
    return pResult;
}

// ========================================================
// wchar ver
// ========================================================

INLINE wchar* ncpy( wchar* _dest, uint _dest_count, const wchar* _src, uint _count )
{
    ex_assert( _dest_count >= _count, "Dest array count must greater or equal than count" );

    wchar* pResult = (wchar*)::wcsncpy( (wchar_t*)_dest, (const wchar_t*)_src, _count );
    ex_assert_slow( ex::str::len(_dest) <= _count, "the dest str is overflow or the null terminator wasn't been copied" );
    return pResult;
}

// ========================================================
// template ver
// ========================================================

template < typename CHAR_T, uint DEST_SIZE >
INLINE CHAR_T* ncpy( CHAR_T (&_dest_buffer)[DEST_SIZE], const CHAR_T* _src, uint _count )
{
    ex_static_assert( TypeTraits<CHAR_T>::isCharacter, "T must be character type" );
    return ex::str::ncpy( _dest_buffer, DEST_SIZE, _src, _count );
}

// ------------------------------------------------------------------
// Desc: strcmp 
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int cmp( const char* _str1, const char* _str2 )
{
    return ::strcmp( _str1, _str2 );
}

// ========================================================
// wchar ver
// ========================================================

INLINE int cmp( const wchar* _str1, const wchar* _str2 )
{
    return ::wcscmp( (const wchar_t*)_str1, (const wchar_t*)_str2 );
}

// ------------------------------------------------------------------ 
// Desc: strstr
// ------------------------------------------------------------------ 

// ======================================================== 
// char ver 
// ======================================================== 

INLINE const char* str( const char* _str, const char* _strSearch )
{
    return ::strstr ( _str, _strSearch );
}

// ======================================================== 
// wchar ver 
// ======================================================== 

INLINE const wchar* str( const wchar* _str, const wchar* _strSearch )
{
    return (const wchar*)::wcsstr ( (const wchar_t*)_str, (const wchar_t*)_strSearch );
}

// ------------------------------------------------------------------
// Desc: stricmp 
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int icmp( const char* _str1, const char* _str2 )
{
#if (EX_COMPILER == EX_MSVC)
    return ::_stricmp( _str1, _str2 );
#else
    return ::strcasecmp( _str1, _str2 );
#endif
}

// ========================================================
// wchar ver
// ========================================================

INLINE int icmp( const wchar* _str1, const wchar* _str2 )
{
#if (EX_COMPILER == EX_MSVC)
    return ::_wcsicmp( (const wchar_t*)_str1, (const wchar_t*)_str2 );
#else
    ex_assert( false, "wstr case compare not support" );
    return 0;
#endif
}

// ------------------------------------------------------------------
// Desc: strncmp 
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int ncmp( const char* _str1, const char* _str2, uint _count )
{
    return ::strncmp( _str1, _str2, _count );
}

// ========================================================
// wchar ver
// ========================================================

INLINE int ncmp( const wchar* _str1, const wchar* _str2, uint _count )
{
    return ::wcsncmp( (const wchar_t*)_str1, (const wchar_t*)_str2, _count );
}

// ------------------------------------------------------------------
// Desc: strnicmp
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int nicmp( const char* _str1, const char* _str2, uint _count )
{
#if (EX_COMPILER == EX_MSVC)
    return ::_strnicmp( _str1, _str2, _count );
#else
    return ::strncasecmp( _str1, _str2, _count );
#endif
}

// ========================================================
// wchar ver
// ========================================================

INLINE int nicmp( const wchar* _str1, const wchar* _str2, uint _count )
{
#if (EX_COMPILER == EX_MSVC)
    return ::_wcsnicmp( (const wchar_t*)_str1, (const wchar_t*)_str2, _count );
#else
    ex_assert( false, "wstr case n compare not support" );
    return 0;
#endif
}

// ------------------------------------------------------------------ 
// Desc: str::idx 
// ------------------------------------------------------------------ 

// ======================================================== 
// char ver 
// ======================================================== 

EX_LIBS_DLL int idx ( const char* _str, const char* _needle, int _start_idx = 0 );

// ======================================================== 
// wchar ver 
// ======================================================== 

EX_LIBS_DLL int idx ( const wchar* _str, const wchar* _needle, int _start_idx = 0 );

// ------------------------------------------------------------------ 
// Desc: str::ridx 
// ------------------------------------------------------------------ 

// ======================================================== 
// char ver 
// ======================================================== 

EX_LIBS_DLL int ridx ( const char* _str, const char* _needle, int _start_idx = -1 );

// ======================================================== 
// wchar ver 
// ======================================================== 

EX_LIBS_DLL int ridx ( const wchar* _str, const wchar* _needle, int _start_idx = -1 );

// ------------------------------------------------------------------
// Desc: str::ato
// ------------------------------------------------------------------

// ========================================================
// general
// ========================================================

template < typename T >
INLINE T ato ( const char* _str )
{
    return (T)(*_str);
}

// ========================================================
// special type
// ========================================================

// DISABLE: template <> INLINE int      str::ato<int>      ( const char* _str ) { return (int)::atoi(_str); }
template <> INLINE int8     ato<int8>     ( const char* _str ) { return (int8)::atoi(_str); }
template <> INLINE int16    ato<int16>    ( const char* _str ) { return (int16)::atoi(_str); }
template <> INLINE int32    ato<int32>    ( const char* _str ) { return (int32)::atoi(_str); }
template <> INLINE int64    ato<int64>    ( const char* _str ) 
{
#if (EX_PLATFORM == EX_LINUX)
    return (int64)::atoll(_str); 
#elif (EX_PLATFORM == EX_WIN32)
    return (int64)::_atoi64(_str); 
#endif
}

// DISABLE: template <> INLINE uint     str::ato<uint>     ( const char* _str ) { return (uint)::atoi(_str); }
template <> INLINE uint8    ato<uint8>    ( const char* _str ) { return (uint8)::atoi(_str); }
template <> INLINE uint16   ato<uint16>   ( const char* _str ) { return (uint16)::atoi(_str); }
template <> INLINE uint32   ato<uint32>   ( const char* _str ) { return (uint32)::atoi(_str); }
template <> INLINE uint64   ato<uint64>   ( const char* _str )
{
#if (EX_PLATFORM == EX_LINUX)
    return (int64)::atoll(_str); 
#elif (EX_PLATFORM == EX_WIN32)
    return (int64)::_atoi64(_str); 
#endif
}

template <> INLINE float    ato<float>    ( const char* _str ) { return (float)::atof(_str); }
template <> INLINE double   ato<double>   ( const char* _str ) { return (double)::atof(_str); }

template <> INLINE char     ato<char>     ( const char* _str ) { return _str[0]; }

// NOTE: msvc comipler define wchar_t to uint16
#if (EX_COMPILER != EX_MSVC) 
// TODO: template <> INLINE wchar    ato<wchar>    ( const char* _str ) { return (local8bit_to_utf16(_str))[0]; }
#endif

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename CHAR_T >
INLINE bool isInTheList( const CHAR_T _char, const CHAR_T* _list, uint _list_count )
{
    ex_static_assert( TypeTraits<CHAR_T>::isCharacter,  "T must be character type" );

    //
    for ( uint i = 0; i < _list_count; ++i )
        if ( _char == _list[i] )
            return true;

    return false;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename CHAR_T >
INLINE bool isInTheList( const CHAR_T* _str, const CHAR_T** _list, uint _list_count )
{
    ex_static_assert( TypeTraits<CHAR_T>::isCharacter, "T must be character type" );

    //
    for ( uint i = 0; i < _list_count; ++i )
        if ( str::cmp(_str, _list[i] ) == 0 )
            return true;

    return false;
}

// ------------------------------------------------------------------
// Desc: get white space list address, the char,wchar white space
//  list store in different address
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE void getWSList( const char* &_list_addr, uint &_list_count )
{
    // define white space list
    static const char WhiteSpaceList[] = 
    {
        (' '),
        ('\t'),
        ('\r'),
        ('\n'),
    };

    // get value
    _list_addr = WhiteSpaceList; // const_cast<char**>(WhiteSpaceList);
	_list_count = EX_ARRAY_COUNT(WhiteSpaceList);
}

// ========================================================
// wchar ver
// ========================================================

INLINE void getWSList( const wchar* &_list_addr, uint &_list_count )
{
    // define white space list
    static const wchar WhiteSpaceList[] = 
    {
        (L' '),
        (L'\t'),
        (L'\r'),
        (L'\n'),
    };

    // get value
    _list_addr = WhiteSpaceList; // const_cast<wchar**>(WhiteSpaceList);
	_list_count = EX_ARRAY_COUNT(WhiteSpaceList);
}

// ------------------------------------------------------------------
// Desc: split given string by given token, save the result into an array 
// ------------------------------------------------------------------

// ========================================================
// single token
// ========================================================

template< typename CHAR_T, template <class> class STR_ALLOCATOR_T, template <class> class ARR_ALLOCATOR_T >
int splitIntoArray( const CHAR_T* _token, 
                    const CHAR_T* _pSplitString,
                    Array< String<CHAR_T, STR_ALLOCATOR_T>, ARR_ALLOCATOR_T >* _pResult )
{
#if 0
    // TODO: remove this? no use in the function
    // get the white space list by type
    const CHAR_T* white_space_list;
    uint list_count = 0;
    ex::str::getWSList( white_space_list, list_count );
#endif

    //
    const CHAR_T* string_to_parse = _pSplitString;
    const CHAR_T* string_to_split = string_to_parse;
    const CHAR_T* rest_string = NULL;

    int token_len = ex::str::len(_token);
    int sub_str_len = 0;
    uint parse_str_len = (token_len == 1) ? EX_UINT32_MAX : ex::str::len(string_to_parse);

    // stop parsing when we get the end of the str
    while ( *string_to_parse != 0 && parse_str_len > 0 )
    {
        sub_str_len += 1;

        // check if split
        if ( ex::str::nicmp( string_to_parse, _token, token_len ) == 0 )
        {
            if ( sub_str_len > 0 )
            {
                _pResult->push_back( String<CHAR_T, STR_ALLOCATOR_T>( string_to_split, sub_str_len-1 ) );
            }
            else
            {
                _pResult->push_back( String<CHAR_T, STR_ALLOCATOR_T>( "" ) );
            }

            // reset the split value (skip token,too)
            string_to_split = string_to_parse + token_len;
            rest_string = string_to_split; 
            sub_str_len = 0;

            //
            parse_str_len -= token_len;
            string_to_parse += token_len;
        }
        else // go to next check and increase split length
        {
            parse_str_len -= 1;
            string_to_parse += 1;
        }
    }

    if ( rest_string != NULL )
    {
        _pResult->push_back( String<CHAR_T, STR_ALLOCATOR_T>( rest_string ) );
    }

    return int(_pResult->size());
}

// ========================================================
// token list 
// ========================================================

template< typename CHAR_T, template <class> class STR_ALLOCATOR_T, template <class> class ARR_ALLOCATOR_T >
int splitIntoArray( const CHAR_T** _token_list, 
                    int _token_count,
                    const CHAR_T* _pSplitString,
                    Array< String<CHAR_T, STR_ALLOCATOR_T>, ARR_ALLOCATOR_T>* _pResult )
{
#if 0
    // TODO: remove this? no use in the function
    // get the white space list by type
    const CHAR_T* white_space_list;
    uint list_count = 0;
    ex::str::getWSList( white_space_list, list_count );
#endif

    //
    const CHAR_T* string_to_parse = _pSplitString;
    const CHAR_T* string_to_split = string_to_parse;
    const CHAR_T* rest_string = NULL;

    // get all token length to token_len_list first
    uint* token_len_list = (uint*)ex_stack_malloc( sizeof(uint)*_token_count );
    for ( int token_idx = 0; token_idx < _token_count; ++token_idx )
    {
        token_len_list[token_idx] = ex::str::len(_token_list[token_idx]);
    }
    uint jump_idx = uint(-1);

    // init sub & parse string length
    uint sub_str_len = 0;
    uint parse_str_len = ex::str::len(string_to_parse);

    // stop parsing when we get the end of the str
    while ( *string_to_parse != 0 && parse_str_len > 0 )
    {
        // jump sub string at first
        sub_str_len += 1;

        // re-init jump_idx after sub string jump;
        jump_idx = uint(-1);

        // check split each split token
        for ( int token_idx = 0; token_idx < _token_count; ++token_idx )
        {
            // check if split
            if ( ex::str::nicmp( string_to_parse, _token_list[token_idx], token_len_list[token_idx] ) == 0 )
            {
                if ( sub_str_len > 0 )
                {
                    _pResult->push_back( String<CHAR_T, STR_ALLOCATOR_T>( string_to_split, sub_str_len-1 ) );
                }
                else
                {
                    _pResult->push_back( String<CHAR_T, STR_ALLOCATOR_T>( "" ) );
                }

                // reset the split value (skip token,too)
                string_to_split = string_to_parse + token_len_list[token_idx];
                rest_string = string_to_split; 
                sub_str_len = 0;

                // jump by this check token length
                jump_idx = token_idx;
                break;
            }
        }

        // go to next check and increase split length
        if ( jump_idx == uint(-1) )
        {
            parse_str_len -= 1;
            string_to_parse += 1;
        }
        else
        {
            parse_str_len -= token_len_list[jump_idx];
            string_to_parse += token_len_list[jump_idx];
        }
    }

    if ( rest_string != NULL )
    {
        _pResult->push_back( String<CHAR_T, STR_ALLOCATOR_T>( rest_string ) );
    }

    return int(_pResult->size());
}

// ------------------------------------------------------------------
// Desc: return true if 'c' is a path separator.
// ------------------------------------------------------------------

INLINE bool isPathSep ( const char _c )
{
#if ( EX_PLATFORM == EX_LINUX )
    return (_c == '/');
#elif ( EX_PLATFORM == EX_WIN32 )
    return (_c == ':' || _c == '/' || _c == '\\');
#endif
}

INLINE bool isPathSep ( const wchar _c )
{
#if ( EX_PLATFORM == EX_LINUX )
    return (_c == L'/');
#elif ( EX_PLATFORM == EX_WIN32 )
    return (_c == L':' || _c == L'/' || _c == L'\\');
#endif
}

// ------------------------------------------------------------------
// Desc: Return true if "p" points to just after a path separator.
//       Take care of multi-byte characters.
//       "_str" must point to the start of the file name
// ------------------------------------------------------------------

// char
INLINE bool afterPathSep ( const char* _str, const char* _p )
{
    if ( _str == _p )
        return false;

    return ex::str::isPathSep(_p[-1]);
}

// wchar
INLINE bool afterPathSep ( const wchar* _str, const wchar* _p )
{
    if ( _str == _p )
        return false;

    return ex::str::isPathSep(_p[-1]);
}

// ------------------------------------------------------------------
// Desc: get the next path component (just after the next path separator).
// ------------------------------------------------------------------

INLINE char* getNextPathComp( char* _fileName )
{
    while ( *_fileName && !ex::str::isPathSep(*_fileName) )
        ++_fileName;
    if ( *_fileName )
        ++_fileName;
    return _fileName;
}

INLINE wchar* getNextPathComp( wchar* _fileName )
{
    while ( *_fileName && !ex::str::isPathSep(*_fileName) )
        ++_fileName;
    if ( *_fileName )
        ++_fileName;
    return _fileName;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void move( char* _to, const char* _from )
{
    ex::mem::move( _to, _from, ex::str::len(_from) + 1 );
}

INLINE void move( wchar* _to, const wchar* _from )
{
    ex::mem::move( _to, _from, 2 * (ex::str::len(_from) + 1) );
}

// ------------------------------------------------------------------
// Desc: 
//  if _stripAll = true, the single dot come at the beginning will
//  be removed, otherwise the function will keep it.
//  example: path = ./foo/./bar
//     _stripAll = false ==> ./foo/bar
//     _stripAll = true ==> foo/bar
// ------------------------------------------------------------------

EX_LIBS_DLL void simplify( char* _in_out_filename, bool _stripAll = false );
EX_LIBS_DLL void simplify( wchar* _in_out_filename, bool _stripAll = false );

// ######################### 
} // end namespace str 
// ######################### 


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END STRING_H_1250524310
// #################################################################################
