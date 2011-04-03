// ======================================================================================
// File         : futil_native.cpp
// Author       : Wu Jie 
// Last Change  : 04/02/2010 | 21:40:04 PM | Friday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "futil_native.h"

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace futil { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool isdir ( const path_t& _fullPath ) { return futil::dir::exists(_fullPath); }
bool isdir ( const wpath_t& _fullPath ) { return futil::dir::exists(_fullPath); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool isfile ( const path_t& _fullPath ) { return futil::file::exists(_fullPath); }
bool isfile ( const wpath_t& _fullPath ) { return futil::file::exists(_fullPath); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// path_t
result_t glob ( const path_t& _pathName, Array<path_t>* _pResult )
{
    // path is not a directory
    if ( futil::dir::exists(_pathName) == false )
    {
        ex_warning( "the path: %s is not exists.", _pathName.c_str() );
        return EResult::invalid_input;
    }
    path_t dirSpec = path_t(_pathName) + "/*";

    //
    WIN32_FIND_DATA findData;
    handle_t hFind = ::FindFirstFile(dirSpec.c_str(), &findData);
    if ( hFind == INVALID_HANDLE_VALUE )
    {
        ex_warning( "Invalid output of FindFirstFile()" );
        return EResult::invalid_output;
    }
    else
    {
        // we skip add file '.' and '..'
        if ( ex::str::ncmp( findData.cFileName, ".", 1) != 0 && 
             ex::str::ncmp( findData.cFileName, "..", 2 ) != 0 )
        {
            _pResult->push_back ( findData.cFileName );
        }

        while ( ::FindNextFile (hFind, &findData) != 0 )
        {
            if ( ex::str::ncmp( findData.cFileName, ".", 1) != 0 && 
                 ex::str::ncmp( findData.cFileName, "..", 2 ) != 0 )
            {
                _pResult->push_back ( findData.cFileName );
            }
        }
        DWORD dwError = GetLastError ();
        FindClose (hFind);
        if ( dwError != ERROR_NO_MORE_FILES )
        {
            _pResult->clear();
            ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
            return EResult::failed;
        }
    }

    return EResult::ok;
}

// wpath_t
result_t glob ( const wpath_t& _pathName /*must be directory*/, Array<wpath_t>* _pResult )
{
    // path is not a directory
    if ( futil::dir::exists(_pathName) == false )
    {
        ex_warning( "the path: %s is not exists.", _pathName.c_str() );
        return EResult::invalid_input;
    }
    wpath_t dirSpec = wpath_t(_pathName) + W("/*");

    //
    WIN32_FIND_DATAW findData;
    handle_t hFind = ::FindFirstFileW((const wchar_t*)dirSpec.c_str(), &findData);
    if ( hFind == INVALID_HANDLE_VALUE )
    {
        ex_warning( "Invalid output of FindFirstFile()" );
        return EResult::invalid_output;
    }
    else
    {
        // we skip add file '.' and '..'
        if ( ex::str::ncmp( (const wchar*)findData.cFileName, W("."), 1) != 0 && 
             ex::str::ncmp( (const wchar*)findData.cFileName, W(".."), 2 ) != 0 )
        {
            _pResult->push_back ( (const wchar*)findData.cFileName );
        }

        while ( ::FindNextFileW (hFind, &findData) != 0 )
        {
            if ( ex::str::ncmp( (const wchar*)findData.cFileName, W("."), 1) != 0 && 
                 ex::str::ncmp( (const wchar*)findData.cFileName, W(".."), 2 ) != 0 )
            {
                _pResult->push_back ( (const wchar*)findData.cFileName );
            }
        }
        DWORD dwError = GetLastError ();
        FindClose (hFind);
        if ( dwError != ERROR_NO_MORE_FILES )
        {
            _pResult->clear();
            ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
            return EResult::failed;
        }
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// path_t
result_t globDirs ( const path_t& _pathName, Array<path_t>* _pResult )
{
    // path is not a directory
    if ( futil::dir::exists(_pathName) == false )
    {
        ex_warning( "the path: %s is not exists.", _pathName.c_str() );
        return EResult::invalid_input;
    }
    path_t dirSpec = path_t(_pathName) + "/*";

    //
    WIN32_FIND_DATA findData;
    handle_t hFind = ::FindFirstFile(dirSpec.c_str(), &findData);
    if ( hFind == INVALID_HANDLE_VALUE )
    {
        ex_warning( "Invalid output of FindFirstFile()" );
        return EResult::invalid_output;
    }
    else
    {
        // we skip add file '.' and '..'
        if ( ex::str::ncmp( findData.cFileName, ".", 1) != 0 && 
             ex::str::ncmp( findData.cFileName, "..", 2 ) != 0 &&
             ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == true )
        {
            _pResult->push_back ( findData.cFileName );
        }

        while ( ::FindNextFile (hFind, &findData) != 0 )
        {
            if ( ex::str::ncmp( findData.cFileName, ".", 1) != 0 && 
                 ex::str::ncmp( findData.cFileName, "..", 2 ) != 0 &&
                 ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == true )
            {
                _pResult->push_back ( findData.cFileName );
            }
        }
        DWORD dwError = GetLastError ();
        FindClose (hFind);
        if ( dwError != ERROR_NO_MORE_FILES )
        {
            _pResult->clear();
            ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
            return EResult::failed;
        }
    }

    return EResult::ok;
}

// wpath_t
result_t globDirs ( const wpath_t& _pathName /*must be directory*/, Array<wpath_t>* _pResult )
{
    // path is not a directory
    if ( futil::dir::exists(_pathName) == false )
    {
        ex_warning( "the path: %s is not exists.", _pathName.c_str() );
        return EResult::invalid_input;
    }
    wpath_t dirSpec = wpath_t(_pathName) + W("/*");

    //
    WIN32_FIND_DATAW findData;
    handle_t hFind = ::FindFirstFileW((const wchar_t*)dirSpec.c_str(), &findData);
    if ( hFind == INVALID_HANDLE_VALUE )
    {
        ex_warning( "Invalid output of FindFirstFile()" );
        return EResult::invalid_output;
    }
    else
    {
        // we skip add file '.' and '..'
        if ( ex::str::ncmp( (const wchar*)findData.cFileName, W("."), 1) != 0 && 
             ex::str::ncmp( (const wchar*)findData.cFileName, W(".."), 2 ) != 0 &&
             ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == true )
        {
            _pResult->push_back ( (const wchar*)findData.cFileName );
        }

        while ( ::FindNextFileW (hFind, &findData) != 0 )
        {
            if ( ex::str::ncmp( (const wchar*)findData.cFileName, W("."), 1) != 0 && 
                 ex::str::ncmp( (const wchar*)findData.cFileName, W(".."), 2 ) != 0 &&
                 ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == true )
            {
                _pResult->push_back ( (const wchar*)findData.cFileName );
            }
        }
        DWORD dwError = GetLastError ();
        FindClose (hFind);
        if ( dwError != ERROR_NO_MORE_FILES )
        {
            _pResult->clear();
            ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
            return EResult::failed;
        }
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// path_t
result_t globFiles ( const path_t& _pathName, Array<path_t>* _pResult )
{
    // path is not a directory
    if ( futil::dir::exists(_pathName) == false )
    {
        ex_warning( "the path: %s is not exists.", _pathName.c_str() );
        return EResult::invalid_input;
    }
    path_t dirSpec = path_t(_pathName) + "/*";

    //
    WIN32_FIND_DATA findData;
    handle_t hFind = ::FindFirstFile(dirSpec.c_str(), &findData);
    if ( hFind == INVALID_HANDLE_VALUE )
    {
        ex_warning( "Invalid output of FindFirstFile()" );
        return EResult::invalid_output;
    }
    else
    {
        // we skip add file '.' and '..'
        if ( ex::str::ncmp( findData.cFileName, ".", 1) != 0 && 
             ex::str::ncmp( findData.cFileName, "..", 2 ) != 0 &&
             ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == false )
        {
            _pResult->push_back ( findData.cFileName );
        }

        while ( ::FindNextFile (hFind, &findData) != 0 )
        {
            if ( ex::str::ncmp( findData.cFileName, ".", 1) != 0 && 
                 ex::str::ncmp( findData.cFileName, "..", 2 ) != 0 &&
                 ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == false )
            {
                _pResult->push_back ( findData.cFileName );
            }
        }
        DWORD dwError = GetLastError ();
        FindClose (hFind);
        if ( dwError != ERROR_NO_MORE_FILES )
        {
            _pResult->clear();
            ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
            return EResult::failed;
        }
    }

    return EResult::ok;
}

// wpath_t
result_t globFiles ( const wpath_t& _pathName /*must be directory*/, Array<wpath_t>* _pResult )
{
    // path is not a directory
    if ( futil::dir::exists(_pathName) == false )
    {
        ex_warning( "the path: %s is not exists.", _pathName.c_str() );
        return EResult::invalid_input;
    }
    wpath_t dirSpec = wpath_t(_pathName) + W("/*");

    //
    WIN32_FIND_DATAW findData;
    handle_t hFind = ::FindFirstFileW((const wchar_t*)dirSpec.c_str(), &findData);
    if ( hFind == INVALID_HANDLE_VALUE )
    {
        ex_warning( "Invalid output of FindFirstFile()" );
        return EResult::invalid_output;
    }
    else
    {
        // we skip add file '.' and '..'
        if ( ex::str::ncmp( (const wchar*)findData.cFileName, W("."), 1) != 0 && 
             ex::str::ncmp( (const wchar*)findData.cFileName, W(".."), 2 ) != 0 &&
             ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == false )
        {
            _pResult->push_back ( (const wchar*)findData.cFileName );
        }

        while ( ::FindNextFileW (hFind, &findData) != 0 )
        {
            if ( ex::str::ncmp( (const wchar*)findData.cFileName, W("."), 1) != 0 && 
                 ex::str::ncmp( (const wchar*)findData.cFileName, W(".."), 2 ) != 0 &&
                 ex::flags_has( findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) == false )
            {
                _pResult->push_back ( (const wchar*)findData.cFileName );
            }
        }
        DWORD dwError = GetLastError ();
        FindClose (hFind);
        if ( dwError != ERROR_NO_MORE_FILES )
        {
            _pResult->clear();
            ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
            return EResult::failed;
        }
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// path_t
bool exists ( const path_t& _fullPath )
{
    return file::exists(_fullPath) || dir::exists(_fullPath);
}

// wpath_t
bool exists ( const wpath_t& _fullPath )
{
    return file::exists(_fullPath) || dir::exists(_fullPath);
}

///////////////////////////////////////////////////////////////////////////////
// futil::file
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace file { 
// ######################### 

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// char
handle_t create ( const path_t& _fullPath, uint32 _openAccessFlags )
{
    //
    handle_t hFile = INVALID_HANDLE_VALUE; 
    DWORD dwFileAccess = 0;
    DWORD dwCreationType = 0;
    DWORD dwFlags = FILE_ATTRIBUTE_NORMAL;

    //
    if ( flags_has( _openAccessFlags, access::read ) )
    {
        dwFileAccess |= FILE_READ_DATA;
        dwCreationType = OPEN_EXISTING;
    }
    if ( flags_has( _openAccessFlags, access::write_exist ) )
    {
        dwFileAccess |= FILE_WRITE_DATA;
        dwCreationType = OPEN_EXISTING;
    }
    if ( flags_has( _openAccessFlags, access::write_append ) )
    {
        dwFileAccess |= FILE_APPEND_DATA;
        dwCreationType = OPEN_ALWAYS;
    }
    if ( flags_has( _openAccessFlags, access::write_replace ) )
    {
        dwFileAccess |= FILE_WRITE_DATA;
        dwCreationType = CREATE_ALWAYS;
    }
    if ( flags_has( _openAccessFlags, access::read_no_buffering ) )
    {
        dwFileAccess |= GENERIC_READ;
		dwCreationType = OPEN_EXISTING;
		dwFlags |= FILE_FLAG_NO_BUFFERING;
    }

    //
    hFile = ::CreateFileA( _fullPath.c_str(), dwFileAccess, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, dwCreationType, dwFlags, NULL );

    //
    if ( !futil::file::_private::isValid(hFile) )
    {
        DWORD dwError = GetLastError ();
        ex_warning( "CreateFile %s failed. Error Code: %u.\n", _fullPath.c_str(), dwError );
    }
    return hFile;
}

// wchar
handle_t create ( const wpath_t& _fullPath, uint32 _openAccessFlags )
{
    //
    handle_t hFile = INVALID_HANDLE_VALUE; 
    DWORD dwFileAccess = 0;
    DWORD dwCreationType = 0;
    DWORD dwFlags = FILE_ATTRIBUTE_NORMAL;

    //
    if ( flags_has( _openAccessFlags, access::read ) )
    {
        dwFileAccess |= FILE_READ_DATA;
        dwCreationType = OPEN_EXISTING;
    }
    if ( flags_has( _openAccessFlags, access::write_exist ) )
    {
        dwFileAccess |= FILE_WRITE_DATA;
        dwCreationType = OPEN_EXISTING;
    }
    if ( flags_has( _openAccessFlags, access::write_append ) )
    {
        dwFileAccess |= FILE_APPEND_DATA;
        dwCreationType = OPEN_ALWAYS;
    }
    if ( flags_has( _openAccessFlags, access::write_replace ) )
    {
        dwFileAccess |= FILE_WRITE_DATA;
        dwCreationType = CREATE_ALWAYS;
    }
    if ( flags_has( _openAccessFlags, access::read_no_buffering ) )
    {
        dwFileAccess |= GENERIC_READ;
		dwCreationType = OPEN_EXISTING;
		dwFlags |= FILE_FLAG_NO_BUFFERING;
    }

    //
    hFile = ::CreateFileW( (const wchar_t*)(_fullPath.c_str()), dwFileAccess, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, dwCreationType, dwFlags, NULL );

    //
    if ( !futil::file::_private::isValid(hFile) )
    {
        DWORD dwError = GetLastError ();
        // TODO: const char* utf8 = utf16_to_utf8(_fullPath.c_str());
        const char* utf8 = "TODO";
        ex_warning( "CreateFile %s failed. Error Code: %u.\n", utf8, dwError );
    }
    return hFile;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t close ( handle_t _hFile )
{
    if ( ::CloseHandle(_hFile) == 0 ) {
        DWORD dwError = GetLastError ();
        ex_warning( "CloseHandle failed. Error Code: %u.\n", dwError );
        return EResult::failed;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t read ( handle_t _hFile, void* _pBuffer, sz_t _bytesToRead, sz_t* _pBytesRead )
{
    ex_assert( _pBuffer, "NULL buffer" );

    bool bSuccess = ::ReadFile( _hFile, _pBuffer, (DWORD)_bytesToRead, (DWORD*)_pBytesRead, 0 ) != 0;
    if ( !bSuccess ) {
        DWORD dwError = GetLastError ();
        ex_warning( "ReadFile failed. Error Code: %u.\n", dwError );
        return EResult::read_failed;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t write ( handle_t _hFile, const void* _pBuffer, sz_t _bytesToWrite, sz_t* _pByteWritten )
{
    ex_assert( _pBuffer, "NULL buffer" );

    bool bSuccess = ::WriteFile( _hFile, _pBuffer, (DWORD)_bytesToWrite, (DWORD*)_pByteWritten, 0 ) != 0;
    if ( !bSuccess ) {
        DWORD dwError = GetLastError ();
        ex_warning( "WriteFile failed. Error Code: %u.\n", dwError );
        return EResult::write_failed;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

offset_t seek ( handle_t _hFile, offset_t _offset, futil::seek::Enum _seekMethod )
{
    LARGE_INTEGER newPos;
    newPos.QuadPart= -1ll;

    //
    LARGE_INTEGER dist;
    dist.QuadPart = _offset;

    bool bSuccess = ::SetFilePointerEx( _hFile, dist, &newPos, _seekMethod ) != 0;
    if ( !bSuccess ) {
        DWORD dwError = GetLastError ();
        ex_warning( "SetFilePointerEx failed. Error Code: %u.\n", dwError );
        return 0;
    }

    return newPos.QuadPart;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

sz_t size ( handle_t _hFile )
{
#if (EX_COMPILER == EX_MSVC)
    //
    LARGE_INTEGER sizeOfFile;
    sizeOfFile.QuadPart = 0ll;
    ::GetFileSizeEx( _hFile, &sizeOfFile );
    return sizeOfFile.QuadPart;
#else
    DWORD sizeOfFile = 0; 
    sizeOfFile = ::GetFileSize( _hFile, NULL );
    return sizeOfFile;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool isValid ( handle_t _hFile ) 
{
    return (_hFile != INVALID_HANDLE_VALUE);
}

// ######################### 
} // end namespace _private 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// char
bool exists ( const path_t& _fullPath )
{
    // to ensure if a file exits, it must first exits, second not be a directory.
    return ::GetFileAttributesA( _fullPath.c_str() ) != uint(-1) && 
        ::GetFileAttributesA( _fullPath.c_str() ) != FILE_ATTRIBUTE_DIRECTORY;
}

// wchar
bool exists ( const wpath_t& _fullPath )
{
    // to ensure if a file exits, it must first exits, second not be a directory.
    return ::GetFileAttributesW( (const wchar_t*)(_fullPath.c_str()) ) != uint(-1) && 
        ::GetFileAttributesW( (const wchar_t*)(_fullPath.c_str()) ) != FILE_ATTRIBUTE_DIRECTORY;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// char
result_t remove ( const path_t& _fullPath )
{
    // if the path not exists or is not a directory 
    if ( futil::file::exists(_fullPath) == false ) {
        return EResult::not_found;
    }

    // now remove the directory and check if success.
    bool bSuccess = ::DeleteFileA ( _fullPath.c_str() ) != 0;
    if ( !bSuccess ) {
        DWORD dwError = GetLastError ();
        ex_warning( "DeleteFile failed. Error Code: %u.\n", dwError );
        return EResult::failed;
    }

    return EResult::ok;
}

// wchar
result_t remove ( const wpath_t& _fullPath )
{
    // if the path not exists or is not a directory 
    if ( futil::file::exists(_fullPath) == false ) {
        return EResult::not_found;
    }

    // now remove the directory and check if success.
    bool bSuccess = ::DeleteFileW ( (const wchar_t*)(_fullPath.c_str()) ) != 0;
    if ( !bSuccess ) {
        DWORD dwError = GetLastError ();
        ex_warning( "DeleteFile failed. Error Code: %u.\n", dwError );
        return EResult::failed;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t copy ( const path_t& _src, const path_t& _new, bool _overwrite )
{
    bool bSuccess = ::CopyFile( _src.c_str(), _new.c_str(), !_overwrite ) != 0; 
    if ( !bSuccess )
    {
        DWORD dwError = GetLastError ();
        ex_warning( "CopyFile failed. Error Code: %u.\n", dwError );
        return EResult::failed;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t glob ( const path_t& _pathName, Array<path_t>* _pResult )
{
    // TODO { 
    // // 
    // WIN32_FIND_DATA findData;

    // handle_t hFind = ::FindFirstFile(dirSpec.c_str(), &findData);
    // if ( hFind == INVALID_HANDLE_VALUE )
    // {
    //     ex_warning( "Invalid output of FindFirstFile()" );
    //     return EResult::invalid_output;
    // }
    // else
    // {
    //     // we skip add file '.' and '..'
    //     if ( ex::StrnCmp( findData.cFileName, ".", 1) != 0 && ex::StrnCmp( findData.cFileName, "..", 2 ) != 0 )
    //     {
    //         _pResult->push_back ( findData.cFileName );
    //     }

    //     while ( ::FindNextFile (hFind, &findData) != 0 )
    //     {
    //         if ( ex::StrnCmp( findData.cFileName, ".", 1) != 0 && ex::StrnCmp( findData.cFileName, "..", 2 ) != 0 )
    //         {
    //             _pResult->push_back ( findData.cFileName );
    //         }
    //     }
    //     DWORD dwError = GetLastError ();
    //     FindClose (hFind);
    //     if ( dwError != ERROR_NO_MORE_FILES )
    //     {
    //         _pResult->clear();
    //         ex_warning( "FindNextFile error. Error Code: %u.\n", dwError );
    //         return EResult::failed;
    //     }
    // }
    // } TODO end 

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// path
uint64 fileID ( const path_t& _fullPath )
{
    if ( futil::file::exists(_fullPath) )
    {
        WIN32_FIND_DATA win32FileInfo;
        futil::handle_t hFile = ::FindFirstFile(_fullPath.c_str(), &win32FileInfo);
        bool bOk = futil::file::_private::isValid(hFile);
        if ( bOk )
        {
            // NOTE:
            // typedef struct _SYSTEMTIME  
            // {  
            //     WORD   wYear; // Year - 1998  
            //     WORD   wMonth; // 1-January, 2-Febraury, .... 12-December  
            //     WORD   wDayOfWeek; // 0-Sunday, 1-Monday, ... 6-Saturday  
            //     WORD   wDay; // day of month  
            //     WORD   wHour; // 0-23 hourformat  
            //     WORD   wMinute; // 0-59  
            //     WORD   wSecond; // 0-59  
            //     WORD   wMilliseconds; // 0-999  
            // }   SYSTEMTIME;     

            FILETIME ft;
            SYSTEMTIME st;  

            ft.dwHighDateTime = win32FileInfo.ftLastWriteTime.dwHighDateTime;
            ft.dwLowDateTime = win32FileInfo.ftLastWriteTime.dwLowDateTime;

            FileTimeToSystemTime( &ft, &st );      

            // make system as a string
            static const uint MAXLEN = 128;
            char strTime [MAXLEN];
            snprintf ( strTime, MAXLEN, "%d%d%d%d%d%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );

            return gen_uint64 ( hash_str(_fullPath.c_str()), hash_str(strTime) );
        }
    }
    return 0;
}

// wpath
uint64 fileID ( const wpath_t& _fullPath )
{
    if ( futil::file::exists(_fullPath) )
    {
        WIN32_FIND_DATAW win32FileInfo;
        futil::handle_t hFile = ::FindFirstFileW( (const wchar_t*)_fullPath.c_str(), &win32FileInfo);
        bool bOk = futil::file::_private::isValid(hFile);
        if ( bOk )
        {
            // NOTE:
            // typedef struct _SYSTEMTIME  
            // {  
            //     WORD   wYear; // Year - 1998  
            //     WORD   wMonth; // 1-January, 2-Febraury, .... 12-December  
            //     WORD   wDayOfWeek; // 0-Sunday, 1-Monday, ... 6-Saturday  
            //     WORD   wDay; // day of month  
            //     WORD   wHour; // 0-23 hourformat  
            //     WORD   wMinute; // 0-59  
            //     WORD   wSecond; // 0-59  
            //     WORD   wMilliseconds; // 0-999  
            // }   SYSTEMTIME;     

            FILETIME ft;
            SYSTEMTIME st;  

            ft.dwHighDateTime = win32FileInfo.ftLastWriteTime.dwHighDateTime;
            ft.dwLowDateTime = win32FileInfo.ftLastWriteTime.dwLowDateTime;

            FileTimeToSystemTime( &ft, &st );      

            // make system as a string
            static const uint MAXLEN = 128;
            char strTime [MAXLEN];
            snprintf ( strTime, MAXLEN, "%d%d%d%d%d%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );

            return gen_uint64 ( hash_str(_fullPath.c_str()), hash_str(strTime) );
        }
    }
    return 0;
}

// ######################### 
} // end namespace file 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// dir
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace dir { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// char
bool exists ( const path_t& _fullPath ) {
    return ::GetFileAttributesA( _fullPath.c_str() ) != uint(-1) && 
        ::GetFileAttributesA( _fullPath.c_str() ) == FILE_ATTRIBUTE_DIRECTORY;
}

// wchar
bool exists ( const wpath_t& _fullPath ) {
    return ::GetFileAttributesW( (const wchar_t*)(_fullPath.c_str()) ) != uint(-1) && 
        ::GetFileAttributesW( (const wchar_t*)(_fullPath.c_str()) ) == FILE_ATTRIBUTE_DIRECTORY;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t mkdir ( const path_t& _fullPath )
{
    if ( !::CreateDirectory ( _fullPath.c_str(), NULL ) )
    {
        DWORD errID = GetLastError ();
        if ( errID == ERROR_ALREADY_EXISTS )
            return EResult::already_existed;

        if ( errID == ERROR_PATH_NOT_FOUND )
            return EResult::not_found;
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t mkdirs ( const path_t& _fullPath )
{
    result_t eResult = EResult::ok;
    // 
    path_t::pair_t pair = _fullPath.split (); 

    // if the path level reach to 0, and not exists, create it.
    if ( pair.second.empty() && !futil::dir::exists( pair.first ) )
    {
        eResult = futil::dir::mkdir (_fullPath);
        if ( eResult == EResult::already_existed )
            eResult = EResult::ok;
        return eResult;
    }

    // recursive create directories if not exists
    if ( !pair.first.empty() && !pair.second.empty() && !futil::dir::exists( pair.first ) )
    {
        ex_check_return ( futil::dir::mkdirs ( pair.first.c_str() ) == EResult::ok, 
                          EResult::failed,
                          "Failed to create path %s", 
                          pair.first.c_str() );
    }

    // 
    eResult = futil::dir::mkdir (_fullPath);
    if ( eResult == EResult::already_existed )
        eResult = EResult::ok;
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t remove ( const path_t& _fullPath, bool _removeSubs )
{
    // if the path not exists or is not a directory 
    if ( futil::dir::exists(_fullPath) == false )
    {
        return EResult::not_exists;
    }

    // if we have sub directories and files, recursively delete them
    if ( _removeSubs )
    {
        // TODO:
    }

    // now remove the directory and check if success.
    bool bSuccess = ::RemoveDirectory ( _fullPath.c_str() ) != 0;
    if ( !bSuccess )
    {
        DWORD dwError = GetLastError ();
        ex_warning( "RemoveDirectory error. Error Code: %u.\n", dwError );
        return EResult::failed;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t copy ( const path_t& _src, const path_t& _dest )
{
    result_t eResult = EResult::ok;

    // check if src-path exists
    if ( futil::dir::exists(_src) == false )
    {
        return EResult::not_exists;
    }
    // check if dest-path exists, if not, create it.
    if ( futil::dir::exists(_dest) == false )
    {
        eResult = futil::dir::mkdirs(_dest);
        if ( eResult != EResult::ok )
            return eResult; 
    }

    // get files
    Array<path_t> file_names;
    eResult = futil::globFiles ( _src, &file_names );
    if ( eResult != EResult::ok )
        return eResult;

    // recursively copy dirs, and files.
    for ( Array<path_t>::iterator iter = file_names.begin(); iter != file_names.end(); ++iter )
    {
        path_t src_file = _src + *iter;
        path_t dest_file = _dest + *iter;

        // if src_file is dir
        if ( futil::isdir(src_file) ) {
            if ( futil::dir::copy ( src_file, dest_file ) != EResult::ok ) {
                ex_warning ( "Failed copy directory %s to %s", src_file.c_str(), dest_file.c_str() ); 
            }
        }
        else {
            if ( futil::file::copy ( src_file, dest_file, true ) == false ) {
                ex_warning ( "Failed copy file %s to %s", src_file.c_str(), dest_file.c_str() ); 
            }
        }
    }

    return eResult;
}


// ######################### 
} // end namespace dir 
// ######################### 

// ######################### 
} // end namespace futil 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

