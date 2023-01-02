#include "NoClip.h"

NoClip noClip;

void NoClip::onUpdate(Functions* functions) {
	/* This would be the preferred way of getting the players position address, but its not possible
	*  because getPosition() return a copy of the original position so we are unable to get it through
	*  that method :(
	*/
	/*
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }

	PlayerMain* playerMain = *(PlayerMain**)playerPointer;
	if (playerMain != nullptr)
	{
		CharacterObject* character = functions->get_Character(playerMain);
		if (character != nullptr)
		{
			Transform* transform = functions->getTransform(character);
			Vector3 vec = functions->getPosition(transform); // not a pointer so its a local copy of the real coords
			std::cout << vec.x << std::endl;
		}
	}
	*/

	/*
	* But we can at least use pointerpaths, although it is really bad practise, the weird value
	* that makes noclip possible is located 0x3C from the players root x coordinate so we can just
	* look for it by path and set it to 100 (idk why but it works)
	*/
	uintptr_t xCordPointer = mem::FindDMAAddy(functions->dllPlayerBaseOffset, {0x30, 0x30, 0x0, 0x20});
	if (xCordPointer == NULL) { return; }

	float* noClipAddress = (float*)(xCordPointer + 0x3C);
	*noClipAddress = 100; // Set this weird variable to 100 or something big and youll be able to go through walls
}

void NoClip::init() {
	setKey('N');
}