#pragma once
#include "utils.h"
#include <vector>

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
	void virtual onEnable() {}
	void virtual onDisable() {}
	void checkForKey();
	void checkForToggle();
	void addKey(int key);

	/*
		Gets called every frame. Use this if:
		- Module has to change global game value every tick
		- Module draws something
	*/
	void virtual onRenderUpdate() {}
};