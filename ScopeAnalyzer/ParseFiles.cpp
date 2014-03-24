#pragma once
/////////////////////////////////////////////////////////////////////
// ParseFiles.cpp - implements the interaction with the parser pkg //
//  Author:       Kavish Pahade                                    //
//  Source:       Jim Fawcett                                      //
/////////////////////////////////////////////////////////////////////

#include "ParseFiles.h"
#include <iostream>
#include <string>
ParseFiles::ParseFiles()
{
}


ParseFiles::~ParseFiles()
{
}

void ParseFiles::parserexecutive(std::string filename, std::vector<std::string> switches)
{
	std::cout << "\n  Processing file " << filename;
	std::cout << "\n  " << std::string(16 , '-');
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	try
	{
		if (pParser)
		{
			if (!configure.Attach(filename))
			{
				std::cout << "\n  could not open file " << filename << std::endl;
			}
		}
		else
		{
			std::cout << "\n\n  Parser not built\n\n";
		}
		// now that parser is built, use it
		bool switch_set = false;
		for (auto tempstr : switches)
		{
			if (tempstr == "/b")
				switch_set = true;
		}
			if (switch_set)
			{
				configure.SetSwitch(true);
				while (pParser->next())
					pParser->parse();
			}
			else
			{
				while (pParser->next())
					pParser->parse();
				configure.PrintMaxTree();
			}			
		std::cout << "\n\n";
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	std::cout << "\n\n";
}
#ifdef TEST_ParseFiles

int main(int argc, char* argv[])
{
	
	FileMgr fm;
	std::string filename="../Test.cpp";
	std::vector<std::string> switches{"/s","/b"};
	ParseFiles PF=new ParseFiles();
	PF.parserexecutive(filename,switches);
	std::cout << "\n\n";
}
#endif
