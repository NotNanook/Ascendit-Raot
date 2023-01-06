#pragma once

#include "Cheat.h"
#include "cheats\InfiniteGas.h"
#include "cheats\InfiniteStress.h"
#include "cheats\NoShootCooldown.h"
#include "cheats\ESP.h"
#include "cheats\NoClip.h"

#include <vector>

class CheatManager {
public:
	void init();
	void add(Cheat cheat);
	void onUpdate(Functions* functions);
	std::vector<Cheat*> cheats;
};

extern CheatManager cheatManager;