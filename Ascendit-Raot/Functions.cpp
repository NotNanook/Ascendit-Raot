#include "pch.h"
#include "Functions.h"
#include <iostream>

Functions::Functions(uintptr_t baseAddress)
{
	this->baseAddress = baseAddress;
	this->dllGameBaseOffset = baseAddress + 0x025A0E70;
	get_Character = (_get_Character)(baseAddress + 0x8EEBF0);
	setAmmo = (_setAmmo)(baseAddress + 0x4DFA80);

	/*
	getTransform = (_getTransform)(baseAddress + 0x519090);
	getPosition = (_getPosition)(baseAddress + 0x1087E60);
	sendMessage = (_sendMessage)(baseAddress + 0x484730);
	getAlivePlayers = (_getAlivePlayers)(baseAddress + 0x3B1C60);
	*/

	printf("[Functions] Base Address %x\n", (int) baseAddress);
}
