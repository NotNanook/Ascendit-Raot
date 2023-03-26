#pragma once

#include "Cheat.h"
#include "utils.h"

#include "cheats/InfiniteGas.h"
#include "cheats/InfiniteStress.h"
#include "cheats/NoShootCooldown.h"
#include "cheats/NoClip.h"

#include <vector>
#include <array>

namespace CheatManager {
	constexpr std::array<cstring, 3> categories { "Combat", "Render", "Misc" };
	const std::array<Cheat*, 4> cheats{
		&infiniteGas,
		&infiniteStress,
		&noShootCooldown,
		&noClip
	};

	/*
		Call this function ONCE at the beginning of your cheat. 
		It reads from the config file and automatically adds all hotkeys.
	*/
	void init();

	/*
		Best called from the render loop because it would 
		otherwise just consume unnecessary resources.
		It checks whether the user pressed a hotkey or if he
		toggled a cheat through the menu
	*/
	void checkUserInput();

	std::vector<Cheat*> cheatsByCategory(cstring category);

	void onRenderUpdate();
};