#include "DirectX11/DirectX.h"

DWORD WINAPI MainThread(LPVOID lpParameter) {
	DirectX::preInit(lpParameter);

	bool InitHook = false;
	while (!InitHook) {
		if (DirectX::Init()) {
			DirectX::CreateHook(8, (void**) &DirectX::oIDXGISwapChainPresent, DirectX::MJPresent);
			DirectX::CreateHook(12, (void**) &DirectX::oID3D11DrawIndexed, DirectX::MJDrawIndexed);
			InitHook = true;
		}
	}

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	// Wait for game logic library to load
	while (!GetModuleHandle("GameAssembly.dll")) {}

	DirectX::functions = Functions(GetModuleHandle("GameAssembly.dll"), GetModuleHandle("UnityPlayer.dll"));

	CheatManager::init();

	//FreeConsole();
	//if (f) fclose(f);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			DirectX::Module = hModule;
			CreateThread(0, 0, MainThread, 0, 0, 0);
			break;
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH: break;
	}
	return TRUE;
}