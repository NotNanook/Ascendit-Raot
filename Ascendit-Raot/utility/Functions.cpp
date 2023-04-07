#include "Functions.h"
#include <Windows.h>
#include <iostream>

void Functions::init() {

	gameAssemblyBase = (uintptr_t)GetModuleHandle("GameAssembly.dll");
	gamePlayerBase = (uintptr_t)GetModuleHandle("UnityPlayer.dll");

	getLockState = (_get_lockState)(gameAssemblyBase + 0x1264B70);
	setLockState = (_set_lockState)(gameAssemblyBase + 0x1264BC0);
	getCharacter = (_getCharacter)(gameAssemblyBase + 0x8EEBF0);
	getCharacterObject = (_getCharacterObject)(gameAssemblyBase + 0x434DB0);
	getClientPlayer = (_getClientPlayer)(gameAssemblyBase + 0x3DC870);
	getAlivePlayers = (_getAlivePlayers)(gameAssemblyBase + 0x52D400);
	getTransform = (_getTransform)(gameAssemblyBase + 0x672290);
	getPosition = (_getPosition)(gameAssemblyBase + 0x1173DF0);
	getCamera = (_getCamera)(gameAssemblyBase + 0x125EDD0);
	worldToScreenPoint = (_worldToScreenPoint)(gameAssemblyBase + 0x125E960);
}