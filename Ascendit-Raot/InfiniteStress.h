#pragma once
#include "Cheat.h"

class InfiniteStress : public Cheat
{
public:
	void init() override;
	void onUpdate(Functions* functions) override;
};

extern InfiniteStress infiniteStress;