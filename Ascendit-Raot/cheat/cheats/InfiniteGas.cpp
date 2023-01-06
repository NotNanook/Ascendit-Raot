#include "InfiniteGas.h"

InfiniteGas infiniteGas;

void InfiniteGas::onUpdate(Functions* functions) {
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**) playerPointer;
	if (playerMain == nullptr) { return; }

	EquipmentManager* equipmentManager = playerMain->equipmentManager;
	if (equipmentManager == nullptr) { return; }
	
	equipmentManager->gasModule->gasPercent = 1;
}

void InfiniteGas::init() {
	addKey(VK_NUMPAD1);
	addKey('K');
}