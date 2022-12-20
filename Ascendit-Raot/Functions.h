#pragma once
#include <iostream>
#include <windows.h>
#include <psapi.h>
#include "Structures.h"
#include "mem.h"

class Functions
{
public:
	uintptr_t baseAddress;
	uintptr_t dllGameBaseOffset;

	Functions(HMODULE baseAddress);

	// Raot functions
	typedef CharacterObject* (__thiscall* _get_Character)(void* playerMain);
	_get_Character get_Character;

	typedef void* (__thiscall* _setAmmo)(void* holdableItem, int leftAmmo, int rightAmmo);
	_setAmmo setAmmo;

	typedef void* (__cdecl* _set_lockState)(CursorLockMode value);
	_set_lockState set_lockState;

	typedef CursorLockMode (__cdecl* _get_lockState)();
	_get_lockState get_lockState;
};
