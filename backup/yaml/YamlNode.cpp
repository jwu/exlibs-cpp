// ======================================================================================
// File         : YamlNode.cpp
// Author       : Wu Jie 
// Last Change  : 10/02/2009 | 19:43:33 PM | Friday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "YamlNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::CYamlNode ( const char* _anchor, const char* _tag )
    : m_Type (eType_Unknown)
{
    if ( _anchor )
        m_Anchor.assign(_anchor);
    if ( _tag )
        m_Tag.assign(_tag);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::~CYamlNode ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int CYamlNode::Compare ( const CYamlNode& _node ) const
{
    if ( m_Type != _node.m_Type )
    {
        return m_Type < _node.m_Type ? -1 : 1; 
    }

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::smart_ptr_t CYamlNode::GetNode ( int _idx ) const
{
    ex_warning ( "can't get node by index" );
    return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::smart_ptr_t CYamlNode::GetNode ( const char* _key ) const
{
    ex_warning ( "can't get node by string" );
    return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::smart_ptr_t CYamlNode::GetNode ( const CYamlNode::smart_ptr_t& _key ) const
{
    ex_warning ( "can't get node by node" );
    return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char* CYamlNode::GetValue () const
{
    ex_warning ( "can't get value from this node" );
    return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlNode::SaveToFile ( yaml_emitter_t* _pEmitter ) const
{
    ex_warning ( "unknown node" );
    return eResult_Failed;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlNode::Flush ( yaml_emitter_t* _pEmitter, yaml_event_t* _pEvent ) const
{
    result_t result_t = eResult_OK;

    int result = yaml_emitter_emit ( _pEmitter, _pEvent ) || yaml_emitter_flush ( _pEmitter );
    if ( result == 0 )
        return eResult_Failed;

    return eResult;
}

// ######################### 
} // end namespace ex 
// ######################### 


