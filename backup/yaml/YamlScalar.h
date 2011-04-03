// ======================================================================================
// File         : YamlScalar.h
// Author       : Wu Jie 
// Last Change  : 10/03/2009 | 00:59:19 AM | Saturday,October
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef YAMLSCALAR_H_1254502766
#define YAMLSCALAR_H_1254502766
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "YamlNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CYamlScalar 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL CYamlScalar : public CYamlNode
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef CYamlScalar self_t;
    typedef CYamlNode base_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    enum EStyle
    {
        eStyle_Plain,
        eStyle_SingleQuoted,
        eStyle_DoubleQuoted,
        eStyle_Literal,
        eStyle_Folded,
    }; // end enum EStyle 

    ///////////////////////////////////////////////////////////////////////////////
    // static public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static yaml_scalar_style_t ToYamlStyle ( CYamlScalar::EStyle _style );
    static CYamlScalar::EStyle FromYamlStyle ( yaml_scalar_style_t _style );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    CYamlScalar ( const char* _value = NULL, CYamlScalar::EStyle _style = CYamlScalar::eStyle_Plain, const char* _anchor = NULL, const char* _tag = NULL );
    virtual ~CYamlScalar ();

    virtual void AddChild ( const CYamlNode::smart_ptr_t& _spNode );
    virtual int Compare ( const CYamlNode& _node ) const;

    //
    virtual const char* GetValue () const { return m_Value.c_str(); }

    //
    void SetStyle ( CYamlScalar::EStyle _style ) { m_Style = _style; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    virtual result_t SaveToFile ( yaml_emitter_t* _pEmitter ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    string_t    m_Value;
    CYamlScalar::EStyle m_Style;

}; // end class CYamlScalar

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END YAMLSCALAR_H_1254502766
// #################################################################################


