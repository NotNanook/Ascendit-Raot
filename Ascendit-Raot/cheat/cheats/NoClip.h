#pragma once
#include "..\Cheat.h"

class NoClip : public Cheat {
public:
	NoClip() : Cheat("NoClip", "Misc", { 'N' }) {}

	void onUpdate(Functions* functions) override;
	void onDisable(Functions* functions) override;
};

extern NoClip noClip;