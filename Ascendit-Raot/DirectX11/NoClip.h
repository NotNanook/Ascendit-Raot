#pragma once
#include "Cheat.h"

class NoClip : public Cheat
{
public:
	void init() override;
	void onUpdate(Functions* functions) override;
	void onDisable(Functions* functions) override;
};

extern NoClip noClip;
