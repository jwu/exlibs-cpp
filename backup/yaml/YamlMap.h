// ======================================================================================
// File         : YamlMap.h
// Author       : Wu Jie 
// Last Change  : 10/03/2009 | 23:52:35 PM | Saturday,October
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef YAMLMAP_H_1254585160
#define YAMLMAP_H_1254585160
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "YamlNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CYamlMap 
// 
// Purpose: 
// 
// NOTE: the yaml mapping emitter is order independence, this make it weak to be a serialize format.
//
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL CYamlMap : public CYamlNode
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef CYamlMap self_t;
    typedef CYamlNode base_t;

    typedef TMap< CYamlNode::smart_ptr_t,
                  CYamlNode::smart_ptr_t > node_map_t;

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    enum EStyle
    {
        eStyle_Block,
        eStyle_Flow
    }; // end enum EStyle 

    ///////////////////////////////////////////////////////////////////////////////
    // static public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static yaml_mapping_style_t ToYamlStyle ( CYamlMap::EStyle _style );
    static CYamlMap::EStyle FromYamlStyle ( yaml_mapping_style_t _style );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    CYamlMap ( CYamlMap::EStyle _style = CYamlMap::eStyle_Block, const char* _anchor = NULL, const char* _tag = NULL );
    virtual ~CYamlMap ();

    virtual void AddChild ( const CYamlNode::smart_ptr_t& _spNode );
    virtual int Compare ( const CYamlNode& _node ) const;

    //
    virtual CYamlNode::smart_ptr_t GetNode ( const char* _key ) const;
    virtual CYamlNode::smart_ptr_t GetNode ( const CYamlNode::smart_ptr_t& _key ) const;

    //
    void SetStyle ( CYamlMap::EStyle _style ) { m_Style = _style; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    virtual result_t SaveToFile ( yaml_emitter_t* _pEmitter ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    CYamlNode::smart_ptr_t m_spHoldingKey;
    node_map_t  m_NodeMap;

    CYamlMap::EStyle m_Style;

}; // end class CYamlMap

// ######################### 
} // end namespace ex 
// ######################### 



// #################################################################################
#endif // END YAMLMAP_H_1254585160
// #################################################################################


