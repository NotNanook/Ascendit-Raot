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
			HoldableItem* holdable = character->holableItem;
			if (holdable != nullptr)
			{
				character->holableItem->isLoadedLeft = 1;
				character->holableItem->isLoadedRight = 1;
			}
		}
	}
}

void NoShootCooldown::init()
{
	setKey(VK_NUMPAD3);
}