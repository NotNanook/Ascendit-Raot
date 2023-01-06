#pragma once
#include "..\utils\Functions.h"

class Cheat {
public:
	bool isEnabled = false;
	bool isToggled = false;
	std::vector<int> keys = {};

	void virtual init() {}
	void virtual onEnable(Functions* functions) {}
	void virtual onDisable(Functions* functions) {}
	void virtual onUpdate(Functions* functions) {}
	void checkForKey(Functions* functions);
	void checkForToggle(Functions* functions);
	void addKey(int key);
};