// ======================================================================================
// File         : File.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:35:26 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FILE_H_1250523331
#define FILE_H_1250523331
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################


///////////////////////////////////////////////////////////////////////////////
// class IFile
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL IFile
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef SmartPtr<IFile> smart_ptr_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:
    IFile( const path_t& _path = path_t() ) 
        : m_path(_path)
    {
    }
    IFile( const wpath_t& _path ) 
        : m_wpath(_path)
    {
    }
    virtual ~IFile() 
    {
        // NOTE: don't do close here. if you want auto-close, do it in your inherit class.
        // cpp constructor/destructor function will lose polymorphism.
        // NOTE: also the close() is a pure function, if you write close here, it will
        // get link error.
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    virtual bool open( uint32 _flags = futil::access::read | futil::access::write_exist ) = 0;
    virtual bool close() = 0;

    //
    virtual futil::offset_t seek( futil::offset_t _offset, futil::seek::Enum _eSeek = futil::seek::begin ) = 0;

    //
    virtual futil::sz_t write( const void* _pData, futil::sz_t _bytesToWrite ) = 0;
    virtual futil::sz_t read( void* _pData, futil::sz_t _bytesToRead ) = 0;

    //
    virtual futil::sz_t size() const = 0;
    virtual futil::offset_t tell() const = 0;

    //
    INLINE void setPath ( const path_t& _path ) { m_path = _path; }
    INLINE const path_t& path() const { return m_path; }

    INLINE void setWPath ( const wpath_t& _path ) { m_wpath = _path; }
    INLINE const wpath_t& wpath() const { return m_wpath; }

    INLINE futil::sz_t sizeToEnd () const { return size() - tell(); }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    path_t m_path;
    wpath_t m_wpath;

}; // end class IFile

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END FILE_H_1250523331
// #################################################################################
