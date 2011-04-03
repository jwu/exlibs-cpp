// ======================================================================================
// File         : YamlMap.cpp
// Author       : Wu Jie 
// Last Change  : 10/03/2009 | 23:55:43 PM | Saturday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "YamlMap.h"
#include "YamlScalar.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlMap::CYamlMap ( CYamlMap::EStyle _style, const char* _anchor, const char* _tag )
    : CYamlNode ( _anchor, _tag ) 
    , m_Style ( _style )
{
    m_Type = eType_Map;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlMap::~CYamlMap ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CYamlMap::AddChild ( const CYamlNode::smart_ptr_t& _spNode )
{
    // if the holding key is NULL, add child as key
    if ( !m_spHoldingKey )
    {
        m_spHoldingKey = _spNode;
    }
    else // else insert holding key and value into map 
    {
        m_NodeMap.Insert ( m_spHoldingKey, _spNode );
        m_spHoldingKey = CYamlNode::smart_ptr_t();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int CYamlMap::Compare ( const CYamlNode& _node ) const
{
    //
    int result = base_t::Compare (_node);
    if ( result != 0 )
    {
        return result;
    }

    // 
    const CYamlMap& mapNode = static_cast<const CYamlMap&>(_node);
    if ( m_NodeMap.Size() != mapNode.m_NodeMap.Size() )
    {
        return m_NodeMap.Size() < mapNode.m_NodeMap.Size() ? -1 : 1; 
    }

    // 
    node_map_t::ConstIterator iter = m_NodeMap.Begin();
    node_map_t::ConstIterator iterComp = mapNode.m_NodeMap.Begin();
    while ( iter != m_NodeMap.End() || iterComp != mapNode.m_NodeMap.End() )
    {
        result = (iter.GetKey())->Compare( *((iterComp.GetKey()).GetPtr()) );
        if ( result != 0 )
        {
            return result;
        }

        result = (*iter)->Compare( *((*iterComp).GetPtr()) );
        if ( result != 0 ) 
        {
            return result;
        }

        ++iter;
        ++iterComp;
    }

    return result;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::smart_ptr_t CYamlMap::GetNode ( const char* _key ) const
{
    CYamlNode::smart_ptr_t spNode ( ex_new CYamlScalar(_key) );
    node_map_t::ConstIterator iter = m_NodeMap.Find ( spNode );
    if ( iter != m_NodeMap.End() )
        return (*iter);

    return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::smart_ptr_t CYamlMap::GetNode ( const CYamlNode::smart_ptr_t& _key ) const
{
    node_map_t::ConstIterator iter = m_NodeMap.Find ( _key );
    if ( iter != m_NodeMap.End() )
        return (*iter);

    return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlMap::SaveToFile ( yaml_emitter_t* _pEmitter ) const
{
    result_t result_t = eResult_OK;

    yaml_event_t event;

    yaml_mapping_start_event_initialize( &event, (yaml_char_t*)GetAnchor(), (yaml_char_t*)GetTag(), 1, CYamlMap::ToYamlStyle(m_Style) );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );

    // save children
    for ( node_map_t::ConstIterator iter = m_NodeMap.Begin(); iter != m_NodeMap.End(); ++iter )
    {
        (*iter)->SaveToFile (_pEmitter);
    }

    yaml_mapping_end_event_initialize( &event );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

yaml_mapping_style_t CYamlMap::ToYamlStyle ( CYamlMap::EStyle _style )
{
    switch ( _style )
    {
    case eStyle_Block:
        return YAML_BLOCK_MAPPING_STYLE;

    case eStyle_Flow:
        return YAML_FLOW_MAPPING_STYLE;

    default:
        return YAML_ANY_MAPPING_STYLE;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlMap::EStyle CYamlMap::FromYamlStyle ( yaml_mapping_style_t _style )
{
    switch ( _style )
    {
    case YAML_BLOCK_MAPPING_STYLE:
        return eStyle_Block;

    case YAML_FLOW_MAPPING_STYLE:
        return eStyle_Flow;

    default:
        return eStyle_Block;
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

