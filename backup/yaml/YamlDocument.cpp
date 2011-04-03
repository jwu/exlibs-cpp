// ======================================================================================
// File         : YamlDocument.cpp
// Author       : Wu Jie 
// Last Change  : 10/02/2009 | 19:34:52 PM | Friday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "YamlDocument.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlDocument::CYamlDocument ()
    : CYamlNode () 
    , m_Implicit (false)
{
    m_Type = eType_Document;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlDocument::~CYamlDocument ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CYamlDocument::AddChild ( const CYamlNode::smart_ptr_t& _spNode )
{
    m_Children.PushBack (_spNode);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int CYamlDocument::Compare ( const CYamlNode& _node )
{
    ex_warning( "Can't compare document node." );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlNode::smart_ptr_t CYamlDocument::GetNode ( int _idx ) const
{
    if ( _idx < int(m_Children.Size()) )
    {
        uint i = 0;
        for ( yaml_nodes_t::ConstIterator iter = m_Children.Begin(); iter != m_Children.End(); ++iter, ++i )
        {
            if ( i == _idx )
                return (*iter);
        }
    }

    return CYamlNode::smart_ptr_t(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlDocument::SaveToFile ( yaml_emitter_t* _pEmitter ) const
{
    result_t result_t = eResult_OK;

    yaml_event_t event;

    // doc start
    yaml_tag_directive_t tag_directive;
    tag_directive.handle = (yaml_char_t*)"!";
    tag_directive.prefix = (yaml_char_t*)(m_Tag.c_str());
    yaml_document_start_event_initialize ( &event, NULL, &tag_directive, NULL, int(m_Implicit) );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );

    // save children
    for ( yaml_nodes_t::ConstIterator iter = m_Children.Begin(); iter != m_Children.End(); ++iter )
    {
        (*iter)->SaveToFile ( _pEmitter );
    }

    // doc end
    yaml_document_end_event_initialize ( &event, int(m_Implicit) );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );

    return eResult;
}

// ######################### 
} // end namespace ex 
// ######################### 

