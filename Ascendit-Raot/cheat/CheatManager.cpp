#include "CheatManager.h"

void CheatManager::init() {
	for (Cheat* cheat: cheats) {
		cheat->init();
	}
}

void CheatManager::onUpdate(Functions* functions) {
	for (Cheat* cheat: cheats) {
		cheat->checkForKey(functions);
		cheat->checkForToggle(functions);
	}
}

std::vector<Cheat*> CheatManager::cheatsByCategory(cstring category) {
	std::vector<Cheat*> ret;

	for (Cheat* cheat: cheats) {
		if (cheat->category == category) {
			ret.push_back(cheat);
		}
	}

	return ret;
}