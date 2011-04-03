// ======================================================================================
// File         : expat.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 14:37:21 PM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#if (EX_COMPILER == EX_MSVC)
#pragma comment( lib, "../../ext/expat/lib/libexpatMT.lib" )
#endif

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

#define BUFFSIZE        EX_KB(10)

char Buff[BUFFSIZE];
int Depth;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// ========================================================
// start
// ========================================================

static void XMLCALL start(void *data, const char *el, const char **attr)
{
    int i;

    for (i = 0; i < Depth; i++)
        printf("  ");

    printf("%s", el);

    for (i = 0; attr[i]; i += 2) {
        printf(" %s='%s'", attr[i], attr[i + 1]);
    }

    printf("\n");
    Depth++;
}

// ========================================================
// end
// ========================================================

static void XMLCALL end(void *data, const char *el)
{
    Depth--;
}

// ========================================================
// TEST
// ========================================================

TEST( expat, test, off )
{
    XML_Parser p = XML_ParserCreate(NULL);
    if (! p) 
    {
        fprintf(stderr, "Couldn't allocate memory for parser\n");
        exit(-1);
    }

    //
    XML_SetElementHandler(p, start, end);

    //
    ex::IFile::smart_ptr_t spFile = ex::futil::file::open<ex::PhysicalFile>("./test.xml");

    if ( spFile )
    {
        int len;
        spFile->read( Buff, ex::uint32(spFile->size()) );
        len = int(spFile->size());
        spFile->close();

        //
        if (XML_Parse(p, Buff, len, 1) == XML_STATUS_ERROR)
        {
            fprintf( stderr, "Parse error at line %" XML_FMT_INT_MOD "u:\n%s\n", XML_GetCurrentLineNumber(p), XML_ErrorString(XML_GetErrorCode(p)) );
        }

        //
        XML_ParserFree(p);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static ex::uint node_count = 0;

void RecordNodes( ex::IFile* _pFile, ex::uint32 _level, ex::XmlNode::smart_ptr_t _parent )
{
    _level += 1;

    if ( _parent )
    {
        ex::string_t tag = _parent->tag(); 

        if ( tag == "Node" )
        {
            ex::string_t text = ex::string_t().printf( "%*sNode[%d]\n", _level*2, "", node_count );
            _pFile->write( text.c_str(), ex::uint32(text.size()) );
            node_count++;
        }

        if ( _parent->childCount() != 0 )
        {
            for ( ex::uint i = 0; i < _parent->childCount(); ++i )
            {
                RecordNodes( _pFile, _level, _parent->child(i) );
            }
        }
    }

    _level -= 1;
}
