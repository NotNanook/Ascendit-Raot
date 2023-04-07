#pragma once
#include "Structures.h"
#include <vector>

namespace Functions
{
	void init();

	inline uintptr_t gameAssemblyBase;
	inline uintptr_t gamePlayerBase;

	typedef CursorLockMode(__cdecl* _get_lockState)();
	inline _get_lockState getLockState;

	typedef void* (__cdecl* _set_lockState)(CursorLockMode value);
	inline _set_lockState setLockState;

	typedef void(__cdecl* _getPosition)(void* transform, Vector3* out);
	inline _getPosition getPosition;

	typedef CharacterObject* (__thiscall* _getCharacter)(void* playerMain);
	inline _getCharacter getCharacter;

	typedef CharacterObject* (__thiscall* _getCharacterObject)(ClientPlayerInstance* clientPlayerInstance);
	inline _getCharacterObject getCharacterObject;

	typedef ClientPlayerInstance* (__thiscall* _getClientPlayer)(MirrorClientObject* mirrorClientObject);
	inline _getClientPlayer getClientPlayer;

	typedef List<MirrorClientObject*>* (__fastcall* _getAlivePlayers)(void* loadList, void* ignoredClient);
	inline _getAlivePlayers getAlivePlayers;

	typedef Transform* (__thiscall* _getTransform)(CharacterObject clientPlayer);
	inline _getTransform getTransform;

	typedef Camera* (__cdecl* _getCamera)();
	inline _getCamera getCamera;

	typedef Vector3(__thiscall* _worldToScreenPoint)(Camera* camera, Vector3* vector);
	inline _worldToScreenPoint worldToScreenPoint;
};

