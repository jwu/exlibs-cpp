// ======================================================================================
// File         : futil_native.h
// Author       : Wu Jie 
// Last Change  : 04/02/2010 | 21:39:54 PM | Friday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FUTIL_NATIVE_H_1270215596
#define FUTIL_NATIVE_H_1270215596
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace futil { 
// ######################### 

// types
typedef uint64 sz_t;
typedef int64  offset_t;
typedef HANDLE handle_t;
static const handle_t InvalidHandle = INVALID_HANDLE_VALUE; 

// seek
namespace seek {
    enum Enum
    {
        begin   = FILE_BEGIN,
        current = FILE_CURRENT,
        end     = FILE_END
    }; // end enum Enum
}

// access
namespace access {
    enum Enum
    {
        read                = 1<<0,
        read_no_buffering   = 1<<1,
        write_exist         = 1<<2,
        write_append        = 1<<3,
        write_replace       = 1<<4
    }; // end enum Enum
}

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

EX_LIBS_DLL bool isdir ( const path_t& _fullPath );
EX_LIBS_DLL bool isdir ( const wpath_t& _fullPath );

EX_LIBS_DLL bool isfile ( const path_t& _fullPath );
EX_LIBS_DLL bool isfile ( const wpath_t& _fullPath );

EX_LIBS_DLL result_t glob ( const path_t& _pathName /*must be directory*/, Array<path_t>* _pResult );
EX_LIBS_DLL result_t glob ( const wpath_t& _pathName /*must be directory*/, Array<wpath_t>* _pResult );

EX_LIBS_DLL result_t globDirs ( const path_t& _pathName /*must be directory*/, Array<path_t>* _pResult );
EX_LIBS_DLL result_t globDirs ( const wpath_t& _pathName /*must be directory*/, Array<wpath_t>* _pResult );

EX_LIBS_DLL result_t globFiles ( const path_t& _pathName /*must be directory*/, Array<path_t>* _pResult );
EX_LIBS_DLL result_t globFiles ( const wpath_t& _pathName /*must be directory*/, Array<wpath_t>* _pResult );

EX_LIBS_DLL bool exists ( const path_t& _fullPath );
EX_LIBS_DLL bool exists ( const wpath_t& _fullPath );

///////////////////////////////////////////////////////////////////////////////
// futil::file
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace file { 
// ######################### 

// ######################### 
namespace _private { 
// ######################### 

    //
    EX_LIBS_DLL handle_t create( const path_t& _fullPath, uint32 _openAccessFlags = access::read|access::write_exist );
    EX_LIBS_DLL handle_t create( const wpath_t& _fullPath, uint32 _openAccessFlags = access::read|access::write_exist );
    EX_LIBS_DLL result_t close( handle_t _hFile );

    //
    EX_LIBS_DLL result_t read ( handle_t _hFile, void* _pBuffer, sz_t _bytesToRead, sz_t* _pBytesRead );
    EX_LIBS_DLL result_t write ( handle_t _hFile, const void* _pBuffer, sz_t _bytesToWrite, sz_t* _pByteWritten );

    //
    EX_LIBS_DLL offset_t seek( handle_t _hFile, offset_t _offset, futil::seek::Enum _seekMethod = futil::seek::current );
    EX_LIBS_DLL sz_t size( handle_t _hFile );

    //
    EX_LIBS_DLL bool isValid ( handle_t _hFile );

// ######################### 
} // end namespace _private 
// ######################### 

    //
    EX_LIBS_DLL bool exists ( const path_t& _fullPath );
    EX_LIBS_DLL bool exists ( const wpath_t& _fullPath );

    EX_LIBS_DLL result_t remove ( const path_t& _fullPath );
    EX_LIBS_DLL result_t remove ( const wpath_t& _fullPath );

    EX_LIBS_DLL result_t copy ( const path_t& _src, const path_t& _new, bool _overwrite = true );

    EX_LIBS_DLL result_t glob ( const path_t& _pathName /*can include wildcard*/, Array<path_t>* _pResult );

    EX_LIBS_DLL uint64 fileID ( const path_t& _fullPath );
    EX_LIBS_DLL uint64 fileID ( const wpath_t& _fullPath );

// ######################### 
} // end namespace file 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// futil::dir
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace dir { 
// ######################### 

    //
    EX_LIBS_DLL bool exists ( const path_t& _fullPath );
    EX_LIBS_DLL bool exists ( const wpath_t& _fullPath );

    EX_LIBS_DLL result_t mkdir ( const path_t& _fullPath );
    EX_LIBS_DLL result_t mkdirs ( const path_t& _fullPath );
    EX_LIBS_DLL result_t remove ( const path_t& _fullPath, bool _removeSubs = false );
    EX_LIBS_DLL result_t copy ( const path_t& _src, const path_t& _dest );

// ######################### 
} // end namespace dir 
// ######################### 

// ######################### 
} // end namespace futil 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END FUTIL_NATIVE_H_1270215596
// #################################################################################
