@echo off
cd .\debug 
@echo **************************************************************************
@echo                    SCOPEANALYZER
@echo **************************************************************************

@echo ========================================================================---
@echo                  Demonstrating Requirement 1
@echo ========================================================================

@echo Project is implemented in C++ using the facilities of the standard template libraries, as provided in the EECS clusters.

@echo ========================================================================
@echo                 Demonstrating Requirement 2
@echo ========================================================================
@echo  Using services of the C++ std::iostream library for all input and output to and from the user’s console and C++ 
@echo  operator new and delete for all dynamic memory management.

@echo ========================================================================
@echo                  Demonstrating Requirement 3 and 4
@echo ========================================================================
@echo -----------------------------------------------------------------------
@echo The switch /s, if present, indicates that the entire directory tree rooted at the path is searched for matching files.

@echo -----------------------------------------------------------------------
ScopeAnalyzer.exe ../testfiles *.cpp,*.h /s /b
@echo -----------------------------------------------------------------------
@echo If the switch /s is not present on the command line only the directory at that path is searched.
ScopeAnalyzer.exe ../testfiles *.cpp,*.h /b
@echo -----------------------------------------------------------------------

@echo ========================================================================
@echo                  Demonstrating Requirement 5
@echo ========================================================================
@echo -----------------------------------------------------------------------
@echo At the end of processing each file, shall display an XML representation of the tree with the largest number of scope nodes.
@echo -----------------------------------------------------------------------
ScopeAnalyzer.exe ../testfiles *.cpp,*.h /s
@echo -----------------------------------------------------------------------

@echo ========================================================================
@echo                  Demonstrating Requirement 6 and 7
@echo ========================================================================
@echo -----------------------------------------------------------------------
@echo A command line option, /b, to show for each analyzed function only function size and complexity
@echo -----------------------------------------------------------------------
ScopeAnalyzer.exe ../testfiles *.cpp,*.h /s /b
@echo -----------------------------------------------------------------------
