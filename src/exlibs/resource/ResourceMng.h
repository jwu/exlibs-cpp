// ======================================================================================
// File         : ResourceMng.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:24:51 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RESOURCEMNG_H_1250526294
#define RESOURCEMNG_H_1250526294
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

#include "Resource.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decl
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class ResourceMng
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL ResourceMng
{
    friend class Resource;

    ///////////////////////////////////////////////////////////////////////////////
    // singleton decl
    ///////////////////////////////////////////////////////////////////////////////

    EX_DECL_SINGLETON( ResourceMng ); 

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef HashMap<string_id_t,Resource*> id_to_res_t; 
    typedef Array<string_t> src_exts_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public member funcionts
    ///////////////////////////////////////////////////////////////////////////////

public:

    // constructor & destructor
    ResourceMng ();
    ~ResourceMng ();

    //
    void unloadAll ();

    //
    template < typename T >
    typename T::smart_ptr_t getRes ( const string_id_t& _resID )
    {
        Resource* pRes = getResPtr ( _resID );
        if ( pRes ) {
            pRes->incRef ();
            return typename T::smart_ptr_t ( static_cast<T*>(pRes) );
        }
        return typename T::smart_ptr_t ();
    }
    bool isLoaded ( const string_id_t& _resID );
    result_t reloadRes ( const string_id_t& _resID );
    result_t reloadResAsync ( const string_id_t& _resID );

    // auto
    result_t autogen ( const r_path_t& _resFile, 
                      const Resource::files_t& _rawFiles, 
                      bool _forceRegen = false );

    //
    template < typename T >
    INLINE result_t registerRes ( bool _skipIfExists = false ) 
    {
        if ( _skipIfExists && this->hasRegistered<T>() )
            return EResult::ok;

        ex_check_return ( m_Factory.reg ( T::classID(), &T::create ) == EResult::ok, EResult::failed, "failed to register type(%s) in resource-factory", T::className() ); 
        ex_check_return ( fsys::register_ftype ( string_id_t(T::src_ext()), T::classID() ) == EResult::ok, EResult::failed, "failed to register type(%s) in fsys", T::className() );
        return EResult::ok;
    }

    //
    template < typename T >
    INLINE result_t unregisterRes () 
    {
        ex_check_return ( m_Factory.unreg ( T::classID() ) == EResult::ok, EResult::failed, "failed to un-register resource type(%s) in factory" );
        ex_check_return ( fsys::unregister_ftype ( string_id_t(T::src_ext()) ) == EResult::ok, EResult::failed, "failed to un-register resource type(%s) in fsys" );
        return EResult::ok;
    }

    //
    template < typename T >
    INLINE bool hasRegistered () const { return hasRegistered( T::classID() ); }
    INLINE bool hasRegistered ( const string_id_t& _typeID ) const 
    {
        return m_Factory.hasRegistered (_typeID);
    }

    // useful when we want dummy resource.
    Resource* createRes ( const string_id_t& _typeID, const string_id_t& _resID );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    result_t releaseRes ( const string_id_t& _resID );
    Resource* getResPtr ( const string_id_t& _resID );

    ///////////////////////////////////////////////////////////////////////////////
    // protected members
    ///////////////////////////////////////////////////////////////////////////////

protected:

    Factory < string_id_t, Resource, Seq<const string_id_t&> > m_Factory; 
    id_to_res_t m_idToRes;

}; // end class ResourceMng 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END RESOURCEMNG_H_1250526294
// #################################################################################
