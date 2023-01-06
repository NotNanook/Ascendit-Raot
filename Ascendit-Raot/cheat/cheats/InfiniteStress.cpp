#include "InfiniteStress.h"

InfiniteStress infiniteStress;

void InfiniteStress::onUpdate(Functions* functions) {
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**) playerPointer;
	if (playerMain == nullptr) { return; }
	
	EquipmentManager* equipmentManager = playerMain->equipmentManager;
	if (equipmentManager == nullptr) { return; }
	
	equipmentManager->stressModule->currentStress = 0;
}

void InfiniteStress::init() {
	addKey(VK_NUMPAD2);
	addKey('I');
}