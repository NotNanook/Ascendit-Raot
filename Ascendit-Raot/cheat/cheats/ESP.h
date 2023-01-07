#pragma once
#include "..\Cheat.h"

class ESP : public Cheat {
public:
	ESP() : Cheat("ESP", "Render", { VK_NUMPAD4 }) {}
	
	void onEnable(Functions* functions) override;
	void onUpdate(Functions* functions) override;
};

extern ESP esp;