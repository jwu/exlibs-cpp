// ======================================================================================
// File         : YamlParser.cpp
// Author       : Wu Jie 
// Last Change  : 10/01/2009 | 12:24:19 PM | Thursday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "YamlParser.h"
#include "YamlDocument.h"
#include "YamlScalar.h"
#include "YamlSequence.h"
#include "YamlMap.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlParser::CYamlParser ()
{
    int result = yaml_parser_initialize(&m_Parser);  
    ex_assert( result == 1, "Failed to initialize yaml parser" );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlParser::~CYamlParser ()
{
    yaml_parser_delete(&m_Parser);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CYamlParser::Parse( const uint8* _pBuffer, uint _size )
{
    //
    yaml_event_t event;
    int done = 0;
    int count = 0;
    int error = 0;

    // clear the stack to make sure we parse node from beginning.
    m_ProcessingNodeStack.Clear();
    m_AliasToNode.Clear();

    // process parsing
    yaml_parser_set_input_string( &m_Parser, _pBuffer, size_t(_size) );
    while ( !done )
    {
        if ( !yaml_parser_parse(&m_Parser, &event) ) 
        {
            ex_error ( "yaml parse error: %s at line: %d, col: %d\n", m_Parser.problem, m_Parser.problem_mark.line+1, m_Parser.problem_mark.column+1 );
            error = 1;
            break;
        }

        done = ProcessEvent ( event );

        yaml_event_delete(&event);
        ++count;
    }
    printf("yaml parse %s (%d events)\n", (error ? "failed" : "successed"), count);

    // 
    m_AliasToNode.Clear();
    ex_assert ( m_ProcessingNodeStack.Size() == 0, "yaml parse error: node stack is not empty, there still have unprocessing node." );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CYamlParser::ParseFile( const char* _filename )
{

    // open file
    ex::IFile::smart_ptr_t spFile = futil::file::open<CPhysicalFile>(_filename);
    if ( spFile )
    {
        uint8* pBuffer = (uint8*)ex_malloc( uint32(spFile->Size()) );
        spFile->read ( pBuffer, uint(spFile->Size()) );

        //
        Parse ( pBuffer, uint(spFile->Size()) );

        ex_free (pBuffer);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool CYamlParser::ProcessEvent( const yaml_event_t& _event )
{
    bool done = false;
    CYamlNode::smart_ptr_t spNode;

    // alias & scalar
    if ( _event.type == YAML_SCALAR_EVENT )
    {
        spNode = CYamlNode::smart_ptr_t ( ex_new CYamlScalar( reinterpret_cast<char*>(_event.data.scalar.value),
                                                              CYamlScalar::FromYamlStyle (_event.data.scalar.style),
                                                              reinterpret_cast<char*>(_event.data.scalar.anchor), 
                                                              reinterpret_cast<char*>(_event.data.scalar.tag) ) );
        if ( _event.data.scalar.anchor )
        {
            m_AliasToNode.Insert( reinterpret_cast<char*>( _event.data.scalar.anchor ), spNode );
        }

        m_ProcessingNodeStack.Top()->AddChild(spNode);
    }
    else if ( _event.type == YAML_ALIAS_EVENT )
    {
        spNode = *(m_AliasToNode.Find( reinterpret_cast<char*>(_event.data.alias.anchor) ));
        m_ProcessingNodeStack.Top()->AddChild(spNode);
    }

    // sequence
    else if ( _event.type == YAML_SEQUENCE_START_EVENT )
    {
        spNode = CYamlNode::smart_ptr_t ( ex_new CYamlSequence( CYamlSequence::FromYamlStyle (_event.data.sequence_start.style),
                                                                reinterpret_cast<char*>(_event.data.sequence_start.anchor), 
                                                                reinterpret_cast<char*>(_event.data.sequence_start.tag) ) );
        if ( _event.data.sequence_start.anchor )
        {
            m_AliasToNode.Insert( reinterpret_cast<char*>(_event.data.sequence_start.anchor), spNode );
        }

        m_ProcessingNodeStack.Top()->AddChild(spNode);
        m_ProcessingNodeStack.Push ( spNode );
    }
    else if ( _event.type == YAML_SEQUENCE_END_EVENT )
    {
        m_ProcessingNodeStack.Pop ();
    }

    // mapping
    else if ( _event.type == YAML_MAPPING_START_EVENT )
    {
        spNode = CYamlNode::smart_ptr_t ( ex_new CYamlMap( CYamlMap::FromYamlStyle (_event.data.mapping_start.style),
                                                           reinterpret_cast<char*>(_event.data.mapping_start.anchor), 
                                                           reinterpret_cast<char*>(_event.data.mapping_start.tag) ) );
        if ( _event.data.mapping_start.anchor )
        {
            m_AliasToNode.Insert( reinterpret_cast<char*>(_event.data.mapping_start.anchor), spNode );
        }

        m_ProcessingNodeStack.Top()->AddChild(spNode);
        m_ProcessingNodeStack.Push ( spNode );
    }
    else if ( _event.type == YAML_MAPPING_END_EVENT )
    {
        m_ProcessingNodeStack.Pop ();
    }

    // document
    else if ( _event.type == YAML_DOCUMENT_START_EVENT )
    {
        spNode = CYamlNode::smart_ptr_t( ex_new CYamlDocument() );
        // DISABLE { 
        // if ( _event.data.document_start.tag_directives.start )
        // {
        //     spNode->SetTag ( reinterpret_cast<char*>( _event.data.document_start.tag_directives.start.prefix ) );
        // }
        // } DISABLE end 

        m_Documents.PushBack ( spNode );
        m_ProcessingNodeStack.Push ( spNode );
    }
    else if ( _event.type == YAML_DOCUMENT_END_EVENT )
    {
        m_ProcessingNodeStack.Pop ();
    }

    // stream
    if ( _event.type == YAML_STREAM_START_EVENT )
    {
        // TODO: encoding
        // yaml_encoding_t encoding = _event.data.stream_start.encoding;
    }
    else if ( _event.type == YAML_STREAM_END_EVENT )
    {
        done = true;
    }

    return done;
}

// ######################### 
} // end namespace ex 
// ######################### 



