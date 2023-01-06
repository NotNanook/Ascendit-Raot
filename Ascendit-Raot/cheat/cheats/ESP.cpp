#include "ESP.h"

ESP esp;

void ESP::onEnable(Functions* functions) {
	std::cout << "On Enable" << std::endl;
}

void ESP::onUpdate(Functions* functions) {
	/*
	IL2CPP::Initialize();
	Unity::CGameObject* pLocal = Unity::GameObject::Find("PlayerMain");
	Unity::CComponent* pLocalChar = pLocal->GetComponent("CharacterObject");
	std::cout << "New way: " << pLocalChar << std::endl;

	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain != nullptr)
	{
		CharacterObject* character = functions->get_Character(playerMain);
		if (character != nullptr)
		{
			std::cout << "Normal way: " << character << std::endl;
		}
	}
	*/
}

void ESP::init() {
	addKey(VK_NUMPAD4);
}