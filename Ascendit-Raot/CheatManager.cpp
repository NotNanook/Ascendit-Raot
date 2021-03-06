#include "pch.h"
#include "CheatManager.h"
#include "InfiniteGas.h"
#include "InfiniteStress.h"
#include "NoShootCooldown.h"

CheatManager cheatManager;

void CheatManager::init()
{
	modules.push_back(&infiniteGas);
	modules.push_back(&infiniteStress);
	modules.push_back(&noShootCooldown);

	for (int i = 0; i < modules.size(); i++)
	{
		modules[i]->init();
	}
}

void CheatManager::onUpdate(Functions* functions)
{
	for (int i = 0; i < modules.size(); i++) 
	{
		modules[i]->checkForKey(functions);
	}
}