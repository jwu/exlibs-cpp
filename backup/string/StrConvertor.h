// ======================================================================================
// File         : StrConvertor.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:26:06 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef STRCONVERTOR_H_1250526371
#define STRCONVERTOR_H_1250526371
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class SStrConvertorHelper 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private {
// #########################

    struct SStrConvertorHelper
    {
        static wchar MakeType(const wchar*);
        static char  MakeType(const char*);
    }; // end struct SStrConvertorHelper 

// #########################
} // end namespace _private
// #########################

///////////////////////////////////////////////////////////////////////////////
// class TStrConvertor 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private {
// #########################

    template <typename CHAR_TYPE_TO, uint32 SIZE=128>
    class TStrConvertor
    {
    public:
        explicit INLINE TStrConvertor( const char* _str );
        explicit INLINE TStrConvertor( const wchar* _str );
        INLINE ~TStrConvertor();
        INLINE operator CHAR_TYPE_TO* (); 

    private:
        // wchar -> char
        INLINE char* Convert( const wchar* _src, char* _dest );
        // char -> wchar
        INLINE wchar* Convert( const char* _src, wchar* _dest );

    private:
        // prevent default constructor
        TStrConvertor();

        // use buffer in stack to hold the source string
        CHAR_TYPE_TO  Buffer[SIZE];

        // in case of the buffer size is short than the string size, hold a point for heap allocate
        CHAR_TYPE_TO* ConvertedString;

    }; // end class TStrConvertor

// #########################
} // end namespace _private
// #########################

// #########################
} // end namespace ex 
// #########################


// ------------------------------------------------------------------
// Desc: EX_IS_SAME_CHARACTER_TYPE
// ------------------------------------------------------------------

#define EX_IS_SAME_CHARACTER_TYPE(str,type) (sizeof(::ex::_private::SStrConvertorHelper::MakeType(str)) == sizeof(type))

// ------------------------------------------------------------------
// Desc: EX_TO_TCHAR / WCHAR / CHAR
// ------------------------------------------------------------------

#define EX_TO_TCHAR(str) EX_IS_SAME_CHARACTER_TYPE(str,tchar) ? (tchar*)str : (tchar*)::ex::_private::TStrConvertor<tchar>(str)
#define EX_TO_WCHAR(str) EX_IS_SAME_CHARACTER_TYPE(str,wchar) ? (wchar*)str : (wchar*)::ex::_private::TStrConvertor<wchar>(str)
#define EX_TO_CHAR(str)  EX_IS_SAME_CHARACTER_TYPE(str,char ) ? (char*)str : (char*)::ex::_private::TStrConvertor<char>(str)

// #################################################################################
#endif // END STRCONVERTOR_H_1250526371
// #################################################################################
