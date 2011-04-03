// ======================================================================================
// File         : futil.h
// Author       : Wu Jie 
// Last Change  : 04/02/2010 | 23:26:21 PM | Friday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FUTIL_H_1270221983
#define FUTIL_H_1270221983
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// native interface
#if ( EX_PLATFORM == EX_WIN32 )
    #include "win32/futil_native.h"
#elif ( EX_PLATFORM == EX_LINUX )
    #include "linux/futil_native.h"
#elif ( EX_PLATFORM == EX_XENON )
    #include "xenon/futil_native.h"
#elif ( EX_PLATFORM == EX_PS3 )
    #include "ps3/futil_native.h"
#endif

// file classes
#include "File.h"
#include "PhysicalFile.h"
#include "TextFile.h"

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace futil { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// futil::file
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace file { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// char
template < typename T >
IFile::smart_ptr_t create ( const path_t& _fullPath, uint32 _flags = futil::access::read | futil::access::write_exist )
{
    IFile::smart_ptr_t spFile ( ex_new T(_fullPath) );
    if ( spFile->open( _flags ) )
        return spFile;
    else
        return IFile::smart_ptr_t(); 
}

// wchar
template < typename T >
IFile::smart_ptr_t create ( const wpath_t& _fullPath, uint32 _flags = futil::access::read | futil::access::write_exist )
{
    IFile::smart_ptr_t spFile ( ex_new T(_fullPath) );
    if ( spFile->open( _flags ) )
        return spFile;
    else
        return IFile::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: Opens a file. 
// The function fails if the file does not exist.
// ------------------------------------------------------------------ 

// char
template < typename T >
IFile::smart_ptr_t open ( const path_t& _fullPath ) { 
    return futil::file::create<T>( _fullPath,  futil::access::read | futil::access::write_exist ); 
}

// wchar
template < typename T >
IFile::smart_ptr_t open ( const wpath_t& _fullPath ) { 
    return futil::file::create<T>( _fullPath,  futil::access::read | futil::access::write_exist ); 
}

// ------------------------------------------------------------------ 
// Desc: Creates a new file, always.
// if a file exists, the function overwrites the file
// ------------------------------------------------------------------ 

// char
template < typename T >
IFile::smart_ptr_t replace ( const path_t& _fullPath ) {
    return futil::file::create<T>( _fullPath,  futil::access::read | futil::access::write_replace ); 
}

// wchar
template < typename T >
IFile::smart_ptr_t replace ( const wpath_t& _fullPath ) {
    return futil::file::create<T>( _fullPath,  futil::access::read | futil::access::write_replace ); 
}

// ------------------------------------------------------------------ 
// Desc: Opens a file, always.
// if a file does not exist, the function creates a file, else if append existing file.
// ------------------------------------------------------------------ 

// char
template < typename T >
IFile::smart_ptr_t append ( const path_t& _fullPath ) {
    return futil::file::create<T>( _fullPath,  futil::access::read | futil::access::write_append ); 
}

// wchar
template < typename T >
IFile::smart_ptr_t append ( const wpath_t& _fullPath ) {
    return futil::file::create<T>( _fullPath,  futil::access::read | futil::access::write_append ); 
}

// ------------------------------------------------------------------ 
// Desc: Opens a file for reading
// ------------------------------------------------------------------ 

// char
template < typename T >
IFile::smart_ptr_t readonly ( const path_t& _fullPath ) {
    return futil::file::create<T>( _fullPath,  futil::access::read ); 
}

// wchar
template < typename T >
IFile::smart_ptr_t readonly ( const wpath_t& _fullPath ) {
    return futil::file::create<T>( _fullPath,  futil::access::read ); 
}

// ------------------------------------------------------------------ 
// Desc: 
// NOTE: after remove the file, the IFile::handle_t is no longer valid.
//       you should not use the spFile after remove.
// ------------------------------------------------------------------ 

EX_LIBS_DLL void remove ( IFile::smart_ptr_t _spFile );

// ######################### 
} // end namespace file 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// futil::dir
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace dir { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// TODO: pls reference QDir.
// TODO: futil::dir::create, 
// TODO: IDir IDir.balabala

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
#endif // END FUTIL_H_1270221983
// #################################################################################


