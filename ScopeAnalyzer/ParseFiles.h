#pragma once
/////////////////////////////////////////////////////////////////////
//  ParseFiles.h - Handles the interaction of Executive with       //
//                   with configure parser package                  //
//   Object Oriented Design, Spring 2014 						   //
//  Author:       Kavish Pahade                                    //
//				  SUID-577029986								   //
//  Source:       Jim Fawcett                                      //
/////////////////////////////////////////////////////////////////////
/* Module Operations:
==================
This modules builds the parser and then calls appropriate parser methods to start the parsing process

Public Interface:
=================
void parserexecutive(std::string filename, std::vector<std::string> switches);
Build Process:
==============
Required files
- Parser.h, Parser.cpp, ScopeStack.h, ScopeStack.cpp,
ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.cpp,
ItokCollection.h, SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
Build commands (either one)
- devenv CodeAnalysis.sln
- cl /EHsc /DTEST_PARSER parser.cpp ActionsAndRules.cpp \
semiexpression.cpp tokenizer.cpp /link setargv.obj

Maintenance History:
====================
ver 1.0 : 12 Jan 06
- first release
*/
//
#include <string>
#include<vector>
#include "..//Parser//Tokenizer.h"
#include "..//Parser//SemiExpression.h"
#include "..//Parser//Parser.h"
#include "..//Parser//ActionsAndRules.h"
#include "..//Parser//ConfigureParser.h"
#include "..//Parser//FoldingRules.h"
class ParseFiles
{
public:
	ParseFiles();
	~ParseFiles();
	void parserexecutive(std::string filename, std::vector<std::string> switches);
};
