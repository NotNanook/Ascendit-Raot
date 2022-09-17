#include "pch.h"
#include "Functions.h"
#include "InfiniteStress.h"

InfiniteStress infiniteStress;

void InfiniteStress::onUpdate(Functions* functions)
{
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain != nullptr)
	{
		EquipmentManager* equipmentManager = playerMain->equipmentManager;
		if (equipmentManager != nullptr)
		{
			equipmentManager->stressModule->currentStress = 0;
		}
	}
}

void InfiniteStress::init()
{
	setKey(VK_NUMPAD2);
	setKey('I');
}