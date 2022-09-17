#include "pch.h"
#include "Cheat.h"
#include "Functions.h"

void Cheat::checkForKey(Functions* functions)
{
	if ((GetAsyncKeyState(this->key) || GetAsyncKeyState(this->charKey)) & 1)
	{
		this->isEnabled = !this->isEnabled;
		if (this->isEnabled)
		{
			this->onEnable(functions);
		}
		else 
		{
			this->onDisable(functions);
		}
	}

	if (this->isEnabled)
	{
		this->onUpdate(functions);
	}
}

void Cheat::setKey(int key)
{
	this->key = key;
}

void Cheat::setKey(char key)
{
	this->charKey = key;
}