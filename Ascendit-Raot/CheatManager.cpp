#include "CheatManager.h"

CheatManager cheatManager;

void CheatManager::init() {
	modules.push_back(&infiniteGas);
	modules.push_back(&infiniteStress);
	modules.push_back(&noShootCooldown);
	modules.push_back(&esp);

	for (int i = 0; i < modules.size(); i++) {
		modules[i]->init();
	}
}

void CheatManager::onUpdate(Functions* functions) {
	for (int i = 0; i < modules.size(); i++) {
		modules[i]->checkForKey(functions);
	}
}

void CheatManager::updateCheats(Functions* functions) {
	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) { break; }

		CheatManager::onUpdate(functions);

		Sleep(10);
	}
}