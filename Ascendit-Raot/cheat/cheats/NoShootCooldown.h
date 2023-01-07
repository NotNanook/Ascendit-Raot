#pragma once
#include "..\Cheat.h"

class NoShootCooldown : public Cheat {
public:
	NoShootCooldown() : Cheat("NoShootCooldown", "Combat", { VK_NUMPAD3, 'O' }) {}

	void onUpdate(Functions* functions) override;
};

extern NoShootCooldown noShootCooldown;