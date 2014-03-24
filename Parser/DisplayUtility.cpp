#pragma once
/////////////////////////////////////////////////////////////////////
// ParseFiles.cpp - implements the interaction with the parser pkg //
//  Author:       Kavish Pahade                                    //
//  Source:       Jim Fawcett                                      //
/////////////////////////////////////////////////////////////////////
#include "DisplayUtility.h"
#include <iostream>
#include <string>
#include "Tokenizer.h"
#include "SemiExpression.h"
#include "Parser.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"
#include "FoldingRules.h"

DisplayUtility::DisplayUtility()
{
}


DisplayUtility::~DisplayUtility()
{
}

void DetailDisplay(Repository *p_Repos)
{
	element elem = p_Repos->scopeStack().pop();
	if (elem.type == "function")
	{
		//std::cout << "\nHandlePop";
		//std::cout << "\n--popping at line count = " << p_Repos->lineCount();

		std::cout << "\nFunction " << elem.name << ", lines =" << p_Repos->lineCount() - elem.lineCount + 1 << ", Complexity=" << p_Repos->ScopeCounter() << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
		Node *tempnode = p_Repos->getRoot();
		Node* tempMaxNode = tempnode->clone();
		if (p_Repos->ScopeCounter() > p_Repos->get_MaxScopeCount())
		{
			int tempcount = p_Repos->ScopeCounter();
			p_Repos->set_MaxScopeCount(tempcount);
			p_Repos->setMaxScopeNode(tempMaxNode);
		}
		p_Repos->set_ScopeCount(1);

	}
	if (elem.type == "class")
	{
		std::cout << "\n  Class " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
	}
	if (elem.type == "struct")
	{
		std::cout << "\n  Struct " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
	}
	if (elem.type == "enum")
	{
		std::cout << "\n  Enum " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
	}
	if (elem.type == "namespace")
	{
		std::cout << "\n  NameSpace " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
	}
}