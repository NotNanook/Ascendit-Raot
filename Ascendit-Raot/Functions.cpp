#include "Functions.h"

Functions::Functions(uintptr_t baseAddress)
{
	this->baseAddress = baseAddress;
	this->dllGameBaseOffset = baseAddress + 0x025A0E70;
	get_Character = (_get_Character)(baseAddress + 0x8EEBF0);
	set_lockState = (_set_lockState)(baseAddress + 0x1264BC0);
	get_lockState = (_get_lockState)(baseAddress + 0x1264B70);
}
