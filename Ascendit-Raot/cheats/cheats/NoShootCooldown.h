#include "Cheat.h"

class NoShootCooldown : public Cheat {
public:
	NoShootCooldown() : Cheat("NoShootCooldown", "Combat", { VK_NUMPAD2 }) {}

	void onRenderUpdate() override;
};

extern NoShootCooldown noShootCooldown;

