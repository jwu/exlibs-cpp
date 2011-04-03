// ======================================================================================
// File         : IO.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:47:08 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef IO_H_1250524031
#define IO_H_1250524031
// #################################################################################

/**
  =======================================
  printf doc
  =======================================

  <General>
      %[flags][width][.precision][modifier]type

  <flags>           control convertion (optional)
      --------------------------------------------------------------------------------------------
      flag  | Description
      ------+-------------------------------------------------------------------------------------
       [-]  | value is left-justified (default is right-justified)
      ------+-------------------------------------------------------------------------------------
       [+]  | forces to show sign of value ([+] or [-])
            | default is to show only [-] for negative values, overrules space
      ------+-------------------------------------------------------------------------------------
      space | print " " in front of positive value, print - for negative value
      ------+-------------------------------------------------------------------------------------
       [#]  | convert to alternative form:
            |   [o]                                 increase precision to force the first digit to be a zero
            |
            |   [x]/[X]                             nonzero result will have prefix "0x" or "0X"
            |
            |   [a]/[A], [e]/[E], [f]/[F], [g]/[G]  result will always have decimal point
            |
            |   [g]/[G]                             trailing zeros are not removed
      ------+-------------------------------------------------------------------------------------
       [0]  | for  [d], [i], [o], [u], [x], [X], [a], [A], [e], [E], [f], [F], [g], [G] 
            | conversions leading zeros are used to pad to the field width instead of spaces
      --------------------------------------------------------------------------------------------

  <width>           number of characters to output (optional)
      ----------------------------------------------------------------------------------------------
      width   | Description
      --------+-------------------------------------------------------------------------------------
      general | This is a decimal integer specifying the minimum field width. If the normal  
              | conversion produces fewer characters than this, the field is padded with     
              | spaces to the specified width. If the normal conversion produces more        
              | characters than this, the field is not truncated. Normally, the output is    
              | right-justified within the field.                                            
      --------+-------------------------------------------------------------------------------------
        [*]   | A field width of [*] may be specified. This means that the next argument       
              | in the argument list (before the actual value to be printed) is used as the  
              | field width. The value must be an integer of type [int]. If the value is      
              | negative, this means to set the [-] flag and to use the absolute value as      
              | the field width.                                                             
      --------+-------------------------------------------------------------------------------------
      example | ( "%*d", 8,20 )  ==> "      20"  (8 width of value 20)
      --------------------------------------------------------------------------------------------
  
  <.precision>      precision of number (optional)
      --------------------------------------------------------------------------------------------
      precision | Description
     -----------+---------------------------------------------------------------------------------
       general  | The precision specifies the number of digits to be written for the numeric  
                | conversions. If the precision is specified, it consists of a period ([.])  
                | followed optionally by a decimal integer (which defaults to zero if        
                | omitted).                                                                  
     -----------+---------------------------------------------------------------------------------
         [*]    | A precision of [*] may be specified. This means that the next argument         
                | in the argument list (before the actual value to be printed) is used as the 
                | precision. The value must be an integer of type [int], and is ignored if it  
                | is negative.                                                                
                | If [*] is specified for both the field width and precision, the field width   
                | argument precedes the precision argument.                                   
     -----------+---------------------------------------------------------------------------------
        (none)  | default precision:
                | 1 for [d], [i], [o], [u], [x], [X] types. Precision gives the minimum number
                | of digits to appear.
                | 6 for [f], [F], [e], [E] types. Precision gives the number of digits to
                | appear after decimal point.
                | For [g], [G] types all digits are printed.
                | For [s] type all characters of the string are printed, not
                | including the terminating null character.
                | For [a], [A] and [FLT_RADIX] of 2: precision is sufficient for an
                | exact representation of the value.
                | For [a], [A] and [FLT_RADIX] not equal to 2: precision is sufficient
                | to distinguish values of type [double].
     -----------+---------------------------------------------------------------------------------
      [.]/[.0]  | For [d], [i], [o], [u], [x], [X] types the default precision is used, unless
                | the value is 0, then no characters are printed.
                | For [f], [F], [e], [E] types no decimal-point and no decimal-digits are
                | printed..
                | For [g], [G] types precision is assumed to be 1.
                | For [s] type nothing is printed.
                | For [a], [A] types no decimal-point and no decimal-digits appear.
     -----------+---------------------------------------------------------------------------------
        [.N]    | For [d], [i], [o], [u], [x], [X] types. At least N digits appear, if 
                | necessary output is expanded with leading zeros.
                | For [f], [F], [e], [E] types. N digits appear after decimal point.
                | For [g], [G] types N digits are printed.
                | For [s] type a maximum of N characters of the string are printed,
                | not including the terminating null character.
                | For [a], [A] types N specifies the number of digits after decimal 
                | point.
     ---------------------------------------------------------------------------------------------
  
  <modifier>        overrides size (type) of argument (optional)
     --------------------------------------------------------------------------------------------
      modifier | Description
     ----------+---------------------------------------------------------------------------------
        [hh]   | Specifies that the argument is a [signed char] or [unsigned char], 
               | as appropriate. A [char] argument is converted to an [int] or [unsigned int] 
               | by the default argument promotions anyway, but this modifier says to convert it 
               | back to a [char] again.
     ----------+---------------------------------------------------------------------------------
        [h]    | Specifies that the argument is a [short int] or [unsigned short int]
               | as appropriate. A [short] argument is converted to an [int] or [unsigned int]
               | by the default argument promotions anyway, but this modifier says to convert it
               | back to a [short] again.
     ----------+---------------------------------------------------------------------------------
        [l]    | Specifies that the argument is a [long int] or [unsigned long int],
               | as appropriate. Two l characters is like the L modifier, below
               | If used with [%c] or [%s] the corresponding parameter is considered
               | as a wide character or wide character string respectively.
     ----------+---------------------------------------------------------------------------------
        [ll]   | Specifies that a following [d], [i], [o], [u], [x], [X] applies to a
               | [long long int] or [unsigned long long int] argument; or that a
               | [n] applies to a pointer to [long long int].
     ----------+---------------------------------------------------------------------------------
        [L]    | Specifies that a following [a], [A], [e], [E], [f], [F], [g], [G] conversion
               | specifier applies to a [long double] argument.
     ----------+---------------------------------------------------------------------------------
        [j]    | Specifies that a following [d], [i], [o], [u], [x], [X] applies to [intmax_t]
               | or [uintmax_t], or that a following [n] applies to pointer to [intmax_t].
     ----------+---------------------------------------------------------------------------------
        [t]    | Specifies that a following [d], [i], [o], [u], [x], [X] applies to a [ptrdiff_t] 
               | or the corresponding unsigned integer type argument,
               | or that a [n] applies to a pointer to a [ptrdiff_t] argument.
     ----------+---------------------------------------------------------------------------------
        [z]    | Specifies that the following [d], [i], [o], [u], [x], [X] applies to a [size_t] 
               | or the corresponding singed integer type argument,
               | or that a [n] applies to a pointer to a signed integer type corresponding to 
               | [size_t] argument.
     ---------------------------------------------------------------------------------------------

  <type>            type of conversion (required)
     ---------------------------------------------------------------------------------------------
         type  | Description
     ----------+----------------------------------------------------------------------------------
       [d],[i] | type [signed int],   output decicmal, style [-]dddd
     ----------+----------------------------------------------------------------------------------
         [o]   | type [unsigned int], output octal,    style:  dddd
     ----------+----------------------------------------------------------------------------------
         [u]   | type [unsigned int], output decimal,  style   dddd
     ----------+----------------------------------------------------------------------------------
         [x]   | type [unsigned int], output hexadecimal, style dddd using a...f
     ----------+----------------------------------------------------------------------------------
         [X]   | type [unsigned int], output hexadecimal, style dddd using A...F
     ----------+----------------------------------------------------------------------------------
       [f],[F] | type [double], output decimal, style [-]ddd.ddd
     ----------+----------------------------------------------------------------------------------
         [e]   | type [double], output decimal, style [-]d.ddde+/-dd
     ----------+----------------------------------------------------------------------------------
         [E]   | type [double], output decimal, style [-]d.dddE+/-dd
     ----------+----------------------------------------------------------------------------------
         [g]   | type [double], printed as type [e] if exponent is less than -4
               | or greater than or equal to the precision. Otherwise [f] is used.
     ----------+----------------------------------------------------------------------------------
         [G]   | type [double], printed as type [E] if exponent is less than -4
               | or greater than or equal to the precision. Otherwise [F] is used.
     ----------+----------------------------------------------------------------------------------
         [a]   | type [double], style [-]0xh.hhhhp+/-d
               |                          h: hexadecimal digit 0...9, a...f
               |                          d: decimal digit
     ----------+----------------------------------------------------------------------------------
         [A]   | type [double], style [-]0Xh.hhhhP+/-d
               |                          h: hexadecimal digit 0...9, A...F
               |                          d: decimal digit
     ----------+----------------------------------------------------------------------------------
         [c]   | no [l] modifier:   type [char], single character is printed
               | with [l] modifier: type [wchar_t], single character is printed 
     ----------+----------------------------------------------------------------------------------
         [s]   | no [l] modifier:   pointer to array of [char], string is printed
               | with [l] modifier: pointer to array of [wchar_t], string is printed 
     ----------+----------------------------------------------------------------------------------
         [p]   | type pointer to [void], value of pointer is printed in an
               | implementation-defined way
     ----------+----------------------------------------------------------------------------------
         [n]   | argument is a pointer to [signed int] into which is written the
               | number of characters written to the output stream so far
     ----------+----------------------------------------------------------------------------------
         [%]   | a % is printed
     ---------------------------------------------------------------------------------------------
 */


// #########################
namespace ex {
// #########################

// ------------------------------------------------------------------
// Desc: printf
// ------------------------------------------------------------------

EX_LIBS_DLL int printf( const char* _format, ... );
EX_LIBS_DLL int printf( const wchar* _format, ... );

// ------------------------------------------------------------------
// Desc: fprintf
// ------------------------------------------------------------------

EX_LIBS_DLL int fprintf( FILE* _stream, const char* _format, ... );
EX_LIBS_DLL int fprintf( FILE* _stream, const wchar* _format, ... );

// ------------------------------------------------------------------
// Desc: vsnprintf 
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int vsnprintf( char* _str, uint _count, const char* _format, va_list _ap )
{
    return ::vsnprintf( _str, _count, _format, _ap );
}

// ========================================================
// wchar ver
// ========================================================

INLINE int vsnprintf( wchar* _str, uint _count, const wchar* _format, va_list _ap )
{
#if ( EX_PLATFORM == EX_PS3 ) 
    return ::vswprintf( (wchar_t*)_str, _count*sizeof(wchar), (const wchar_t*)_format, _ap );
#elif ( EX_PLATFORM == EX_WIN32 )
    return ::_vsnwprintf( (wchar_t*)_str, _count*sizeof(wchar), (const wchar_t*)_format, _ap );
#elif ( EX_PLATFORM == EX_LINUX )
    return wvsnprintf( (wchar_t*)_str, _count*sizeof(wchar), (const wchar_t*)_format, _ap );
#endif
}

// ========================================================
// template ver
// ========================================================

template <typename CHAR_T, size_t DEST_COUNT>
INLINE int vsnprintf( CHAR_T (&_str_buffer)[DEST_COUNT], const CHAR_T* _format, va_list _ap )
{
    ex_static_assert( TypeTraits<CHAR_T>::isCharacter, "T must be character type" );
    int result = ex::vsnprintf( _str_buffer, DEST_COUNT, _format, _ap );
    return result;
}

// ------------------------------------------------------------------
// Desc: snprintf
// ------------------------------------------------------------------

EX_LIBS_DLL int snprintf( char* _buffer, uint _count, const char* _format, ... );
EX_LIBS_DLL int snprintf( wchar* _buffer, uint _count, const wchar* _format, ... );

// template ver
template < typename CHAR_T, uint DEST_SIZE>
INLINE int snprintf( CHAR_T (&_dest_buffer)[DEST_SIZE], const CHAR_T* _format, ... )
{
    ex_static_assert( TypeTraits<CHAR_T>::isCharacter, "T must be character type" );
    va_list args;
    va_start( args, _format );
    int result = ex::vsnprintf( _dest_buffer, DEST_SIZE, _format, args );
    va_end(args);
    return result;
}

// ------------------------------------------------------------------
// Desc: vsprintf
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int vsprintf( char* _str, const char* _format, va_list _ap )
{
    return ::vsprintf( _str, _format, _ap );
}

// ========================================================
// wchar ver
// ========================================================

INLINE int vsprintf( wchar* _str, const wchar* _format, va_list _ap )
{
#if ( EX_PLATFORM == EX_PS3 ) 
    return ::vswprintf( _str, 2048, _format, _ap );
#else
    return ::vswprintf( (wchar_t*)_str, (const wchar_t*)_format, _ap );
#endif
}

// ------------------------------------------------------------------
// Desc: fopen
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE FILE* fopen( const char* _file_name, const char* _open_type )
{
    return ::fopen( _file_name, _open_type );
}

// ========================================================
// wchar ver
// ========================================================

INLINE FILE* fopen( const wchar* _file_name, const wchar* _open_type )
{
#if ( EX_PLATFORM == EX_WIN32 )
    return ::_wfopen( (const wchar_t*)_file_name, (const wchar_t*)_open_type );
#else
    ex_warning( "fopen not support wchar in this platform" );
    return NULL;
#endif
}

// ------------------------------------------------------------------
// Desc: fclose
// ------------------------------------------------------------------

INLINE int fclose( FILE* _stream )
{
    return ::fclose(_stream);
}

// ------------------------------------------------------------------ 
// Desc: fwrite 
// ------------------------------------------------------------------ 

INLINE size_t fwrite ( const void* _pData, size_t _size, size_t _count, FILE* _pStream )
{
    return ::fwrite ( _pData, _size, _count, _pStream );
}

// ------------------------------------------------------------------ 
// Desc: fread 
// ------------------------------------------------------------------ 

INLINE size_t fread ( void* _pData, size_t _size, size_t _count, FILE* _pStream )
{
    return ::fread ( _pData, _size, _count, _pStream );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE int fflush ( FILE* _pStream )
{
    return ::fflush(_pStream);
}

// ------------------------------------------------------------------
// Desc: unlink
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

INLINE int unlink( const char* _file_name )
{
#if ( EX_PLATFORM == EX_WIN32 )
    return ::_unlink( _file_name );
#else
    return ::unlink( _file_name );
#endif
}

// ========================================================
// wchar ver
// ========================================================

INLINE int unlink( const wchar* _file_name )
{
#if ( EX_PLATFORM == EX_WIN32 )
    return ::_wunlink( (const wchar_t*)_file_name );
#else
    ex_warning( "unlink not support wchar in this platform" );
    return -1;
#endif
}

// ------------------------------------------------------------------
// Desc: stat() can't handle a trailing '/' or '\', remove it first.
// ------------------------------------------------------------------

int stat ( const char* _name, struct stat* _stp );
int stat ( const wchar* _name, struct _stat* _stp );

// ------------------------------------------------------------------
// Desc: logf
// ------------------------------------------------------------------

EX_LIBS_DLL void logf( const char* _file_name, const char* _format, ... );
#if EX_UNICODE_PLATFORM
EX_LIBS_DLL void logf( const wchar* _file_name, const wchar* _format, ... );
#endif // END EX_UNICODE_PLATFORM 

// #########################
} // end namespace ex
// #########################

// #################################################################################
#endif // END IO_H_1250524031
// #################################################################################

