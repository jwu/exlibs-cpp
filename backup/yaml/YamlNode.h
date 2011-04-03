// ======================================================================================
// File         : YamlNode.h
// Author       : Wu Jie 
// Last Change  : 10/02/2009 | 19:42:44 PM | Friday,October
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef YAMLNODE_H_1254483767
#define YAMLNODE_H_1254483767
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#ifndef YAML_DECLARE_STATIC
    #define YAML_DECLARE_STATIC
#endif

#include <libyaml/inc/yaml.h>

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CYamlNode 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL CYamlNode
{
    typedef CYamlNode self_t;
    friend class CYamlEmitter;
    friend class CYamlDocument;
    friend class CYamlMap;
    friend class CYamlSequence;
    friend class CYamlScalar;

protected:

    // ------------------------------------------------------------------ 
    // Desc: EType
    // ------------------------------------------------------------------ 

    enum EType
    {
        eType_Unknown = 0,
        eType_Scalar,
        eType_Sequence,
        eType_Map,
        eType_Document,
    }; // end enum EType

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef TSmartPtr<CYamlNode> smart_ptr_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    CYamlNode ( const char* _anchor = NULL, const char* _tag = NULL );
    virtual ~CYamlNode ();

    virtual void AddChild ( const CYamlNode::smart_ptr_t& _spNode ) = 0;
    virtual int Compare ( const CYamlNode& _node ) const;

    INLINE EType GetType() const { return m_Type; }

    // to declare friend functions.
    friend bool operator == ( const CYamlNode& _node1, const CYamlNode& _node2 );
    friend bool operator < ( const CYamlNode& _node1, const CYamlNode& _node2 );

    //
    virtual CYamlNode::smart_ptr_t GetNode ( int _idx ) const;
    virtual CYamlNode::smart_ptr_t GetNode ( const char* _key ) const;
    virtual CYamlNode::smart_ptr_t GetNode ( const CYamlNode::smart_ptr_t& _key ) const;
    virtual const char* GetValue () const;

    //
    INLINE const char* GetTag () const { return m_Tag.c_str(); }
    INLINE void SetTag ( const char* _tag ) { m_Tag = _tag; }

    //
    INLINE const char* GetAnchor () const { return m_Anchor.c_str(); }
    INLINE void SetAnchor ( const char* _anchor ) { m_Anchor = _anchor; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    virtual result_t SaveToFile ( yaml_emitter_t* _pEmitter ) const;
    result_t Flush ( yaml_emitter_t* _pEmitter, yaml_event_t* _pEvent ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    EType m_Type;
    string_t m_Anchor;
    string_t m_Tag;

}; // end class CYamlNode 

///////////////////////////////////////////////////////////////////////////////
// class TLess <CYamlNode::smart_ptr_t> 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
struct TLess<CYamlNode::smart_ptr_t> : public TBinaryFunctor< CYamlNode::smart_ptr_t,
                                                              CYamlNode::smart_ptr_t,
                                                              bool > 
{
    bool operator () ( const CYamlNode::smart_ptr_t& _x, const CYamlNode::smart_ptr_t& _y ) const 
    { 
        return *(_x.GetPtr()) < *(_y.GetPtr()); 
    }
};

///////////////////////////////////////////////////////////////////////////////
// operators
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE bool operator == ( const CYamlNode& _node1, const CYamlNode& _node2 )
{
    return (_node1.Compare(_node2) == 0);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE bool operator < ( const CYamlNode& _node1, const CYamlNode& _node2 )
{
    return (_node1.Compare(_node2) == -1);
}

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END YAMLNODE_H_1254483767
// #################################################################################


