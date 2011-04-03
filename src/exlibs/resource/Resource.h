// ======================================================================================
// File         : Resource.h
// Author       : Wu Jie 
// Last Change  : 08/05/2009 | 20:40:54 PM | Wednesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RESOURCE_H_1250526217
#define RESOURCE_H_1250526217
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decl
///////////////////////////////////////////////////////////////////////////////

class BinarySerializeNode;
namespace _private { struct SReloadThread; }

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class Resource
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Resource : public PropertyObject
{
    ///////////////////////////////////////////////////////////////////////////////
    // general defines (the children just need to write EX_DECL_RESOURCE)
    ///////////////////////////////////////////////////////////////////////////////

    EX_DECL_PROPERTY_OBJECT ( Resource, PropertyObject );
    friend class ResourceMng;
    friend struct _private::SReloadThread;

    enum EState
    {
        eState_Loading,
        eState_Loaded,
        eState_Unloading,
        eState_Unloaded,
    }; // end enum EState

public:

    static void onDropRes ( void* _pData ); 

    typedef Array<r_path_t> files_t;
    typedef HashMap<string_id_t,r_path_t> file_map_t;
    typedef SmartPtr<Resource,RefCounted,&Resource::onDropRes> smart_ptr_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public static functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // static functions
    static ::ex::Resource* create ( const string_id_t& _resID ) { return NULL; }
    static const char* src_ext () { return "unknwon"; }

    // virtual functions
    virtual const char* getSrcExt () const { return "unknown"; }
    virtual uint32 getLatestVersion () const { return 0; }

    ///////////////////////////////////////////////////////////////////////////////
    // SHeader
    ///////////////////////////////////////////////////////////////////////////////

    struct SHeader
    {
        uint32 ver;
        uint32 typeID;
        uint64 fileID;
    }; // end SHeader 

    ///////////////////////////////////////////////////////////////////////////////
    // public member function
    ///////////////////////////////////////////////////////////////////////////////

public:

    Resource ( const string_id_t& _resID );
    virtual ~Resource (); // NOTE: only ResourceMng can call it.

    const string_id_t& resID () const { return m_resID; }
    r_path_t r_path () const { return r_path_t(m_resID.c_str()); }

    uint32 currentVersion() const { return m_curVersion; }
    const file_map_t& rawFiles () const { return m_rawFiles; }

    bool isLoading () { return m_state == eState_Loading; }
    bool isLoaded () { return m_state == eState_Loaded; }
    bool isUnloading () { return m_state == eState_Unloading; }
    bool isUnloaded () { return m_state == eState_Unloaded; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected virtual member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    result_t loadRes ();
    result_t reloadRes ();
    result_t unloadRes ();

    //
    virtual result_t compile ( ISerializeNode* _pNode ) { EX_UNUSED(_pNode); return EResult::failed; }
    virtual result_t processData ( ISerializeNode& _node ) { EX_UNUSED(_node); return EResult::failed; }
    virtual result_t reload ( ISerializeNode& _node ) { EX_UNUSED(_node); return EResult::failed; }
    virtual result_t unload () { return EResult::failed; }

    //
    virtual result_t autogen ( const Resource::files_t& _rawFiles ) 
    { 
        EX_UNUSED(_rawFiles); 
        ex_warning("resource %s not support autogen", this->getClassName() ); 
        return EResult::failed; 
    }

    //
    bool checkIfNeedCompile ( const path_t& _srcFullPath, const path_t& _binFullPath ); 
    result_t writeCompiledResource ( const path_t& _srcFullPath, const path_t& _binFullPath, BinarySerializeNode& _binaryNode );
    result_t loadCompiledResource ( const path_t& _binFullPath, BinarySerializeNode* _pBinaryNode );

    // NOTE: only invoke in ResourceMng.
    INLINE void incRef () { ++m_refCount; }
    INLINE void decRef () { --m_refCount; ex_assert(m_refCount>=0,"ref count go to -1!"); }
    INLINE int refCount () const { return m_refCount; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected members
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // the ref-count in Resource is different than the one used in Resource::smart_ptr_t.
    // the smart point is the resource used outside ResourceMng, those copy,assign will inc/dec
    // the ref-count in smart-pointer only. but those getRes,ReleaseResource will inc/dec the
    // the ref count here.
    int m_refCount;

    //
    EState m_state;

    // the resource id is the format of dir1::dir2::res_name
    // the raw_data is in data/resources/dir1/dir2/res_name.raw_suffix 
    // the compiled data is in data_bin/resources/dir1/dir2/res_name.raw_suffix 
    string_id_t     m_resID; 

    uint32 m_curVersion;
    file_map_t  m_rawFiles;

}; // end class Resource 

///////////////////////////////////////////////////////////////////////////////
// macros
///////////////////////////////////////////////////////////////////////////////

#define EX_DECL_RESOURCE(_selfType,_baseType,_srcExt,_ver) \
        EX_DECL_PROPERTY_OBJECT(_selfType,_baseType); \
    public: \
        /* ---------- typedefs ---------- */ \
        typedef SmartPtr<_selfType,RefCounted,&Resource::onDropRes> smart_ptr_t; \
        /* ---------- static member functions ---------- */ \
    public: \
        static ::ex::Resource* create ( const string_id_t& _resID ) \
        { \
            return ex_new_tag ( #_selfType ) _selfType (_resID); \
        } \
        static const char* src_ext () { return _srcExt; } \
        static uint32 latestVersion() { return _ver; } \
        /* ---------- public member functions ---------- */ \
    public: \
        virtual const char* getSrcExt () const { return _selfType::src_ext(); } \
        virtual uint32 getLatestVersion () const { return _selfType::latestVersion(); } \
        /* ---------- back to private at the end ---------- */ \
    private:

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END RESOURCE_H_1250526217
// #################################################################################

