#pragma once

#include "Cheat.h"
#include "cheats\InfiniteGas.h"
#include "cheats\InfiniteStress.h"
#include "cheats\NoShootCooldown.h"
#include "cheats\ESP.h"
#include "cheats\NoClip.h"

#include <vector>
#include <array>

namespace CheatManager {
	constexpr std::array<cstring, 3> categories { "Combat", "Render", "Misc" };
	const std::array<Cheat*, 5> cheats {
		&infiniteGas,
		&infiniteStress,
		&noShootCooldown,
		&esp,
		&noClip
	};

	void init();
	void onUpdate(Functions* functions);
	std::vector<Cheat*> cheatsByCategory(cstring category);
};