#pragma once
#include "..\Cheat.h"

class InfiniteGas : public Cheat {
public:
	InfiniteGas() : Cheat("InfiniteGas", "Combat", { VK_NUMPAD1, 'K' }) {}
	
	void onUpdate(Functions* functions) override;
};

extern InfiniteGas infiniteGas;