#pragma once

#include "Cheat.h"
#include "InfiniteGas.h"
#include "InfiniteStress.h"
#include "NoShootCooldown.h"
#include "ESP.h"
#include "NoClip.h"

#include <vector>

class CheatManager
{
public:
	void init();
	void onUpdate(Functions* functions);
	std::vector<Cheat*> modules;
};

extern CheatManager cheatManager;