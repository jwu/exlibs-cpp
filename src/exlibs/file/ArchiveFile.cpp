// ======================================================================================
// File         : ArchiveFile.cpp
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 10:04:17 AM | Tuesday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "ArchiveFile.h"

// #########################
namespace ex { 
// #########################

// TODO:
#if 0
///////////////////////////////////////////////////////////////////////////////
// member function defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

CArchiveFile::CArchiveFile( const r_path_t& _path )
     : IFile(_path),
       m_handle(fsys::InvalidHandle)
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

CArchiveFile::~CArchiveFile()
{
    close();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool CArchiveFile::open( uint32 _flags )
{
    ex_assert( fsys::file::_private::isValid(m_handle)==false, "already open a file" );

    m_handle = fsys::file::_private::create( m_path, _flags );
    if ( !fsys::file::_private::isValid(m_handle) )
    {
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool CArchiveFile::close()
{
    if ( fsys::file::_private::isValid(m_handle) )
    {
        fsys::file::_private::close(m_handle);
        m_handle = fsys::InvalidHandle; 
        return true;
    }
    return false;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::offset_t CArchiveFile::seek( futil::offset_t _offset, futil::seek::Enum _eSeek )
{
    return fsys::file::_private::seek( m_handle, _offset, _eSeek ); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::sz_t CArchiveFile::write( const void* _pData, futil::sz_t _bytesToWrite )
{
    ex_warning ("archive file can't write");
    // fsys::sz_t bytesWritten = 0;
    // result_t eResult = fsys::file::_private::write( m_handle, _pData, _bytesToWrite, &bytesWritten );
    // if ( eResult != EResult::ok )
    // {
    //     // TODO:
    // }
    // return bytesWritten;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::sz_t CArchiveFile::read( void* _pData, futil::sz_t _bytesToRead )
{
    fsys::sz_t bytesRead = 0;
    result_t eResult = fsys::file::_private::read( m_handle, _pData, _bytesToRead, &bytesRead );
    if ( eResult != EResult::ok )
    {
        // TODO:
    }
    return bytesRead;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::sz_t CArchiveFile::size() const
{
    return fsys::file::_private::size( m_handle );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

futil::offset_t CArchiveFile::tell() const
{
    return fsys::file::_private::seek( m_handle, 0 );
}
#endif

// #########################
} // end namespace ex 
// #########################

