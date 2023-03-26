#pragma once
#include "Cheat.h"

class InfiniteStress : public Cheat {
public:
	InfiniteStress() : Cheat("Infinite Stress", "Combat", { VK_NUMPAD3 }) {}

	void onRenderUpdate() override;
};

extern InfiniteStress infiniteStress;

