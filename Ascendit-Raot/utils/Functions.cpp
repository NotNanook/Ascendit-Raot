#include "Functions.h"

Functions::Functions(HMODULE baseAddressGameDll, HMODULE baseAddressPlayerDll) {
	baseAddress = (uintptr_t) baseAddressGameDll;
	dllGameBaseOffset = baseAddress + 0x025A0E70;
	dllPlayerBaseOffset = (uintptr_t) baseAddressPlayerDll + 0x017A7540;
	get_Character = (_get_Character) (baseAddress + 0x8EEBF0);
	set_lockState = (_set_lockState) (baseAddress + 0x1264BC0);
	get_lockState = (_get_lockState) (baseAddress + 0x1264B70);
	getTransform = (_getTransform) (baseAddress + 0x672290);
	getPosition = (_getPosition) (baseAddress + 0x1171C30);
}