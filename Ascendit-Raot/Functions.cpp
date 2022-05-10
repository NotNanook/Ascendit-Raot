#include "pch.h"
#include "Functions.h"

Functions::Functions(uintptr_t baseAddress)
{
	this->baseAddress = baseAddress;
	this->dllGameBaseOffset = baseAddress + 0x0240A538;
	get_Character = (_get_Character)(baseAddress + 0x7959B0);
	getTransform = (_getTransform)(baseAddress + 0x519090);
	getPosition = (_getPosition)(baseAddress + 0x1087E60);
}
