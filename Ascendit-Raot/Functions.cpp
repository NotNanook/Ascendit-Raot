#include "Functions.h"

Functions::Functions(HMODULE baseAddressGameDll, HMODULE baseAddressPlayerDll)
{
	this->baseAddress = (uintptr_t)baseAddressGameDll;
	this->dllGameBaseOffset = this->baseAddress + 0x025A0E70;
	this->dllPlayerBaseOffset = (uintptr_t)baseAddressPlayerDll + 0x017A7540;
	get_Character = (_get_Character)(this->baseAddress + 0x8EEBF0);
	set_lockState = (_set_lockState)(this->baseAddress + 0x1264BC0);
	get_lockState = (_get_lockState)(this->baseAddress + 0x1264B70);
	getTransform = (_getTransform)(this->baseAddress + 0x672290);
	getPosition = (_getPosition)(this->baseAddress + 0x1171C30);
}
