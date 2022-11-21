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
			HoldableItem* holdable = character->equipedItem;
			if (holdable != nullptr)
			{
				character->equipedItem->isLeftLoaded = 1;
				character->equipedItem->isRightLoaded = 1;
			}
		}
	}
}

void NoShootCooldown::init()
{
	setKey(VK_NUMPAD3);
	setKey('O');
}