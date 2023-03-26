#include "NoShootCooldown.h"
#include "Functions.h"
#include "Structures.h"

NoShootCooldown noShootCooldown;

void NoShootCooldown::onRenderUpdate() {
	uintptr_t playerPointer = utils::FindDMAAddy(Functions::gameAssemblyBase + 0x025A0E70, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain == nullptr) { return; }

	CharacterObject* character = Functions::getCharacter(playerMain);
	if (character == nullptr) { return; }

	HoldableItem* holdable = character->equipedItem;
	if (holdable == nullptr) { return; }

	character->equipedItem->isLeftLoaded = 1;
	character->equipedItem->isRightLoaded = 1;
}