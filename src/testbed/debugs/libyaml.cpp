// ======================================================================================
// File         : libyaml.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 15:02:35 PM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

// DISABLE { 
#if 0

#pragma comment( lib, "../../ext/libyaml/lib/yaml.lib" )

#ifndef YAML_DECLARE_STATIC
#define YAML_DECLARE_STATIC
#endif

#include "libyaml/inc/yaml.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( libyaml, emitter, off )
{
    const char* fileName = "res/yaml/debug-emitter.yaml";

    int canonical = 0;
    int unicode = 0;

    const static ex::uint BUFFER_SIZE = 65536; 
    const static ex::uint MAX_EVENTS = 1024;

    yaml_emitter_t emitter;
    unsigned char buffer[BUFFER_SIZE];
    size_t written = 0;
    yaml_event_t events[MAX_EVENTS];
    int done = 0;
    int count = 0;
    int error = 0;
    memset(buffer, 0, BUFFER_SIZE);
    memset(events, 0, MAX_EVENTS*sizeof(yaml_event_t));

    ex_assert ( yaml_emitter_initialize(&emitter), "" );
    if (canonical) {
        yaml_emitter_set_canonical(&emitter, 1);
    }
    if (unicode) {
        yaml_emitter_set_unicode(&emitter, 1);
    }
    yaml_emitter_set_output_string(&emitter, buffer, BUFFER_SIZE, &written);

    // init events
    ex::uint eventCount = 0;
    {
        // stream start
        yaml_stream_start_event_initialize ( &events[eventCount++], YAML_UTF8_ENCODING );

        // doc start
        yaml_document_start_event_initialize ( &events[eventCount++], 0, 0, 0, 0 );

        // 
        yaml_mapping_start_event_initialize( &events[eventCount++], NULL, NULL, 1, YAML_BLOCK_MAPPING_STYLE );

        // ID:
        yaml_scalar_event_initialize ( &events[eventCount++], NULL, NULL, (yaml_char_t*)"ID", 2, 1, 0, YAML_PLAIN_SCALAR_STYLE );

        //   name: wu jie
        yaml_mapping_start_event_initialize( &events[eventCount++], NULL, NULL, 1, YAML_BLOCK_MAPPING_STYLE );
        yaml_scalar_event_initialize ( &events[eventCount++], NULL, NULL, (yaml_char_t*)"name", 4, 1, 0, YAML_PLAIN_SCALAR_STYLE );
        yaml_scalar_event_initialize ( &events[eventCount++], NULL, NULL, (yaml_char_t*)"wu jie", 6, 1, 0, YAML_PLAIN_SCALAR_STYLE );
        yaml_mapping_end_event_initialize( &events[eventCount++] );

        // ID:
        yaml_scalar_event_initialize ( &events[eventCount++], NULL, NULL, (yaml_char_t*)"ID", 2, 1, 0, YAML_PLAIN_SCALAR_STYLE );

        //   name: karas
        yaml_mapping_start_event_initialize( &events[eventCount++], NULL, NULL, 1, YAML_BLOCK_MAPPING_STYLE );
        yaml_scalar_event_initialize ( &events[eventCount++], NULL, NULL, (yaml_char_t*)"name", 4, 1, 0, YAML_PLAIN_SCALAR_STYLE );
        yaml_scalar_event_initialize ( &events[eventCount++], NULL, NULL, (yaml_char_t*)"karas", 5, 1, 0, YAML_PLAIN_SCALAR_STYLE );
        yaml_mapping_end_event_initialize( &events[eventCount++] );

        //
        yaml_mapping_end_event_initialize( &events[eventCount++] );

        // doc end
        yaml_document_end_event_initialize ( &events[eventCount++], 1 );

        // stream end
        yaml_stream_end_event_initialize ( &events[eventCount++] );
    }

    //
    for ( ex::uint i = 0; i < eventCount; ++i )
    {
        ex_assert ( yaml_emitter_emit(&emitter, &events[i]) || 
                    ( yaml_emitter_flush(&emitter) /*&& print_output(argv[number], buffer, written, count)*/ ), "" );
        ++count;
    }

    //
    FILE *file;
    file = fopen( fileName , "wb");
    ex_assert ( file, "" );
    ex_assert ( fwrite ( buffer, 1, written, file ) == written, "failed to write to file" );
    ex_assert ( !fclose(file), "" );
    yaml_emitter_delete(&emitter);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( libyaml, parser, off )
{
    const char* fileName = "res/yaml/unit-testing.yaml";

    FILE *file;

    yaml_parser_t parser;
    yaml_event_t event;
    // yaml_document_t document;

    int done = 0;
    int count = 0;
    int error = 0;

    printf("Parsing '%s': ", fileName);
    fflush(stdout);

    file = fopen(fileName, "rb");
    ex_assert(file,"");

    ex_assert(yaml_parser_initialize(&parser), "");

    yaml_parser_set_input_file(&parser, file);

    // DISABLE { 
    // ex::IFile::smart_ptr_t spFile = futil::file::open<PhysicalFile>(fileName);
    // if ( spFile )
    // {
    //      uint8* pBuffer = (uint8*)ex_malloc( ex::uint32(spFile->size()) );
    //      spFile->read ( pBuffer, ex::uint32(spFile->size()) );
    //      yaml_parser_set_input_string( &parser, pBuffer, size_t(spFile->size()) );
    // }
    // } DISABLE end 

#if 1
    while (!done)
    {
        if (!yaml_parser_parse(&parser, &event)) {
            printf("\treader error: %s at line: %d, col: %d\n", parser.problem, parser.problem_mark.line+1, parser.problem_mark.column+1 );
            error = 1;
            break;
        }

        done = (event.type == YAML_STREAM_END_EVENT);

        yaml_event_delete(&event);

        count ++;
    }
#else
    while (!done)
    {
        if (!yaml_parser_load(&parser, &document)) {
            printf("\treader error: %s at line: %d, col: %d\n", parser.problem, parser.problem_mark.line+1, parser.problem_mark.column+1 );
            error = 1;
            break;
        }

        done = (!yaml_document_get_root_node(&document));

        yaml_document_delete(&document);

        if (!done) count ++;
    }
#endif


    yaml_parser_delete(&parser);

    // DISABLE: ex_free (pBuffer);

    ex_assert(!fclose(file), "");

    printf("%s (%d events)\n", (error ? "FAILURE" : "SUCCESS"), count);
}
#endif

// } DISABLE end 
