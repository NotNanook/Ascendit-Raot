#include "pch.h"
#include "Functions.h"
#include "InfiniteGas.h"

InfiniteGas infiniteGas;

void InfiniteGas::onUpdate(Functions* functions) 
{
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain != nullptr)
	{
		EquipmentManager* equipmentManager = playerMain->equipmentManager;
		if (equipmentManager != nullptr)
		{
			equipmentManager->gasModule->gasPercent = 1;
		}
	}
}

void InfiniteGas::init()
{
	setKey(VK_NUMPAD1);
	setKey('U');
}