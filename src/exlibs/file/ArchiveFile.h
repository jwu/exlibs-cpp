// ======================================================================================
// File         : ArchiveFile.h
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 10:02:19 AM | Tuesday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ARCHIVEFILE_H_1271124145
#define ARCHIVEFILE_H_1271124145
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

#include "File.h" // abstract class

// #########################
namespace ex { 
// #########################

// TODO:
#if 0
///////////////////////////////////////////////////////////////////////////////
// class CArchiveFile
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL CArchiveFile : public IFile
{
    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    CArchiveFile ( const r_path_t& _path = path_t() );
    virtual ~CArchiveFile();

    ///////////////////////////////////////////////////////////////////////////////
    // public member function 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    virtual bool open ( uint32 _flags = futil::access::read | futil::access::write_exist );
    virtual bool close();

    //
    virtual futil::offset_t seek( futil::offset_t _offset, futil::seek::Enum _eSeek = futil::seek::begin );

    //
    virtual futil::sz_t write( const void* _pData, futil::sz_t _bytesToWrite );
    virtual futil::sz_t read( void* _pData, futil::sz_t _bytesToRead );

    //
    virtual futil::sz_t size () const;
    virtual futil::offset_t tell () const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    fsys::fnode m_handle;

}; // end class CArchiveFile
#endif

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END ARCHIVEFILE_H_1271124145
// #################################################################################


