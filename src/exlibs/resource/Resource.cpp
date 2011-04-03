// ======================================================================================
// File         : Resource.cpp
// Author       : Wu Jie 
// Last Change  : 08/05/2009 | 21:54:54 PM | Wednesday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Resource.h"
#include "ResourceMng.h"
#include "../Serialization/BinarySerializeNode.h"
#include "../Serialization/XmlSerializeNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// static member defines
///////////////////////////////////////////////////////////////////////////////

EX_DEF_PROPERTIES_BEGIN (Resource)
    EX_REGISTER_PROPERTY_ATTRS ( "ResID", m_resID, PropAttr::readonly|PropAttr::no_serialize )
    EX_REGISTER_PROPERTY_ATTRS ( "CurrentVersion", m_curVersion, PropAttr::readonly )
    EX_REGISTER_PROPERTY_ATTRS ( "RawFiles", m_rawFiles, PropAttr::readonly )
EX_DEF_PROPERTIES_END()

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Resource::onDropRes ( void* _pData )
{
    Resource* _pResource = static_cast<Resource*>(_pData);
    ex_check( EX_GP(ResourceMng)->releaseRes ( _pResource->m_resID ) == EResult::ok, 
              "Error: Failed to release resource: type: %s, name: %s.", 
              _pResource->getClassID().c_str(), 
              _pResource->m_resID.c_str() );
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Resource::Resource ( const string_id_t& _resID )
    : m_refCount(0)
    , m_state (eState_Unloaded)
    , m_resID (_resID)
    , m_curVersion (0)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Resource::~Resource ()
{
    // NOTE: we can't call unloadRes() in ~Resource, because unloadRes() including 
    //       virtual function unload(), and call virtual function in construt/destruct will loose polymorphisn in cpp.
    if ( isLoaded() )
    {
        ex_warning ( "error! try to delete a resource-ptr without unload it first: %s", m_resID.c_str() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Resource::loadCompiledResource ( const path_t& _binFullPath, BinarySerializeNode* _pBinaryNode )
{
    IFile::smart_ptr_t spFile = futil::file::readonly<PhysicalFile>(_binFullPath);
    if ( spFile )
    {
        // skip check header
        // skip check raw-file counts.
        // skip check raw-file ids.
        spFile->seek ( sizeof(Resource::SHeader) + sizeof(uint32) + sizeof(uint64) * this->rawFiles().size(), futil::seek::current );

        // read raw data
        uint sizeToEnd = uint(spFile->sizeToEnd());
        _pBinaryNode->loadFromFile ( spFile, sizeToEnd );
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Resource::writeCompiledResource ( const path_t& _srcFullPath, const path_t& _binFullPath, BinarySerializeNode& _binaryNode )
{
    // if the dest path not exists, we need to create them first
    if ( futil::dir::exists(_binFullPath) == false )
    {
        ex_check_return ( futil::dir::mkdirs ( _binFullPath.split().first ) == EResult::ok, 
                          EResult::failed,
                          "Failed to create path: %s",  
                          _binFullPath.split().first.c_str() );
    }

    // now open the desired file
    IFile::smart_ptr_t spFile = futil::file::replace<PhysicalFile>(_binFullPath);
    if ( spFile )
    {
        // write header
        Resource::SHeader header;
        header.ver = this->currentVersion();
        header.typeID = hash_str ( getClassName() ); 
        uint64 fileID = futil::file::fileID ( _srcFullPath );
        ex_assert (fileID != 0, "fileID is zero. (it happends when the file not found)");
        header.fileID = fileID;
        spFile->write ( &header, sizeof (header) );

        // write raw-files number and count
        uint32 numRawFiles = this->rawFiles().size();
        spFile->write ( &numRawFiles, sizeof (numRawFiles) );
        for ( file_map_t::c_iterator iter = this->rawFiles().begin(); iter != this->rawFiles().end(); ++iter )
        {
            uint64 rawFileID = futil::file::fileID ( (*iter).rawfile() );
            ex_assert (rawFileID != 0, "fileID is zero. (it happends when the file not found)");
            spFile->write ( &rawFileID, sizeof (rawFileID) );
        }

        // write raw data
        if ( _binaryNode.size() > 0 )
            _binaryNode.saveToFile ( spFile );
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool Resource::checkIfNeedCompile ( const path_t& _srcFullPath, const path_t& _binFullPath )
{
    // if the dest file not exists, compile it!
    if ( futil::file::exists( _binFullPath ) == false )
        return true;

    IFile::smart_ptr_t spFile = futil::file::readonly<PhysicalFile>(_binFullPath);
    if ( spFile )
    {
        // get src-file file-id.
        uint64 fileID = futil::file::fileID ( _srcFullPath );

        // check the header
        Resource::SHeader header;
        spFile->read ( &header, sizeof(header) );
        if ( this->currentVersion() != header.ver ||
             hash_str ( this->getClassName() ) != header.typeID ||
             fileID != header.fileID )
        {
            return true;
        }

        // check raw-data file counts
        uint32 numRawFiles = 0;
        spFile->read ( &numRawFiles, sizeof(uint32) );
        if ( numRawFiles != this->rawFiles().size() )
        {
            return true;
        }

        // check raw-data file ids
        for ( file_map_t::c_iterator iter = this->rawFiles().begin(); iter != this->rawFiles().end(); ++iter )
        {
            uint64 fileID = -1;
            spFile->read ( &fileID, sizeof(uint64) );
            uint64 rawFileID = futil::file::fileID ( (*iter).rawfile() );
            if ( fileID != rawFileID )
            {
                return true;
            }
        }
    }

    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Resource::loadRes ()
{
    result_t eResult = EResult::ok;

    // check if file exist
    ex_log("load resource %s\n", m_resID.c_str() );

    // check if resource file exists.
    r_path_t rfile = r_path_t( this->resID().c_str() );
    if ( fsys::file::exists( rfile ) ) {
        // set to loading state
        m_state = eState_Loading;

        // prepare the bin-serialize node.
        BinarySerializeNode binaryNode (512);

        // if we are in exrepo mode, load the resource directly.
        if ( fsys::repo ( string_id_t(rfile.repoName().c_str()) )->mode == fsys::mode::exrepo )
        {
            // TODO { 
            // IFile::smart_ptr_t spFile = fsys::file::readonly(rfile);
            // if ( spFile ) // read data from archive-file
            // {
            //     uint sizeToEnd = uint(spFile->sizeToEnd());
            //     binaryNode.loadFromFile ( spFile, sizeToEnd );
            // }
            // } TODO end 
        }
        else
        {
            //
            path_t srcFullPath = rfile.srcfile();
            path_t binFullPath = rfile.binfile();

            // serialize the source resource info
            ex::XmlSerializeNode loadNode ( ex::XmlNode::smart_ptr_t(ex_new ex::XmlNode( this->getClassName() ) ) );
            loadNode.loadFromFile ( srcFullPath.c_str() );
            this->serialize( &loadNode );

            // check if need compile resource
            if ( checkIfNeedCompile( srcFullPath, binFullPath ) )
            {
                // TODO: during compile the src file and dest file should be lock. so that no one can write the resource.
                // Lock( srcFullPath );
                // Lock( binFullPath );

                ex_log("  |- compile resource %s\n", srcFullPath.c_str() );
                binaryNode.setSaving ();
                ex_check_return( compile ( &binaryNode ) == EResult::ok, 
                                 EResult::failed, 
                                 "resource %s compiled failed.", 
                                 m_resID.c_str() );

                // save compiled resource to file
                ex_check_return( writeCompiledResource ( srcFullPath, binFullPath, binaryNode ) == EResult::ok, 
                                 EResult::failed, 
                                 "failed to write compiled resource: %s", 
                                 binFullPath.c_str() );

                ex_log("  |- save as %s\n", binFullPath.c_str() );

                // TODO: after finish writing the resource,  src file and dest file should be unlock.
                // UnLock( srcFullPath );
                // UnLock( binFullPath );
            }
            else // load compiled resource directly
            {
                ex_log("  |- load compiled resource %s\n", binFullPath.c_str() );
                binaryNode.setLoading ();
                ex_check_return ( loadCompiledResource ( binFullPath, &binaryNode ) == EResult::ok, 
                                  EResult::failed,
                                  "failed to loadCompiledResource" );

                // TODO: if load failed, we have to try re-compile the resource
            }
        }

        // process the data by binary node
        binaryNode.setLoading ();
        if ( binaryNode.size() > 0 )
        {
            ex_log("  |- process raw data\n" );
            eResult = this->processData ( binaryNode );
        }

        //
        if ( eResult != EResult::ok )
            ex_log("  |- failed to process data in resource %s\n", m_resID.c_str());
        else
            ex_log("  |- done\n" );

        // set to loaded state
        m_state = eState_Loaded;
    }
    else {
        ex_warning ( "Resource file not found: %s", rfile.c_str() );
        return EResult::not_found;
    }

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Resource::reloadRes ()
{
    result_t eResult = EResult::ok;

    // NOTE: reload only happends in local fmode. 

    // check if file exist
    ex_log("reload resource %s\n", m_resID.c_str() );

    // check if resource file exists.
    r_path_t rfile = r_path_t( this->resID().c_str() );

    if ( fsys::file::exists( rfile ) ) {
        // set to loading state
        m_state = eState_Loading;

        BinarySerializeNode binaryNode (512);

        //
        path_t srcFullPath = rfile.srcfile();
        path_t binFullPath = rfile.binfile();

        // re-compile the resource 

        // TODO: during compile the src file and dest file should be lock. so that no one can write the resource.
        // Lock( srcFullPath );
        // Lock( binFullPath );

        ex_log("  |- compile resource %s\n", srcFullPath.c_str() );
        binaryNode.setSaving ();
        ex_check_return( compile ( &binaryNode ) == EResult::ok, 
                         EResult::failed,
                         "resource %s compiled failed.", 
                         m_resID.c_str() );

        // save compiled resource to file
        ex_check_return( writeCompiledResource ( srcFullPath, binFullPath, binaryNode ) == EResult::ok, 
                         EResult::failed,
                         "failed to write compiled resource: %s", 
                         binFullPath.c_str() );

        ex_log("  |- save as %s\n", binFullPath.c_str() );

        // TODO: after finish writing the resource,  src file and dest file should be unlock.
        // UnLock( srcFullPath );
        // UnLock( binFullPath );

        // use binary memory for processing 
        binaryNode.setLoading ();
        if ( binaryNode.size() > 0 )
        {
            ex_log("  |- reload resource.\n" );
            eResult = this->reload ( binaryNode );
        }

        //
        if ( eResult != EResult::ok )
            ex_log("  |- failed to reload resource %s\n", m_resID.c_str() );
        else
            ex_log("  |- done\n" );

        // set to loaded state
        m_state = eState_Loaded;
    }
    else {
        ex_warning ( "Resource file not found: %s", rfile.c_str() );
        return EResult::not_found;
    }

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t Resource::unloadRes ()
{
    if ( isLoading () )
    {
        // TODO: should cancle the loading { 
        m_state = eState_Loaded;
        // } TODO end 
    }

    if ( isLoaded() )
    {
        // set state to unloading
        m_state = eState_Unloading;

        // check unload result 
        if ( this->unload () == EResult::ok )
        {
            m_state = eState_Unloaded;
            return EResult::ok;
        }
        else // else, go back to loaded state.
        {
            m_state = eState_Loaded;
            return EResult::failed;
        }
    }
    else
    {
        ex_warning ( "unload resource %s failed. the resource state is not mark as 'Loaded'.", m_resID.c_str() );
        return EResult::failed;
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

