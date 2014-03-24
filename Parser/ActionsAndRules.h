#ifndef ACTIONSANDRULES_H
#define ACTIONSANDRULES_H
/////////////////////////////////////////////////////////////////////
//  ActionsAndRules.h - declares new parsing rules and actions     //
//   Object Oriented Design, Spring 2014 						   //
//  Author:       Kavish Pahade                                    //
//				  SUID-577029986								   //
//  Source:       Jim Fawcett                                      //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines several action classes.  Its classes provide 
  specialized services needed for specific applications.  The modules
  Parser, SemiExpression, and Tokenizer, are intended to be reusable
  without change.  This module provides a place to put extensions of
  these facilities and is not expected to be reusable. 

  Public Interface:
  =================
  Toker t(someFile);              // create tokenizer instance
  SemiExp se(&t);                 // create a SemiExp attached to tokenizer
  Parser parser(se);              // now we have a parser
  Rule1 r1;                       // create instance of a derived Rule class
  Action1 a1;                     // create a derived action
  r1.addAction(&a1);              // register action with the rule
  parser.addRule(&r1);            // register rule with parser
  while(se.getSemiExp())          // get semi-expression
  parser.parse();               //   and parse it
  PrintMaxTree(Repository * p_Repos) //Printing the tree using the XMLWriter Class
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
  ver 2.0 : 01 Jun 11
  - added processing on way to building strong code analyzer
  ver 1.1 : 17 Jan 09
  - changed to accept a pointer to interfaced ITokCollection instead
    of a SemiExpression
  ver 1.0 : 12 Jan 06
  - first release

*/
//
#include <queue>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include "Parser.h"
#include "ITokCollection.h"
#include "ScopeStack.h"
#include "Tokenizer.h"
#include "SemiExpression.h"
#include "../ScopeAnalyzer/XmlWriter.h"
//#include "DisplayUtility.h"
#include "../MTree/MTree/Mtree.h"
#include "../MTree/MTree/MNode.h"
///////////////////////////////////////////////////////////////
// ScopeStack element is application specific
typedef TMTree::MNode<std::string> Node;
struct element
{
  std::string type;
  std::string name;
  size_t lineCount;
  std::string show()
  {
    std::ostringstream temp;
    temp << "(";
    temp << type;
    temp << ", ";
    temp << name;
    temp << ", ";
    temp << lineCount;
    temp << ")"; 
    return temp.str();
  }
};

///////////////////////////////////////////////////////////////
// Repository instance is used to share resources
// among all actions.
class DisplayUtility;
class Repository  // application specific
{
  
	typedef TMTree::MNode<std::string> Node; 
	Node* pRoot;
	Node* MaxNode;
	std::vector<Node*> nodes;//Vector of nodes storing the root as the Function name and rest are scopes
	int scopeCount = 1;
    ScopeStack<element> stack;//Stack data structure to be used in the Printing the XML tree 
    Toker* p_Toker;
	int MaxScopeCount=0; //Keeping the count of the function with the maximum no of scopes
	bool switchflag=false; //Flag which is set if the /b flag is set
public:
  Repository(Toker* pToker)
  {
    p_Toker = pToker;
	pRoot=NULL;
     MaxNode = NULL;
	std::vector<Node*> nodes;
  }
  ScopeStack<element>& scopeStack()
  {
    return stack;
  }
  void setMaxScopeNode(Node* _tmNode)
  {
	  MaxNode = _tmNode;
  }
  Node* getMaxScopeNode()
  {
	  return MaxNode;
  }
  Toker* Toker()
  {
    return p_Toker;
  }
  size_t lineCount()
  {
    return (size_t)(p_Toker->lines());
  }
  Node* getRoot()
  {
		  return pRoot;
  }
  void setRoot(Node* _Root)
  {
	  pRoot = _Root;
  }
  void increment_MaxScopeCount()
  {
	  MaxScopeCount++;
  }
  int get_MaxScopeCount()
  {
	  return MaxScopeCount;
  }
  void set_MaxScopeCount(int _tmval)
  {
	  MaxScopeCount = _tmval;
  }
  int ScopeCounter()
  {
	  return (int)(scopeCount);
  }
  std::vector<Node*> getnodes()
  {
	  return nodes;
  }
  void setnodes(std::vector<Node*> _nodes)
  {
	  nodes=_nodes;
  }
  void Increment_ScopeCount()
  {
	  scopeCount++;
  }
  void set_ScopeCount(int n)
  {
	  scopeCount=n;
  }
  void setswitchflag(bool switchvalue)
  {
	  switchflag = switchvalue;
  }
  bool getswitchflag()
  {
	  return switchflag;
  }
};

///////////////////////////////////////////////////////////////
// rule to detect beginning of anonymous scope

class BeginningOfScope : public IRule
{
public:
  bool doTest(ITokCollection*& pTc)
  {
    //std::cout << "\n--BeginningOfScope rule";
    if(pTc->find("{") < pTc->length())
    {
      doActions(pTc);
      return false;
    }
    return false;
  }
};

///////////////////////////////////////////////////////////////
// action to handle scope stack at end of scope

class HandlePush : public IAction
{
  Repository* p_Repos;
public:
  HandlePush(Repository* pRepos)
  {
    p_Repos = pRepos;
  }
  void doAction(ITokCollection*& pTc)
  {
    element elem;
    elem.type = "unknown";
    elem.name = "anonymous";
    elem.lineCount = p_Repos->lineCount();
    p_Repos->scopeStack().push(elem);
  }
};

///////////////////////////////////////////////////////////////
// rule to detect end of scope



class EndOfScope : public IRule
{
	public:
	 bool doTest(ITokCollection*& pTc)
  {
    //std::cout << "\n--EndOfScope rule";
    if(pTc->find("}") < pTc->length())
    {
		doActions(pTc);
      return false;
    }
    return false;
  }
};
class newOper : public TMTree::Operation<Node>
{
public:
	bool operator()(Node* pNode)
	{
		std::cout << "\n -- " << pNode->ToString();
		return false;
	}
};
///////////////////////////////////////////////////////////////
// action to handle scope stack at end of scope

class HandlePop : public IAction
{
  Repository* p_Repos;
public:
  HandlePop(Repository* pRepos)
  {
    p_Repos = pRepos;
  }
  void doAction(ITokCollection*& pTc)
  {
    if(p_Repos->scopeStack().size() == 0)
      return;
	std::vector<Node*> tmpNodes = p_Repos->getnodes();
	if (tmpNodes.size() > 1)
		tmpNodes.pop_back();
	p_Repos->setnodes(tmpNodes);
	element elem = p_Repos->scopeStack().pop();
	if(elem.type == "function")
    {
     	std::cout << "\n\n\nFunction " << elem.name << ", Function Size  =" << p_Repos->lineCount() - elem.lineCount + 1 <<"\n Complexity="<< p_Repos->ScopeCounter() << ", Beginning of Scope=" << elem.lineCount + 1 << ", End of Scope =" << p_Repos->lineCount() + 1;
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
	if (!p_Repos->getswitchflag())
	{

		if (elem.type == "class")
		{
			std::cout << "\n\nClass " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
		}
		if (elem.type == "struct")
		{
			std::cout << "\n\n  Struct " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
		}
		if (elem.type == "enum")
		{
			std::cout << "\n\n  Enum " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
		}
		if (elem.type == "namespace")
		{
			std::cout << "\n\n  NameSpace " << elem.name << ", lines = " << p_Repos->lineCount() - elem.lineCount + 1 << ", Opening brace=" << elem.lineCount + 1 << ", Closing brace=" << p_Repos->lineCount() + 1;
		}
	}
  }
};

///////////////////////////////////////////////////////////////
// rule to detect preprocessor statements

class PreprocStatement : public IRule
{
public:
  bool doTest(ITokCollection*& pTc)
  {
    //std::cout << "\n--PreprocStatement rule";
    if(pTc->find("#") < pTc->length())
    {
      doActions(pTc);
      return true;
    }
    return false;
  }
};

///////////////////////////////////////////////////////////////
// action to print preprocessor statement to console

class PrintPreproc : public IAction
{
public:
  void doAction(ITokCollection*& pTc)
  {
    std::cout << "\n\n  Preproc Stmt: " << pTc->show().c_str();
  }
};

///////////////////////////////////////////////////////////////
// rule to detect function definitions
static std::map <std::string, int> maxMap;
class FunctionDefinition : public IRule
{
	//Repository * p_Repos;
	
public:
	FunctionDefinition(){
	}

	/*FunctionDefinition(Repository* pRepos)
	{
		p_Repos = pRepos;
	}*/
	bool isSpecialKeyWord(const std::string& tok)
  {
		
		const static std::string keys[]
      = { "for", "while", "switch", "if", "catch" };
    for(int i=0; i<5; ++i)
      if(tok == keys[i])
        return true;
    return false;
  }
  bool doTest(ITokCollection*& pTc)
  {
	  
	  ITokCollection& tc = *pTc;
    if(tc[tc.length()-1] == "{")
    {
      size_t len = tc.find("(");
      if(len < tc.length() && !isSpecialKeyWord(tc[len-1]))
      {
        doActions(pTc);
		return true;
      }
    }
    return false;
  }
};
// action to push function name onto ScopeStack

class PushFunction : public IAction
{
	Repository* p_Repos;
public:
	PushFunction(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		ITokCollection& tc = *pTc;
	    size_t len = tc.find("(");
		Node* tempnode;
		tempnode = new Node(tc[len - 1]);
		p_Repos->setRoot(tempnode);
		std::vector<Node*> tmpNodes = p_Repos->getnodes();
		tmpNodes.clear();
		tmpNodes.push_back(tempnode);
		p_Repos->setnodes(tmpNodes);
		//p_Repos->setnodes(p_Repos->getnodes());
		
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("(") - 1];
		element elem;
		elem.type = "function";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);
	}
};


class ScopeDefinition : public IRule
{
	//Repository * p_Repos;
public:
	ScopeDefinition()
	{

	}
	/*ScopeDefinition(Repository* pRepos)
	{
		p_Repos = pRepos;
	}*/
	bool isSpecialKeyWord(const std::string& tok)
	{
		const static std::string keys[]
			= { "for", "while", "switch", "if","else", "catch" };
		for (int i = 0; i<5; ++i)
		if (tok == keys[i])
			return true;
		return false;
	}
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("(");
			if (len == tc.length() && tc[0] == "else")
				len = tc.length() - 2;
			if (len < tc.length() && isSpecialKeyWord(tc[len - 1]))
			{
				//Node *child = new Node(tc[len - 1]);
				//p_Repos->Increment_ScopeCount();
				
				//p_Repos->getnodes()[p_Repos->getnodes().size() - 1]->addChild(child);
				//p_Repos->getnodes().push_back(child);
				doActions(pTc);
				return true;
			}
		}
	
		return false;
	}
};



///////////////////////////////////////////////////////////////
// action to push scopeDef name onto ScopeStack

class PushScope : public IAction
{
	Repository* p_Repos;
public:
	PushScope(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope		
		//p_Repos->scopeStack().pop();
			ITokCollection& tc = *pTc;
		
		    size_t len = tc.find("(");
			if (len == tc.length() && tc[0] == "else")
				len = tc.length() - 2;
			Node *child = new Node(tc[len - 1]);
			//p_Repos->addChild(child);
			std::vector<Node*> vectorNodes = p_Repos->getnodes();
			p_Repos->Increment_ScopeCount();
			vectorNodes[vectorNodes.size() - 1]->addChild(child);
			vectorNodes.push_back(child);
			p_Repos->setnodes(vectorNodes);
			// push function scope
			
	}
};


class ClassDefinition : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("class");
			if (len < tc.length())
			{
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};
class EnumDefinition : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("enum");
			if (len < tc.length())
			{
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};
class StructDefinition : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("struct");
			if (len < tc.length())
			{
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};
class NameSpaceDefinition : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("namespace");
			if (len < tc.length())
			{
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};
///////////////////////////////////////////////////////////////

class PushClass : public IAction
{
	Repository* p_Repos;
public:
	PushClass(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("class") + 1];
		element elem;
		elem.type = "class";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);
	}
};
class PushStruct : public IAction
{
	Repository* p_Repos;
public:
	PushStruct(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("struct") + 1];
		element elem;
		elem.type = "struct";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);
	}
};
class PushNameSpace : public IAction
{
	Repository* p_Repos;
public:
	PushNameSpace(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("namespace") + 1];
		element elem;
		elem.type = "namespace";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);
	}
};
class PushEnum : public IAction
{
	Repository* p_Repos;
public:
	PushEnum(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("enum") + 1];
		element elem;
		elem.type = "enum";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);
	}
};
///////////////////////////////////////////////////////////////
// action to send semi-expression that starts a function def
// to console

class PrintFunction : public IAction
{
public:
	void PrintMaxTree(Repository * p_Repos)
	{
		if (p_Repos->getnodes().size() > 0)
		{

			std::cout << "\n Maximum Scope Function: " << p_Repos->getMaxScopeNode()->value();
			std::cout << "\n Maximum Scope-Count: " << p_Repos->get_MaxScopeCount();
			std::cout << "\n";
			std::stack<Node*> NodeStack;
			Node* MaxNode = p_Repos->getMaxScopeNode();
			NodeStack.push(MaxNode);
			XmlWriter wtr;
			wtr.indent();
			wtr.start(MaxNode->value());
			wtr.addDeclaration();
			while (!NodeStack.empty())
			{
				Node* tempnode = NodeStack.top()->nextUnmarkedChild();
				if (tempnode == 0)
				{
					wtr.end();
					NodeStack.pop();
				}
				else
				{
					NodeStack.push(tempnode);
					tempnode->clearMarks();
					wtr.start(NodeStack.top()->value());
				}

			}
			//wtr.end();
			std::cout << wtr.xml();
		}
	}
	
  void doAction(ITokCollection*& pTc)
  {
    std::cout << "\n\n  FuncDef Stmt: " << pTc->show().c_str();
  }
};

///////////////////////////////////////////////////////////////
// action to send signature of a function def to console

class PrettyPrintFunction : public IAction
{
public:
  void doAction(ITokCollection*& pTc)
  {
    pTc->remove("public");
    pTc->remove(":");
    pTc->trimFront();
    int len = pTc->find(")");
    std::cout << "\n\n  Pretty Stmt:    ";
    for(int i=0; i<len+1; ++i)
      std::cout << (*pTc)[i] << " ";
  }
};

#endif
