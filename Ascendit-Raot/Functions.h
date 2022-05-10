#pragma once
#include "Structures.h"

class Functions
{
public:
	uintptr_t baseAddress;
	uintptr_t dllGameBaseOffset;

	Functions(uintptr_t baseAddress);

	typedef CharacterObject* (__thiscall* _get_Character)(void* playerMain);
	_get_Character get_Character;

	typedef Transform* (__cdecl* _getTransform)(void* player);
	_getTransform getTransform;

	typedef Vector3* (__cdecl* _getPosition)(void* transform, void* out);
	_getPosition getPosition;
};
