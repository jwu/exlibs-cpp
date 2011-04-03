// ======================================================================================
// File         : Failure.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:28:28 AM | Tuesday,August
// Description  : This is a modified version of CppUnitLite
// ======================================================================================

// #################################################################################
#ifndef FAILURE_H_1250526515
#define FAILURE_H_1250526515
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// class Failure 
// 
// Purpose: 
//  Failure records the circumstances surrounding a test failure.  Using C++
//  macros were are able to record the name of the file where the failure 
//  occurred, the line number, and the text of the condition which provoked
//  the failure.
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Failure
{
public:
	Failure ( std::string theCondition, 
              std::string theTestName, 
              std::string theFileName, 
              long theLineNumber ) 
		: condition (theCondition), 
          testName (theTestName), 
          fileName (theFileName), 
          lineNumber (theLineNumber)
	{
	}

public:
	std::string condition;
	std::string testName;
	std::string fileName;
	long lineNumber;
}; // end class Failure


// ------------------------------------------------------------------
// Desc: operator << 
// ------------------------------------------------------------------

inline std::ostream& operator<< ( std::ostream& stream, Failure& failure )
{
    stream 
        << "Failure: \"" << failure.condition.c_str () << "\" " 
        << "line " << failure.lineNumber << " in "
        << failure.fileName.c_str ()
        << std::endl;

    return stream;
}

// #################################################################################
#endif // END FAILURE_H_1250526515
// #################################################################################

