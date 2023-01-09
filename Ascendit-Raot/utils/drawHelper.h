#pragma once
#include "Functions.h"

#include "../dependencies/ImGui/imgui.h"
#include "../dependencies/ImGui/imgui_impl_dx11.h"
#include "../dependencies/ImGui/imgui_impl_win32.h"

namespace drawHelper {
	void drawGui(Functions* functions);
	void setStyle();

	inline ImGuiWindowFlags window_flags = 0;
	inline CursorLockMode lastState = None;
	inline ImFont* fontFutura = nullptr;
};