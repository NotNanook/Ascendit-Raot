#include "ESP.h"
#include "Functions.h"
#include "ImGui/imgui.h"

ESP esp;

std::vector<Vector3> playerPosList;
Camera* camera;

int getAlivePlayerCount(MirrorClientObject* buffer[]) {
	int count = 0;
	for (int i = 0; i < 64; i++) {
		count++;
		if (buffer[i] == 0x0000000000000000) {
			return count;
		}
	}
	return count;
}

float calculateRadius(float distance, float minRadius, float maxRadius) {
	if (distance <= 100) {
		return  maxRadius;
	}
	else if (distance >= 200) {
		return minRadius;
	}
	else {
		float scaleFactor = (distance - 100) / (2000 - 100);
		float scaledRadius = (1 - scaleFactor) * maxRadius + scaleFactor * minRadius;
		return scaledRadius;
	}
}

void ESP::onRenderUpdate() {
	List<MirrorClientObject*>* playerList = Functions::getAlivePlayersSafe(NULL, NULL);
	if (playerList == nullptr) return;
	int alivePlayerCount = getAlivePlayerCount(playerList->content->buffer);

	camera = Functions::getCamera();
	playerPosList.clear();

	// get local player position
	uintptr_t xCordPointer = utils::FindDMAAddy(Functions::gamePlayerBase + 0x017FF600, { 0x78, 0x28, 0x138, 0x28, 0xA0 });
	if (xCordPointer == NULL) { return; }
	float* localXCord = (float*)xCordPointer;
	float* localYCord = (float*)(xCordPointer+0x4);
	float* localZCord = (float*)(xCordPointer+0x8);

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	for (int i = 0; i < alivePlayerCount - 1; i++) {
		MirrorClientObject* playerOne = playerList->content->buffer[i];
		ClientPlayerInstance* clientPlayerInstance = Functions::getClientPlayerSafe(playerOne);
		if (clientPlayerInstance != nullptr) {
			CharacterObject* characterObject = Functions::getCharacterObject(clientPlayerInstance);
			Transform* transform = Functions::getTransform(*characterObject);

			Vector3 vecOther;
			Functions::getPosition(transform, &vecOther);
			vecOther.y += 1;

			Vector3 screenPos = Functions::worldToScreenPoint(camera, &vecOther);
			if (screenPos.z > 0) {
				screenPos.y = (ImGui::GetIO().DisplaySize.y - screenPos.y);
			}

			float distance = std::sqrtf((std::pow(*localXCord - vecOther.x, 2) +
				std::pow(*localYCord - vecOther.y, 2) +
				std::pow(*localZCord - vecOther.z, 2)));

			if (distance < 1) return; // Dont draw esp on yourself

			float scaledRadius = calculateRadius(distance, 3, 5);
			drawList->AddCircleFilled(ImVec2(screenPos.x, screenPos.y), scaledRadius, ImColor(255, 255, 255, 170));
		}
	}
}