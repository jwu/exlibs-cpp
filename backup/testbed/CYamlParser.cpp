// ======================================================================================
// File         : CYamlParser.cpp
// Author       : Wu Jie 
// Last Change  : 10/04/2009 | 13:30:26 PM | Sunday,October
// Description  : 
// ======================================================================================

#include "testbed.h"

// DISABLE { 
#if 0
///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs/Yaml/YamlParser.h"
#include "exlibs/Yaml/YamlScalar.h"
#include "exlibs/Yaml/YamlSequence.h"
#include "exlibs/Yaml/YamlMap.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST ( CYamlParser, Parse )
{
    //
    const char* fileName = "res/yaml/unit-testing.yaml";
    ex::CYamlParser parser;
    parser.ParseFile ( fileName );
    const ex::CYamlParser::yaml_documents_t& docs = parser.GetDocuments();

    uint idx = 0;
    // example 0
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);
        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode("index");

        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("Mark McGwire") );
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("Sammy Sosa") );
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("Ken Griffey") );

        ++idx;
    }

    // example 1 
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("hr")->GetValue() == ex::string_t("65") );
        CHECK ( spRoot->GetNode("avg")->GetValue() == ex::string_t("0.278") );
        CHECK ( spRoot->GetNode("rbi")->GetValue() == ex::string_t("147") );

        ++idx;
    }

    // example 2
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode("american");
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("Boston Red Sox") );
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("Detroit Tigers") );
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("New York Yankees") );

        spNode = spRoot->GetNode("national");
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("New York Mets") );
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("Chicago Cubs") );
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("Atlanta Braves") );

        ++idx;
    }
    
    // example 3
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode(0);
        CHECK ( spNode->GetNode("name")->GetValue() == ex::string_t("Mark McGwire") ); 
        CHECK ( spNode->GetNode("hr")->GetValue() == ex::string_t("65") ); 
        CHECK ( spNode->GetNode("avg")->GetValue() == ex::string_t("0.278") ); 

        spNode = spRoot->GetNode(1);
        CHECK ( spNode->GetNode("name")->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spNode->GetNode("hr")->GetValue() == ex::string_t("63") ); 
        CHECK ( spNode->GetNode("avg")->GetValue() == ex::string_t("0.288") ); 

        ++idx;
    }

    // example 4
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode(0);
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("name") ); 
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("hr") ); 
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("avg") ); 

        spNode = spRoot->GetNode(1);
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("Mark McGwire") ); 
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("65") ); 
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("0.278") ); 

        spNode = spRoot->GetNode(2);
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("63") ); 
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("0.288") ); 

        ++idx;
    }

    // example 5
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode("Mark McGwire");
        CHECK ( spNode->GetNode("hr")->GetValue() == ex::string_t("65") ); 
        CHECK ( spNode->GetNode("avg")->GetValue() == ex::string_t("0.278") ); 

        spNode = spRoot->GetNode("Sammy Sosa");
        CHECK ( spNode->GetNode("hr")->GetValue() == ex::string_t("63") ); 
        CHECK ( spNode->GetNode("avg")->GetValue() == ex::string_t("0.288") ); 

        ++idx;
    }

    // example 6
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode(0)->GetValue() == ex::string_t("Mark McGwire") ); 
        CHECK ( spRoot->GetNode(1)->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spRoot->GetNode(2)->GetValue() == ex::string_t("Ken Griffey") ); 

        ++idx;

        spDoc = docs[idx];
        spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode(0)->GetValue() == ex::string_t("Chicago Cubs") ); 
        CHECK ( spRoot->GetNode(1)->GetValue() == ex::string_t("St Louis Cardinals") ); 

        ++idx;
    }

    // example 7
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("time")->GetValue() == ex::string_t("20:03:20") ); 
        CHECK ( spRoot->GetNode("player")->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spRoot->GetNode("action")->GetValue() == ex::string_t("strike (miss)") ); 

        ++idx;

        spDoc = docs[idx];
        spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("time")->GetValue() == ex::string_t("20:03:47") ); 
        CHECK ( spRoot->GetNode("player")->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spRoot->GetNode("action")->GetValue() == ex::string_t("grand slam") ); 

        ++idx;
    }

    // example 8
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode("hr");
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("Mark McGwire") ); 
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("Sammy Sosa") ); 

        spNode = spRoot->GetNode("rbi");
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("Ken Griffey") ); 

        ++idx;
    }

    // example 9
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode1 = spRoot->GetNode("hr");
        CHECK ( spNode1->GetNode(0)->GetValue() == ex::string_t("Mark McGwire") ); 
        CHECK ( spNode1->GetNode(1)->GetValue() == ex::string_t("Sammy Sosa") ); 

        ex::CYamlNode::smart_ptr_t spNode2 = spRoot->GetNode("rbi");
        CHECK ( spNode2->GetNode(0)->GetValue() == ex::string_t("Sammy Sosa") ); 
        CHECK ( spNode2->GetNode(1)->GetValue() == ex::string_t("Ken Griffey") ); 

        CHECK ( spNode1->GetNode(1) == spNode2->GetNode(0) ); 

        ++idx;
    }

    // example 10
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spKey ( ex_new ex::CYamlSequence() );
        spKey->AddChild ( ex::CYamlNode::smart_ptr_t ( ex_new ex::CYamlScalar("Detroit Tigers") ) );
        spKey->AddChild ( ex::CYamlNode::smart_ptr_t ( ex_new ex::CYamlScalar("Chicago cubs") ) );
            
        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode(spKey);
        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("2001-07-23") ); 

        spKey = ex::CYamlNode::smart_ptr_t ( ex_new ex::CYamlSequence() );
        spKey->AddChild ( ex::CYamlNode::smart_ptr_t ( ex_new ex::CYamlScalar("New York Yankees") ) );
        spKey->AddChild ( ex::CYamlNode::smart_ptr_t ( ex_new ex::CYamlScalar("Atlanta Braves") ) );

        spNode = spRoot->GetNode(spKey);

        CHECK ( spNode->GetNode(0)->GetValue() == ex::string_t("2001-07-02") ); 
        CHECK ( spNode->GetNode(1)->GetValue() == ex::string_t("2001-08-12") ); 
        CHECK ( spNode->GetNode(2)->GetValue() == ex::string_t("2001-08-14") ); 

        ++idx;
    }

    // example 11
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode(0);
        CHECK ( spNode->GetNode("item")->GetValue() == ex::string_t("Super Hoop") ); 
        CHECK ( spNode->GetNode("quantity")->GetValue() == ex::string_t("1") ); 

        spNode = spRoot->GetNode(1);
        CHECK ( spNode->GetNode("item")->GetValue() == ex::string_t("Basketball") ); 
        CHECK ( spNode->GetNode("quantity")->GetValue() == ex::string_t("4") ); 

        spNode = spRoot->GetNode(2);
        CHECK ( spNode->GetNode("item")->GetValue() == ex::string_t("Big Shoes") ); 
        CHECK ( spNode->GetNode("quantity")->GetValue() == ex::string_t("1") ); 

        ++idx;
    }

    // example 12
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetValue() == ex::string_t("\\//||\\/||\n// ||  ||__\n") ); 

        ++idx;
    }

    // example 13
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetValue() == ex::string_t("Mark McGwires year was crippled by a knee injury.") ); 

        ++idx;
    }

    // example 14
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        const char* str = 
            "Sammy Sosa completed another fine season with great stats.\n"
            "\n"
            "  63 Home Runs\n"
            "  0.288 Batting Average\n"
            "\n"
            "What a year!\n";
        CHECK ( spRoot->GetValue() == ex::string_t(str) ); 

        ++idx;
    }

    // example 15
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("name")->GetValue() == ex::string_t("Mark McGwire") ); 
        CHECK ( spRoot->GetNode("accomplishment")->GetValue() == ex::string_t("Mark set a major league home run record in 1998.\n") ); 
        CHECK ( spRoot->GetNode("stats")->GetValue() == ex::string_t("65 Home Runs\n0.278 Batting Average\n") ); 

        ++idx;
    }

    // example 16
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        // TODO: should use libiconv convert str to wstr. { 
        // const char* str = spRoot->GetNode("unicode")->GetValue();
        // ex::wstring_t wstr = ex::wstring_t(L"Sosa did fine.\u263A"); 
        // DISABLE: CHECK ( spRoot->GetNode("unicode")->GetValue() == ex::string_t("Sosa did fine.\u263A") ); 
        // } TODO end 

        CHECK ( spRoot->GetNode("control")->GetValue() == ex::string_t("\b1998\t1999\t2000\n") ); 
        CHECK ( spRoot->GetNode("hexesc")->GetValue() == ex::string_t("\x13\x10 is \r\n") ); 
        CHECK ( spRoot->GetNode("single")->GetValue() == ex::string_t("\"Howdy!\" he cried.") ); 
        CHECK ( spRoot->GetNode("quoted")->GetValue() == ex::string_t(" # not a 'comment'.") ); 
        CHECK ( spRoot->GetNode("tie-fighter")->GetValue() == ex::string_t("|\\-*-/|") ); 

        ++idx;
    }

    // example 17
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("plain")->GetValue() == ex::string_t("This unquoted scalar spans many lines.") ); 
        CHECK ( spRoot->GetNode("quoted")->GetValue() == ex::string_t("So does this quoted scalar.\n") ); 

        ++idx;
    }

    // example 18
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("canonical")->GetValue() == ex::string_t("12345") ); 
        CHECK ( spRoot->GetNode("decimal")->GetValue() == ex::string_t("+12,345") ); 
        CHECK ( spRoot->GetNode("sexagesimal")->GetValue() == ex::string_t("3:25:45") ); 
        CHECK ( spRoot->GetNode("octal")->GetValue() == ex::string_t("014") ); 
        CHECK ( spRoot->GetNode("hexadecimal")->GetValue() == ex::string_t("0xC") ); 

        ++idx;
    }

    // example 19
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("canonical")->GetValue() == ex::string_t("1.23015e+3") ); 
        CHECK ( spRoot->GetNode("exponential")->GetValue() == ex::string_t("12.3015e+02") ); 
        CHECK ( spRoot->GetNode("sexagesimal")->GetValue() == ex::string_t("20:30.15") ); 
        CHECK ( spRoot->GetNode("fixed")->GetValue() == ex::string_t("1,230.15") ); 
        CHECK ( spRoot->GetNode("negative infinity")->GetValue() == ex::string_t("-.inf") ); 
        CHECK ( spRoot->GetNode("not a number")->GetValue() == ex::string_t(".NaN") ); 

        ++idx;
    }

    // example 20
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("null")->GetValue() == ex::string_t("~") ); 
        CHECK ( spRoot->GetNode("true")->GetValue() == ex::string_t("y") ); 
        CHECK ( spRoot->GetNode("false")->GetValue() == ex::string_t("n") ); 
        CHECK ( spRoot->GetNode("string")->GetValue() == ex::string_t("12345") ); 

        ++idx;
    }

    // example 21
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetNode("canonical")->GetValue() == ex::string_t("2001-12-15T02:59:43.1Z") ); 
        CHECK ( spRoot->GetNode("iso8601")->GetValue() == ex::string_t("2001-12-14t21:59:43.10-05:00") ); 
        CHECK ( spRoot->GetNode("spaced")->GetValue() == ex::string_t("2001-12-14 21:59:43.10 -5") ); 
        CHECK ( spRoot->GetNode("date")->GetValue() == ex::string_t("2002-12-14") ); 

        ++idx;
    }

    // example 22
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode("not-date"); 
        CHECK ( spNode->GetTag() == ex::string_t("tag:yaml.org,2002:str") ); 
        CHECK ( spNode->GetValue() == ex::string_t("2002-04-28") ); 

        spNode = spRoot->GetNode("picture"); 
        CHECK ( spNode->GetTag() == ex::string_t("tag:yaml.org,2002:binary") ); 
        const char* str1 = 
            "R0lGODlhDAAMAIQAAP//9/X\n"
            "17unp5WZmZgAAAOfn515eXv\n"
            "Pz7Y6OjuDg4J+fn5OTk6enp\n"
            "56enmleECcgggoBADs=\n";
        CHECK ( spNode->GetValue() == ex::string_t(str1) ); 

        spNode = spRoot->GetNode("application specific tag"); 
        CHECK ( spNode->GetTag() == ex::string_t("!something") ); 
        const char* str2 = 
            "The semantics of the tag\n"
            "above may be different for\n"
            "different documents.\n";
        CHECK ( spNode->GetValue() == ex::string_t(str2) ); 

        ++idx;
    }

    // example 23
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetTag() == ex::string_t("tag:clarkevans.com,2002:shape") ); 
        CHECK ( spRoot->GetNode(0)->GetTag() == ex::string_t("tag:clarkevans.com,2002:circle") ); 
        CHECK ( spRoot->GetNode(1)->GetTag() == ex::string_t("tag:clarkevans.com,2002:line") ); 
        CHECK ( spRoot->GetNode(2)->GetTag() == ex::string_t("tag:clarkevans.com,2002:label") ); 

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode(0)->GetNode("center"); 
        CHECK ( spNode->GetNode("x")->GetValue() == ex::string_t("73") ); 
        CHECK ( spNode->GetNode("y")->GetValue() == ex::string_t("129") ); 
        CHECK ( spRoot->GetNode(0)->GetNode("radius")->GetValue() == ex::string_t("7") ); 

        spNode = spRoot->GetNode(1)->GetNode("start"); 
        CHECK ( spNode->GetNode("x")->GetValue() == ex::string_t("73") ); 
        CHECK ( spNode->GetNode("y")->GetValue() == ex::string_t("129") ); 
        spNode = spRoot->GetNode(1)->GetNode("finish"); 
        CHECK ( spNode->GetNode("x")->GetValue() == ex::string_t("89") ); 
        CHECK ( spNode->GetNode("y")->GetValue() == ex::string_t("102") ); 

        spNode = spRoot->GetNode(2)->GetNode("start"); 
        CHECK ( spNode->GetNode("x")->GetValue() == ex::string_t("73") ); 
        CHECK ( spNode->GetNode("y")->GetValue() == ex::string_t("129") ); 
        CHECK ( spRoot->GetNode(2)->GetNode("color")->GetValue() == ex::string_t("0xFFEEBB") ); 
        CHECK ( spRoot->GetNode(2)->GetNode("text")->GetValue() == ex::string_t("Pretty vector drawing.") ); 

        ++idx;
    }

    // example 24
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetTag() == ex::string_t("tag:yaml.org,2002:set") ); 
        CHECK ( spRoot->GetNode("Mark McGwire")->GetValue() == ex::string_t("") ); 
        CHECK ( spRoot->GetNode("Sammy Sosa")->GetValue() == ex::string_t("") ); 
        CHECK ( spRoot->GetNode("Ken Griff")->GetValue() == ex::string_t("") ); 

        ++idx;
    }

    // example 25
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetTag() == ex::string_t("tag:yaml.org,2002:omap") ); 
        CHECK ( spRoot->GetNode(0)->GetNode("Mark McGwire")->GetValue() == ex::string_t("65") ); 
        CHECK ( spRoot->GetNode(1)->GetNode("Sammy Sosa")->GetValue() == ex::string_t("63") ); 
        CHECK ( spRoot->GetNode(2)->GetNode("Ken Griffy")->GetValue() == ex::string_t("58") ); 

        ++idx;
    }

    // example 26
    {
        ex::CYamlNode::smart_ptr_t spDoc = docs[idx];
        ex::CYamlNode::smart_ptr_t spRoot = spDoc->GetNode(0);

        CHECK ( spRoot->GetTag() == ex::string_t("tag:clarkevans.com,2002:invoice") ); 

        ex::CYamlNode::smart_ptr_t spNode = spRoot->GetNode(0)->GetNode("index"); 
        CHECK ( spNode->GetTag() == ex::string_t("ex::float") ); 
        CHECK ( spNode->GetValue() == ex::string_t("1.0") ); 

        ++idx;
    }
}
#endif
// } DISABLE end 
