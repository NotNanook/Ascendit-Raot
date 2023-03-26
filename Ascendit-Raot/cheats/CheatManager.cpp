#include "CheatManager.h"
#include "DirectX.h"

void CheatManager::init() {
	for (Cheat* cheat: cheats) {
		cheat->init();
	}
}

void CheatManager::checkUserInput() {
	for (Cheat* cheat: cheats) {
		if(DirectX::isWindowFocused()) cheat->checkForKey();
		cheat->checkForToggle();
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

void CheatManager::onRenderUpdate() {
	for (Cheat* cheat : cheats) {
		if (cheat->isEnabled) {
			cheat->onRenderUpdate();
		}
	}
}