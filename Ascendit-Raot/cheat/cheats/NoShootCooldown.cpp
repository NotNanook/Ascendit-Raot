#include "NoShootCooldown.h"

NoShootCooldown noShootCooldown;

void NoShootCooldown::onUpdate(Functions* functions) {
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**) playerPointer;
	if (playerMain == nullptr) { return; }

	CharacterObject* character = functions->get_Character(playerMain);
	if (character == nullptr) { return; }

	HoldableItem* holdable = character->equipedItem;
	if (holdable == nullptr) { return; }

	character->equipedItem->isLeftLoaded = 1;
	character->equipedItem->isRightLoaded = 1;
}