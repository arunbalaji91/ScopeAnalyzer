/////////////////////////////////////////////////////////////////////
//  FileManager.cpp - Handles the implementation of the file-operations//
//   Object Oriented Design, Spring 2014 						   //
//  Author:       Kavish Pahade                                    //
//				  SUID-577029986								   //
//  Source:       Jim Fawcett                                      //
/////////////////////////////////////////////////////////////////////

#include "FileManager.h"
#include <iostream>
#include "..//FileSystem//FileSystemDemo//FileSystem.h"

FileManager::files& FileManager::search(const std::string& path, FileManager::patterns patts,FileManager::switches swt)
{
	
	boolean recursive_flag = false;
	for (auto swit : swt)
	{
		if (swit == "/s")
		{
			recursive_flag = true;
		}
	}
		if (!recursive_flag)
		{
			for (auto patt : patts)
			{
				files temp = FileSystem::Directory::getFiles(path, patt);
				for (auto file : temp)
					_files.push_back(path + "/"+file);
			}

		}
		else
		{
			std::vector<std::string> tempfiles;
			for (auto patt : patts)
			{
				 tempfiles= FileSystem::Directory::getFiles(path, patt);
				 for (auto temp : tempfiles)
					 _files.push_back(path+"/"+temp);
			}
			files temp=recursivesearch(path, patts);
			for (auto file : temp)
				_files.push_back(file);
		}
		
	
	return _files;
}
void FileManager::recursive_directories(const std::string& path)
{
	
	std::vector<std::string> temp_directories=FileSystem::Directory::getDirectories(path);
	for (size_t i = 2; i < temp_directories.size(); i++)
	{
		if (temp_directories.size() == 0) return;
		directories.push_back(path+"/"+temp_directories[i]);
		recursive_directories(path +"/"+ temp_directories[i]);
	}
}
FileManager::files& FileManager::recursivesearch(const std::string& path, FileManager::patterns patts)
{
	
	for (auto patt : patts)
	{
		//std::vector<std::string> directories=FileSystem::Directory::getDirectories(path);
		recursive_directories(path);
		for (size_t i = 0; i < directories.size();i++)
		{
			files temp = FileSystem::Directory::getFiles(directories[i], patt);
			for (auto file : temp)
				innerfiles.push_back(directories[i] +"/" +file);
		}
	}
	return innerfiles;
}
#ifdef TEST_FILEMGR

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
		std::cout << "\n  " << argv[i];
	FileMgr fm;
	FileManager::switches swt{"/s","/b"};
	FileMgr::patterns patts{ "*.h", "*.cpp" };
	FileMgr::files foundFiles = fm.search(".", patts,swt);
	fm.recursive_directories(const std::string& path);
	FileMgr::files recFiles=fm.recursivesearch(const std::string& path, FileManager::patterns patts)
	for (auto file : foundFiles)
		std::cout << "\n  " << file;
	for (auto file : recFiles)
		std::cout << "\n  " << file;
	std::cout << "\n\n";
}
#endif
