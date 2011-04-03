// ======================================================================================
// File         : PhysicalFile.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:36:34 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PHYSICALFILE_H_1250523479
#define PHYSICALFILE_H_1250523479
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

#include "File.h" // abstract class

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class PhysicalFile
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL PhysicalFile : public IFile
{
    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    PhysicalFile ( const path_t& _path = path_t() );
    PhysicalFile ( const wpath_t& _path );
    virtual ~PhysicalFile();

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

    futil::handle_t m_handle;

}; // end class PhysicalFile

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END PHYSICALFILE_H_1250523479
// #################################################################################
