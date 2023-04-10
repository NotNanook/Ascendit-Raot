#pragma once

#include "Cheat.h"
#include "utils.h"

#include "cheats/InfiniteGas.h"
#include "cheats/InfiniteStress.h"
#include "cheats/NoShootCooldown.h"
#include "cheats/NoClip.h"
#include "cheats/ESP.h"

#include <vector>
#include <array>

namespace CheatManager {
	constexpr std::array<cstring, 3> categories { "Combat", "Render", "Misc" };
	const std::array<Cheat*, 5> cheats{
		&infiniteGas,
		&infiniteStress,
		&noShootCooldown,
		&noClip,
		&esp
	};

	std::vector<Cheat*> cheatsByCategory(cstring category);

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

	/*
		Gets called every frame
	*/
	void onRenderUpdate();
};