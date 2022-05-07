#include "pch.h"
#include "Functions.h"

Functions::Functions(uintptr_t baseAddress)
{
	this->baseAddress = baseAddress;
	this->dllGameBaseOffset = baseAddress + 0x0231D310;
	get_Character = (_get_Character)(baseAddress + 0x69EAE0);
	getTransform = (_getTransform)(baseAddress + 0x524F70);
	getPosition = (_getPosition)(baseAddress + 0x1106130);
	getParryData = (_getParryData)(baseAddress + 0x45F2F0);
	startAttack = (_startAttack)(baseAddress + 0x468C70);
}
