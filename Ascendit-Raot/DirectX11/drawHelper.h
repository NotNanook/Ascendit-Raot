#pragma once
#include "Functions.h"

#include "../Directories/ImGui/imgui.h"
#include "../Directories/ImGui/imgui_impl_dx11.h"
#include "../Directories/ImGui/imgui_impl_win32.h"

class drawHelper
{
public:
	static void drawGui(Functions* functions);
	static void setStyle();

	inline static ImGuiWindowFlags window_flags = 0;
	inline static CursorLockMode lastState = None;
	inline static ImFont* fontFutura = nullptr;
};

