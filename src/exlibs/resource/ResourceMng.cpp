// ======================================================================================
// File         : ResourceMng.cpp
// Author       : Wu Jie 
// Last Change  : 08/05/2009 | 22:25:17 PM | Wednesday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "ResourceMng.h"
#include "../Serialization/XmlSerializeNode.h"

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace _private { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CReloadThread 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

struct SReloadThread : public Thread
{
    result_t run ()
    {
        return pRes->reloadRes();
    }
    Resource* pRes;
}; // end CReloadThread

// ######################### 
} // end namespace _private 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ResourceMng::ResourceMng ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ResourceMng::~ResourceMng ()
{
    unloadAll();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ResourceMng::unloadAll ()
{
    for ( id_to_res_t::iterator iterRes = m_idToRes.begin(); iterRes != m_idToRes.end(); ++iterRes )
    {
        if ( (*iterRes)->unloadRes() == EResult::ok )
        {
            ex_log("resource %s unloaded\n", iterRes.key().c_str() );
            ex_delete (*iterRes);
        }
    }
    m_idToRes.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Resource* ResourceMng::createRes ( const string_id_t& _typeID, const string_id_t& _resID ) 
{
    Resource* pRes = m_Factory.create(_typeID,_resID); 
    return pRes;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t ResourceMng::releaseRes ( const string_id_t& _resID ) 
{
    result_t eResult = EResult::not_found; 

    // if find resource in resource table by resource id. 
    // decrease the refrence, and if the refrence go to zero. release it.
    id_to_res_t::iterator iterRes = m_idToRes.find(_resID); 
    if ( iterRes != m_idToRes.end() )
    {
        (*iterRes)->decRef();
        if ( (*iterRes)->refCount() == 0 )
        {
            if ( (*iterRes)->unloadRes() == EResult::ok )
            {
                ex_log("resource %s unloaded\n", _resID.c_str() );
                ex_delete (*iterRes);
                m_idToRes.erase(iterRes);
            }
        }
        eResult = EResult::ok;
    }

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ResourceMng::isLoaded ( const string_id_t& _resID )
{
    // find resource table by resource type
    id_to_res_t::iterator itRes = m_idToRes.find(_resID);
    if ( itRes != m_idToRes.end() )
    {
        if ( (*itRes)->isLoaded() )
        {
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t ResourceMng::reloadRes ( const string_id_t& _resID )
{
    // find resource table by resource type
    id_to_res_t::iterator itRes = m_idToRes.find(_resID);
    if ( itRes != m_idToRes.end() )
    {
        if ( !(*itRes)->isLoading() )
        {
            result_t eResult = (*itRes)->reloadRes ();
            if ( eResult != EResult::ok ) {
                (*itRes)->unloadRes();
                return eResult;
            }
        }
        else
        {
            // TODO: should cancle and reload... { 
            return EResult::ok;
            // } TODO end 
        }
    }

    // if we don't found the resource, do pure-load
    Resource::smart_ptr_t spRes = this->getRes<Resource> (_resID);
    if ( !spRes )
        return EResult::failed;
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t ResourceMng::reloadResAsync ( const string_id_t& _resID )
{
    // find resource by res path-id
    id_to_res_t::iterator itRes = m_idToRes.find(_resID); 
    if ( itRes != m_idToRes.end() )
    {
        if ( !(*itRes)->isLoading() )
        {
            // TODO: we should use request queue, and cancle the previours (re)loading thread if new(same) resource comes. { 
            _private::SReloadThread* pReloadThread = ex_new _private::SReloadThread();
            pReloadThread->pRes = *itRes;
            pReloadThread->setName ( string_t("resource_reload_thread") + _resID.c_str() );
            pReloadThread->setAutoRelease (true);
            pReloadThread->start();
            // } TODO end 
        }
        return EResult::ok;
    }

    //
    ex_warning ( "reload failed: resource %s not found", _resID.c_str() );
    return EResult::not_found;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t ResourceMng::autogen ( const r_path_t& _resFile, 
                                const Resource::files_t& _rawFiles, 
                                bool _forceRegen )
{
    // check if the file already exits
    if ( _forceRegen == false && fsys::file::exists(_resFile) ) // if not force regen, return.
    {
        return EResult::ok;
    }

    // check if raw-files exists
    for ( Resource::files_t::c_iterator iter = _rawFiles.begin(); iter != _rawFiles.end(); ++iter )
    {
        if ( futil::file::exists( (*iter).rawfile() ) == false )
            return EResult::failed;
    }

    // if we don't have the path parsed by resID, create one.
    path_t src_file = _resFile.srcfile();
    path_t dir = src_file.dirName();
    if ( futil::file::exists(dir) == false )
        ex::futil::dir::mkdirs (dir);

    // create an instance to handle autogen.
    string_id_t res_type = _resFile.resTypeID();
    Resource* pRes = this->createRes ( res_type, string_id_t(_resFile.c_str()) );
    pRes->registerProperties();
    pRes->m_curVersion = pRes->getLatestVersion();

    // process autogen
    ex_check_return ( pRes->autogen(_rawFiles) == EResult::ok, EResult::failed, "failed to autogen resource %s", res_type.c_str() );

    //
    ex::XmlSerializeNode saveNode ( ex::XmlNode::smart_ptr_t(ex_new ex::XmlNode(res_type.c_str()) ) );
    pRes->serialize( &saveNode );
    saveNode.saveToFile ( src_file.c_str() );
    ex_log("autogen resource %s\n", src_file.c_str() );

    //
    ex_delete (pRes);

    //
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Resource* ResourceMng::getResPtr ( const string_id_t& _resID )
{
    // if the type id or the resource id is invalid, return NULL resource
    if ( _resID.isValid() == false )
        return NULL;

    // find resource table by resource type
    id_to_res_t::iterator itRes = m_idToRes.find(_resID);
    if ( itRes != m_idToRes.end() )
    {
        return (*itRes); 
    }

    // get resource type by resource-path src-ext
    string_id_t typeID = r_path_t(_resID.c_str()).resTypeID ();
    Resource* pRes = createRes (typeID,_resID);
    if ( pRes == NULL )
        return NULL;

    pRes->registerProperties (); // this will trigger registerProperties.

    // TODO { 
    // load in multi thread
    if ( pRes->loadRes () != EResult::ok )
    {
        pRes->unloadRes();
        ex_delete (pRes); // if failed to load the resource, unloaded!
        return NULL;
    }
    else
    {
        m_idToRes.insert ( _resID, pRes );
        return pRes;
    }
    // } TODO end 

    ex_warning ( "Please register resource type %s", typeID.c_str() );
    return NULL;
}

// ######################### 
} // end namespace ex 
// ######################### 

