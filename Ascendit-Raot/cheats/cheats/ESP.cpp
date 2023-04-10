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

void ESP::onRenderUpdate() {
	List<MirrorClientObject*>* playerList = Functions::getAlivePlayers(NULL, NULL);
	int alivePlayerCount = getAlivePlayerCount(playerList->content->buffer);

	camera = Functions::getCamera();
	playerPosList.clear();

	for (int i = 0; i < alivePlayerCount - 1; i++) {
		MirrorClientObject* playerOne = playerList->content->buffer[i];
		ClientPlayerInstance* clientPlayerInstance = Functions::getClientPlayer(playerOne);
		CharacterObject* characterObject = Functions::getCharacterObject(clientPlayerInstance);
		Transform* transform = Functions::getTransform(*characterObject);

		Vector3 out;
		Functions::getPosition(transform, &out);
		if (out.z > -8) {
			playerPosList.push_back(out);
		}
	}

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	for (Vector3 vec : playerPosList) {
		Vector3 screenPos = Functions::worldToScreenPoint(camera, &vec);
		if (screenPos.z > 0) {
			screenPos.y = (ImGui::GetIO().DisplaySize.y - screenPos.y);
		}

		drawList->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImVec2(screenPos.x, screenPos.y), ImColor(255, 255, 255, 170), 1.0f);
	}
}