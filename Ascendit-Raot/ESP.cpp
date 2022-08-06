#include "pch.h"
#include "ESP.h"
#include <iostream>

ESP esp;

void ESP::onEnable(Functions* functions)
{
	/*
	MirrorClientObject* client = functions->getAlivePlayers(NULL, NULL);
	for (int i = 0; i < 10; i++) {
		std::cout << "*(array + " << i << ") : ";
		std::cout << client << std::endl;
	}
	*/
}

void ESP::onUpdate(Functions* functions)
{
}

void ESP::init()
{
	setKey(VK_NUMPAD4);
}