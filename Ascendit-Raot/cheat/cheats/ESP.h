#pragma once
#include "..\Cheat.h"

class ESP : public Cheat {
public:
	void init() override;
	void onEnable(Functions* functions) override;
	void onUpdate(Functions* functions) override;
};

extern ESP esp;