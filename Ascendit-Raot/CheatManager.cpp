#include "CheatManager.h"
#include "InfiniteGas.h"
#include "InfiniteStress.h"
#include "NoShootCooldown.h"
#include "ESP.h"
#include <iostream>

CheatManager cheatManager;

void CheatManager::init()
{
	modules.push_back(&infiniteGas);
	modules.push_back(&infiniteStress);
	modules.push_back(&noShootCooldown);
	modules.push_back(&esp);

	for (int i = 0; i < modules.size(); i++)
	{
		modules[i]->init();
	}

	printf("[CheatManager] All cheats successfully initialized\n");
}

void CheatManager::onUpdate(Functions* functions)
{
	for (int i = 0; i < modules.size(); i++) 
	{
		modules[i]->checkForKey(functions);
	}
}