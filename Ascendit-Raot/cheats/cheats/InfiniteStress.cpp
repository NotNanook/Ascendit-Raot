#include "InfiniteStress.h"
#include "Functions.h"
#include "Structures.h"

InfiniteStress infiniteStress;

void InfiniteStress::onRenderUpdate() {
	uintptr_t playerPointer = utils::FindDMAAddy(Functions::gameAssemblyBase + 0x025A0E70, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain == nullptr) { return; }

	EquipmentManager* equipmentManager = playerMain->equipmentManager;
	if (equipmentManager == nullptr) { return; }

	equipmentManager->stressModule->currentStress = 0;
}