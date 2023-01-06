#pragma once
#include "..\Cheat.h"

class NoShootCooldown : public Cheat {
public:
	void init() override;
	void onUpdate(Functions* functions) override;
};

extern NoShootCooldown noShootCooldown;