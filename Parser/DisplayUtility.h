#pragma once
#include "ActionsAndRules.h"

class Repository;//Forward decalaration required for the cyclic depedent files
class DisplayUtility
{
public:
	DisplayUtility();
	~DisplayUtility();
	void DetailDisplay(Repository *p_Repos);
};

