#pragma once
#include<vector>
#include "Cheat.h"

class CheatManager
{
public:
	void init();
	void onUpdate(Functions* functions);
	std::vector<Cheat*> modules;
};

extern CheatManager cheatManager;