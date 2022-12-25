#include "Cheat.h"

void Cheat::checkForKey(Functions* functions)
{
	for (int key : this->keys) {

		if (GetAsyncKeyState(key) & 1) {
			this->isEnabled = !this->isEnabled;
			this->isToggled = !this->isToggled;

			if (this->isEnabled) {
				this->onEnable(functions);
			}
			else {
				this->onDisable(functions);
			}
		}

		if (this->isEnabled)
		{
			this->onUpdate(functions);
		}

	}
}

void Cheat::checkForToggle(Functions* functions)
{
	if (this->isToggled && !this->isEnabled) {
		this->onEnable(functions);
		this->isEnabled = true;
	}
	else if (!this->isToggled && this->isEnabled) {
		this->onDisable(functions);
		this->isEnabled = false;
	}
}

void Cheat::setKey(int key)
{
	if (!std::count(this->keys.begin(), this->keys.end(), key)) {
		this->keys.push_back(key);
		return;
	}
	std::cout << "Key already used for this module" << std::endl;
}