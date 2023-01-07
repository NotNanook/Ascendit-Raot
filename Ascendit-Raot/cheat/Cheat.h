#pragma once
#include "..\utils\Functions.h"

class Cheat {
public:
	cstring name;
	cstring category;
	bool isEnabled = false;
	bool isToggled = false;
	std::vector<int> keys = {};

	Cheat(cstring name, cstring category, std::vector<int> keys)
		: name(name), category(category), keys(keys) {}

	void virtual init() {}
	void virtual onEnable(Functions* functions) {}
	void virtual onDisable(Functions* functions) {}
	void virtual onUpdate(Functions* functions) {}
	void checkForKey(Functions* functions);
	void checkForToggle(Functions* functions);
	void addKey(int key);
};