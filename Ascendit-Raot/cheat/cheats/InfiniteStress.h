#pragma once
#include "..\Cheat.h"

class InfiniteStress : public Cheat {
public:
	InfiniteStress() : Cheat("InfiniteStress", "Combat", { VK_NUMPAD2, 'I' }) {}

	void onUpdate(Functions* functions) override;
};

extern InfiniteStress infiniteStress;