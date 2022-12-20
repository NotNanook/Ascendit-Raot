#include "Functions.h"

Functions::Functions(HMODULE baseAddress)
{
	this->baseAddress = (uintptr_t)baseAddress;
	this->dllGameBaseOffset = this->baseAddress + 0x025A0E70;
	get_Character = (_get_Character)(this->baseAddress + 0x8EEBF0);
	set_lockState = (_set_lockState)(this->baseAddress + 0x1264BC0);
	get_lockState = (_get_lockState)(this->baseAddress + 0x1264B70);
}
