// ======================================================================================
// File         : TestData.cpp
// Author       : Wu Jie 
// Last Change  : 08/29/2010 | 10:39:29 AM | Sunday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "TestData.h"

///////////////////////////////////////////////////////////////////////////////
// properties
///////////////////////////////////////////////////////////////////////////////

EX_DEF_PROPERTIES_BEGIN_NS (TestData)
    EX_REGISTER_PROPERTY_ATTRS ( "ID", m_ID, ex::PropAttr::none )
    EX_REGISTER_PROPERTY_ATTRS ( "tag", m_tag, ex::PropAttr::none )
    EX_REGISTER_PROPERTY_ATTRS ( "action", m_action, ex::PropAttr::none )
    EX_REGISTER_PROPERTY_ATTRS ( "magic", m_magic, ex::PropAttr::none )
    EX_REGISTER_PROPERTY_ATTRS ( "hp", m_hp, ex::PropAttr::none )
    EX_REGISTER_PROPERTY_ATTRS ( "mp", m_mp, ex::PropAttr::none )
EX_DEF_PROPERTIES_END()

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TestData::TestData ()        
    : m_ID (-1)
    , m_tag ("unknown")
    , m_action (-1)
    , m_magic (-1)
    , m_hp (10)
    , m_mp (10)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TestData::~TestData ()        
{
}


