#include "utils.h"
#include "DirectX.h"
#include "MinHook.h"
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

void utils::waitBaseModuleLoaded() {
	while (!GetModuleHandleA("GameAssembly.dll")) {
		Sleep(1000);
	}
}

void utils::createDebugConsole() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

void utils::closeDebugConsole() {
	fclose(consoleFile);
	FreeConsole();
}

bool utils::CreateHook(uint16_t Index, void** Original, void* Function) {
	assert(Index >= 0 && Original != NULL && Function != NULL);
	void* target = (void*)MethodsTable[Index];
	if (MH_CreateHook(target, Function, Original) != MH_OK || MH_EnableHook(target) != MH_OK) {
		return false;
	}
	return true;
}

void utils::DisableHook(uint16_t Index) {
	assert(Index >= 0);
	MH_DisableHook((void*)MethodsTable[Index]);
}

void utils::RemoveAllHooks() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

void utils::DestroyImGui() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

DWORD __stdcall utils::EjectThread(LPVOID lpParameter) {
	DirectX::DisableHooks();
#if defined _DEBUG
	closeDebugConsole();
#endif
	FreeLibraryAndExitThread(hModule, 0);
}

bool utils::isPtrInvalid(void* p)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	if (::VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		// check the page is not a guard page
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
}

uintptr_t utils::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	if (addr == 0) { return 0; }

	for (unsigned int i = 0; i < offsets.size(); ++i) {
		// Check if the current address is valid
		if (isPtrInvalid((void*)addr)) {
			return 0;
		}

		addr = *(uintptr_t*)addr;
		if (addr == 0) { return 0; }
		addr += offsets[i];
	}
	return addr;
}