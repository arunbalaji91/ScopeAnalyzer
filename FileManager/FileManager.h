#pragma once
/////////////////////////////////////////////////////////////////////
//  FileManager.h - Handles the implementation of the file operations//
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

files& search(const std::string& path, patterns patts, switches swt);
This function recursively gets the files based on the switch present

files& recursivesearch(const std::string& path, patterns patts);
This function recursively gets the files from all the directories

void recursive_directories(const std::string& path);
This function gets the directories recursively ans sets the directories vector

Maintenance History:
====================
ver 1.0 : 12 Jan 06
- first release
*/
//

#include <string>
#include <vector>
class FileManager
{
public:
	typedef std::vector<std::string> files;
	typedef std::vector<std::string> patterns;
	typedef std::vector<std::string> switches;
	files& search(const std::string& path, patterns patts, switches swt);
	files& recursivesearch(const std::string& path, patterns patts);
	void recursive_directories(const std::string& path);
private:
	std::string path;
	files _files;
	std::vector<std::string> innerfiles;
	std::vector<std::string> directories;
	patterns _patterns;
	switches _switches;
};







