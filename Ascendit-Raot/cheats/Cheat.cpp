#include "Cheat.h"

void Cheat::checkForKey() {
	for (int key : keys) {
		if (GetAsyncKeyState(key) & 1) {
			isToggled = !isToggled;
		}
	}
}

void Cheat::checkForToggle() {
	if (isEnabled == isToggled) { return; }

	isEnabled = isToggled;

	if (isEnabled) {
		onEnable();
	}
	else if (!isEnabled) {
		onDisable();
	}
}

void Cheat::addKey(int key) {
	if (!std::count(keys.begin(), keys.end(), key)) {
		keys.push_back(key);
		return;
	}
}