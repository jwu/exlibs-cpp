// ======================================================================================
// File         : YamlScalar.cpp
// Author       : Wu Jie 
// Last Change  : 10/03/2009 | 10:46:43 AM | Saturday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
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

CYamlScalar::CYamlScalar ( const char* _value, CYamlScalar::EStyle _style, const char* _anchor, const char* _tag )
    : CYamlNode ( _anchor, _tag ) 
    , m_Style (_style)
{
    if ( _value )
        m_Value.assign (_value);
    m_Type = eType_Scalar;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlScalar::~CYamlScalar ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CYamlScalar::AddChild ( const CYamlNode::smart_ptr_t& _spNode )
{
    ex_warning ( "Scalar don't have child" );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int CYamlScalar::Compare ( const CYamlNode& _node ) const
{
    //
    int result = base_t::Compare (_node);
    if ( result != 0 )
    {
        return result;
    }

    // 
    const CYamlScalar& scalarNode = static_cast<const CYamlScalar&>(_node);
    if ( m_Value < scalarNode.m_Value )
        return -1;
    else if( m_Value > scalarNode.m_Value )
        return 1;
    else
        return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlScalar::SaveToFile ( yaml_emitter_t* _pEmitter ) const
{
    result_t result_t = eResult_OK;

    yaml_event_t event;

    yaml_scalar_event_initialize ( &event, (yaml_char_t*)GetAnchor(), (yaml_char_t*)GetTag(), (yaml_char_t*)GetValue(), int(m_Value.Size()), 1, 0, CYamlScalar::ToYamlStyle(m_Style) );
    ex_check_return ( Flush( _pEmitter, &event ), "Flush failed" );

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

yaml_scalar_style_t CYamlScalar::ToYamlStyle ( CYamlScalar::EStyle _style )
{
    switch ( _style )
    {
    case eStyle_Plain:
        return YAML_PLAIN_SCALAR_STYLE;

    case eStyle_SingleQuoted:
        return YAML_SINGLE_QUOTED_SCALAR_STYLE;

    case eStyle_DoubleQuoted:
        return YAML_DOUBLE_QUOTED_SCALAR_STYLE;

    case eStyle_Literal:
        return YAML_LITERAL_SCALAR_STYLE;

    case eStyle_Folded:
        return YAML_FOLDED_SCALAR_STYLE;

    default:
        return YAML_ANY_SCALAR_STYLE;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlScalar::EStyle CYamlScalar::FromYamlStyle ( yaml_scalar_style_t _style )
{
    switch ( _style )
    {
    case YAML_PLAIN_SCALAR_STYLE:
        return eStyle_Plain;

    case YAML_SINGLE_QUOTED_SCALAR_STYLE:
        return eStyle_SingleQuoted;

    case YAML_DOUBLE_QUOTED_SCALAR_STYLE:
        return eStyle_DoubleQuoted;

    case YAML_LITERAL_SCALAR_STYLE:
        return eStyle_Literal;

    case YAML_FOLDED_SCALAR_STYLE:
        return eStyle_Folded;

    default:
        return eStyle_Plain;
    }
}

// ######################### 
} // end namespace ex 
// ######################### 


