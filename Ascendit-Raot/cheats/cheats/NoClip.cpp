#include "NoClip.h"
#include "Functions.h"
#include "Structures.h"

NoClip noClip;

void NoClip::onRenderUpdate() {
	/*
	* This would be the preferred way of getting the players position address, but its not possible
	* because getPosition() returns a copy of the original position so we are unable to get it through
	* that method :(
	*/

	/*
	uintptr_t playerPointer = mem::FindDMAAddy(functions->dllGameBaseOffset, { 0xB8, 0x0 });
	if (playerPointer == NULL) { return; }
	PlayerMain* playerMain = *(PlayerMain**) playerPointer;
	if (playerMain != nullptr) { return; }
	CharacterObject* character = functions->get_Character(playerMain);
	if (character != nullptr) { return; }
	Transform* transform = functions->getTransform(character);
	Vector3 vec = functions->getPosition(transform); // not a pointer so its a local copy of the real coords
	std::cout << vec.x << std::endl;
	*/

	/*
	* But we can at least use pointerpaths, although it is really bad practise, the weird value
	* that makes noclip possible is located 0x3C from the players root x coordinate so we can just
	* look for it by path and set it to 100 (idk why but it works)
	*/

	uintptr_t xCordPointer = utils::FindDMAAddy(Functions::gamePlayerBase + 0x017FF600, { 0x78, 0x28, 0x138, 0x28, 0xA0 });	if (xCordPointer == NULL) { return; }
	if (xCordPointer == NULL || utils::isPtrInvalid((void*)xCordPointer)) { return; }
	float* noClipAddress = (float*)(xCordPointer + 0x3C);
	*noClipAddress = 100; // Set this weird variable to 100 or something big and youll be able to go through walls
}

void NoClip::onDisable() {
	uintptr_t xCordPointer = utils::FindDMAAddy(Functions::gamePlayerBase + 0x017FF600, { 0x78, 0x28, 0x138, 0x28, 0xA0 });	if (xCordPointer == NULL) { return; }
	if (xCordPointer == NULL || utils::isPtrInvalid((void*)xCordPointer)) { return; }
	float* noClipAddress = (float*)(xCordPointer + 0x3C);
	*noClipAddress = -1; // Set this weird variable to -1 and collisions will work again
}