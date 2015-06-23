#pragma once
/////////////////////////////////////////////////////////////////////
//  Executive.cpp - Interacts with the Command Line and passes the //
//					input to the parser executive package          //
// Author:       Kavish Pahade                                     //
//SUID-577029986												   //
//Object Oriented Design, Spring 2014 							   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include "../FileSystem/FileSystemDemo/FileSystem.h"
#include "../FileManager/FileManager.h"
#include "../ScopeAnalyzer/ParseFiles.h"

using namespace FileSystem;


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "\n  please enter path and patterns\n\n";
		return 1;
	}
	std::string path = argv[1];
	FileManager::patterns patts;
	
	//std::vector<std::string> elems;
	std::stringstream ss(argv[2]);
	std::string item;
	while (std::getline(ss, item, ','))
		{
			patts.push_back(item);
		}
		
	FileManager::switches swt;
	for (int i = 3; i < argc; ++i)
		swt.push_back(argv[i]);
	FileManager fm;
	FileManager::files myFiles = fm.search(path, patts, swt);
	ParseFiles PF;
	for (std::string file : myFiles)
	PF.parserexecutive(file,swt);
	std::cout << "\n\n";
////////////////////////////////////////////////////////	
	//code updated by:arunbalaji
	for(int jam = 0; jam < 5; jam++)
		std::cout<<"dummy"<<std::endl;
	std::cout << "\n\n";
///////////////////////////////////////////////////////	
	return 0;
}
