#pragma once
#include "Functions.h"
#include "mem.h"
#include <iostream>

class Cheat
{
public:
	bool isEnabled = false;
	int key;

	void virtual init() {};
	void virtual onEnable(Functions* functions) {}
	void virtual onDisable(Functions* functions) {}
	void virtual onUpdate(Functions* functions) {}
	void checkForKey(Functions* functions);
	void setKey(int key);
};