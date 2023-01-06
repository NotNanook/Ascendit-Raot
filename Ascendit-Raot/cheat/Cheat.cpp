#include "Cheat.h"

void Cheat::checkForKey(Functions* functions) {
	for (int key: keys) {
		if (GetAsyncKeyState(key) & 1) {
			isEnabled = !isEnabled;
			isToggled = !isToggled;

			if (isEnabled) {
				onEnable(functions);
			} else {
				onDisable(functions);
			}
		}

		if (isEnabled) {
			onUpdate(functions);
		}
	}
}

void Cheat::checkForToggle(Functions* functions) {
	if (isToggled && !isEnabled) {
		onEnable(functions);
		isEnabled = true;
	} else if (!isToggled && isEnabled) {
		onDisable(functions);
		isEnabled = false;
	}
}

void Cheat::addKey(int key) {
	if (!std::count(keys.begin(), keys.end(), key)) {
		keys.push_back(key);
		return;
	}
	std::cout << "Key already used for this module" << std::endl;
}