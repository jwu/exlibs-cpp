// ======================================================================================
// File         : PhysicalFile.cpp
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 10:04:02 AM | Tuesday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "PhysicalFile.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// member function defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

PhysicalFile::PhysicalFile( const path_t& _path )
     : IFile(_path),
       m_handle(futil::InvalidHandle)
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

PhysicalFile::PhysicalFile( const wpath_t& _path )
     : IFile(_path),
       m_handle(futil::InvalidHandle)
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

PhysicalFile::~PhysicalFile()
{
    close();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool PhysicalFile::open( uint32 _flags )
{
    ex_assert( futil::file::_private::isValid(m_handle)==false, "already open a file" );

    if ( !m_path.empty() )
        m_handle = futil::file::_private::create( m_path, _flags );
    else if ( !m_wpath.empty() )
        m_handle = futil::file::_private::create( m_wpath, _flags );

    if ( !futil::file::_private::isValid(m_handle) ) {
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool PhysicalFile::close()
{
    if ( futil::file::_private::isValid(m_handle) )
    {
        futil::file::_private::close(m_handle);
        m_handle = futil::InvalidHandle; 
        return true;
    }
    return false;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::offset_t PhysicalFile::seek( futil::offset_t _offset, futil::seek::Enum _eSeek )
{
    return futil::file::_private::seek( m_handle, _offset, _eSeek ); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::sz_t PhysicalFile::write( const void* _pData, futil::sz_t _bytesToWrite )
{
    futil::sz_t bytesWritten = 0;
    result_t eResult = futil::file::_private::write( m_handle, _pData, _bytesToWrite, &bytesWritten );
    if ( eResult != EResult::ok )
    {
        // TODO:
    }
    return bytesWritten;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::sz_t PhysicalFile::read( void* _pData, futil::sz_t _bytesToRead )
{
    futil::sz_t bytesRead = 0;
    result_t eResult = futil::file::_private::read( m_handle, _pData, _bytesToRead, &bytesRead );
    if ( eResult != EResult::ok )
    {
        // TODO:
    }
    return bytesRead;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::sz_t PhysicalFile::size() const
{
    return futil::file::_private::size( m_handle );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::offset_t PhysicalFile::tell() const
{
    return futil::file::_private::seek( m_handle, 0 );
}

// #########################
} // end namespace ex 
// #########################

