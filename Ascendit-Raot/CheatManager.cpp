#include "CheatManager.h"

CheatManager cheatManager;

void CheatManager::init() {
	modules.push_back(&infiniteGas);
	modules.push_back(&infiniteStress);
	modules.push_back(&noShootCooldown);
	modules.push_back(&esp);
	modules.push_back(&noClip);

	for (int i = 0; i < modules.size(); i++) {
		modules[i]->init();
	}
}

void CheatManager::onUpdate(Functions* functions) {
	for (int i = 0; i < modules.size(); i++) {
		modules[i]->checkForKey(functions);
		modules[i]->checkForToggle(functions);
	}
}