// ======================================================================================
// File         : YamlSequence.cpp
// Author       : Wu Jie 
// Last Change  : 10/03/2009 | 23:55:48 PM | Saturday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "YamlSequence.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlSequence::CYamlSequence ( CYamlSequence::EStyle _style, const char* _anchor, const char* _tag )
    : CYamlNode ( _anchor, _tag ) 
    , m_Style ( _style )
{
    m_Type = eType_Sequence;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlSequence::~CYamlSequence ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 


void CYamlSequence::AddChild ( const CYamlNode::smart_ptr_t& _spNode )
{
    m_Nodes.PushBack (_spNode);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int CYamlSequence::Compare ( const CYamlNode& _node ) const
{
    //
    int result = base_t::Compare (_node);
    if ( result != 0 )
    {
        return result;
    }

    // 
    const CYamlSequence& seqNode = static_cast<const CYamlSequence&>(_node);
    if ( m_Nodes.Size() != seqNode.m_Nodes.Size() )
    {
        return m_Nodes.Size() < seqNode.m_Nodes.Size() ? -1 : 1; 
    }

    // 
    nodes_t::ConstIterator iter = m_Nodes.Begin();
    nodes_t::ConstIterator iterComp = seqNode.m_Nodes.Begin();
    while ( iter != m_Nodes.End() || iterComp != seqNode.m_Nodes.End() )
    {
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

CYamlNode::smart_ptr_t CYamlSequence::GetNode ( int _idx ) const
{
    if ( _idx < int(m_Nodes.Size()) )
        return m_Nodes[_idx];
    else
        return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlSequence::SaveToFile ( yaml_emitter_t* _pEmitter ) const
{
    result_t result_t = eResult_OK;

    yaml_event_t event;

    yaml_sequence_start_event_initialize( &event, (yaml_char_t*)GetAnchor(), (yaml_char_t*)GetTag(), 1, CYamlSequence::ToYamlStyle(m_Style) );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );

    // save children
    for ( nodes_t::ConstIterator iter = m_Nodes.Begin(); iter != m_Nodes.End(); ++iter )
    {
        (*iter)->SaveToFile (_pEmitter);
    }

    yaml_sequence_end_event_initialize( &event );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

yaml_sequence_style_t CYamlSequence::ToYamlStyle ( CYamlSequence::EStyle _style )
{
    switch ( _style )
    {
    case eStyle_Block:
        return YAML_BLOCK_SEQUENCE_STYLE;

    case eStyle_Flow:
        return YAML_FLOW_SEQUENCE_STYLE;

    default:
        return YAML_ANY_SEQUENCE_STYLE;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlSequence::EStyle CYamlSequence::FromYamlStyle ( yaml_sequence_style_t _style )
{
    switch ( _style )
    {
    case YAML_BLOCK_SEQUENCE_STYLE:
        return eStyle_Block;

    case YAML_FLOW_SEQUENCE_STYLE:
        return eStyle_Flow;

    default:
        return eStyle_Block;
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

