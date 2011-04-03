// ======================================================================================
// File         : YamlSequence.h
// Author       : Wu Jie 
// Last Change  : 10/03/2009 | 23:55:46 PM | Saturday,October
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef YAMLSEQUENCE_H_1254626539
#define YAMLSEQUENCE_H_1254626539
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "YamlNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CYamlSequence 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL CYamlSequence : public CYamlNode
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef CYamlSequence self_t;
    typedef CYamlNode base_t;

    typedef Array< CYamlNode::smart_ptr_t > nodes_t;

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

    static yaml_sequence_style_t ToYamlStyle ( CYamlSequence::EStyle _style );
    static CYamlSequence::EStyle FromYamlStyle ( yaml_sequence_style_t _style );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    CYamlSequence ( CYamlSequence::EStyle _style = CYamlSequence::eStyle_Block, const char* _anchor = NULL, const char* _tag = NULL );
    virtual ~CYamlSequence ();

    virtual void AddChild ( const CYamlNode::smart_ptr_t& _spNode );
    virtual int Compare ( const CYamlNode& _node ) const;

    //
    virtual CYamlNode::smart_ptr_t GetNode ( int _idx ) const;

    //
    void SetStyle ( CYamlSequence::EStyle _style ) { m_Style = _style; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    virtual result_t SaveToFile ( yaml_emitter_t* _pEmitter ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    nodes_t m_Nodes;

    CYamlSequence::EStyle m_Style;

}; // end class CYamlSequence

// ######################### 
} // end namespace ex 
// ######################### 



// #################################################################################
#endif // END YAMLSEQUENCE_H_1254626539
// #################################################################################

