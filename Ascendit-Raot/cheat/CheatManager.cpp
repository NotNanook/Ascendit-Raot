#include "CheatManager.h"

CheatManager cheatManager;

void CheatManager::init() {
	cheats = {
		&infiniteGas,
		&infiniteStress,
		&noShootCooldown,
		&esp,
		&noClip
	};
	
	for (Cheat* cheat: cheats) {
		cheat->init();
	}
}

void CheatManager::add(Cheat cheat) {
	cheats.push_back(&cheat);
}

void CheatManager::onUpdate(Functions* functions) {
	for (Cheat* cheat: cheats) {
		cheat->checkForKey(functions);
		cheat->checkForToggle(functions);
	}
}