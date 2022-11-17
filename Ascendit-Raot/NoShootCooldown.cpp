#include "pch.h"
#include "Functions.h"
#include "NoShootCooldown.h"

NoShootCooldown noShootCooldown;

void NoShootCooldown::onUpdate(Functions* functions)
{
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain != nullptr)
	{
		CharacterObject* character = functions->get_Character(playerMain);
		if (character != nullptr)
		{
			HoldableItem* holdable = character->holdableItem;
			if (holdable != nullptr)
			{
				character->holdableItem->isLeftLoaded = 1;
				character->holdableItem->isRightLoaded = 1;
			}
		}
	}
}

void NoShootCooldown::init()
{
	setKey(VK_NUMPAD3);
	setKey('O');
}