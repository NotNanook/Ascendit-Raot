#pragma once

#include "Cheat.h"
#include "InfiniteGas.h"
#include "InfiniteStress.h"
#include "NoShootCooldown.h"
#include "ESP.h"

#include <vector>
#include <iostream>

class CheatManager
{
public:
	void init();
	void onUpdate(Functions* functions);
	void updateCheats(Functions* functions);
	std::vector<Cheat*> modules;
};

extern CheatManager cheatManager;