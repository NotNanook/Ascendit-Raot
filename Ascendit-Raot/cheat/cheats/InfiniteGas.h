#pragma once
#include "..\Cheat.h"

class InfiniteGas : public Cheat {
public:
	void init() override;
	void onUpdate(Functions* functions) override;
};

extern InfiniteGas infiniteGas;