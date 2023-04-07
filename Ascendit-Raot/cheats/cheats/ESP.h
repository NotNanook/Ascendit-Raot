#pragma once
#include "Cheat.h"

class ESP : public Cheat {
public:
	ESP() : Cheat("ESP", "Render", { VK_NUMPAD5 }) {}

	void onRenderUpdate() override;
};

extern ESP esp;
