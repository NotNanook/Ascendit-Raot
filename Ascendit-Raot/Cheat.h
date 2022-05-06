#pragma once
#include "pch.h"
#include "Functions.h"

class Cheat
{
public:
	bool isEnabled = false;
	int key;

	void virtual init() {};
	void virtual onEnable() {}
	void virtual onDisable() {}
	void virtual onUpdate(Functions* functions) {}
	void checkForKey(Functions* functions);
	void setKey(int key);
};