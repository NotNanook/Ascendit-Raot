#pragma once

#include "Cheat.h"
#include "cheats\InfiniteGas.h"
#include "cheats\InfiniteStress.h"
#include "cheats\NoShootCooldown.h"
#include "cheats\ESP.h"
#include "cheats\NoClip.h"

#include <vector>
#include <array>

constexpr std::array<cstring, 3> categories { "Combat", "Render", "Misc" };

std::vector<Cheat*> cheats(cstring category);

class CheatManager {
public:
	std::vector<Cheat*> cheats;

	void init();
	void add(Cheat cheat);
	void onUpdate(Functions* functions);
};

extern CheatManager cheatManager;