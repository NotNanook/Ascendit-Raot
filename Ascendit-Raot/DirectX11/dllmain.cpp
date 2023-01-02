#include "DirectX.h"

DWORD WINAPI MainThread(LPVOID lpParameter) {

	DirectX::preInit(lpParameter);

	bool InitHook = false;
	while (InitHook == false) {
		if (DirectX::Init() == true) {
			DirectX::CreateHook(8, (void**)&DirectX::oIDXGISwapChainPresent, DirectX::MJPresent);
			DirectX::CreateHook(12, (void**) &DirectX::oID3D11DrawIndexed, DirectX::MJDrawIndexed);
			InitHook = true;
		}
	}

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	// Wait for game logic library to load
	while (!GetModuleHandle("GameAssembly.dll")) { continue; }

	DirectX::functions = Functions(GetModuleHandle("GameAssembly.dll"), GetModuleHandle("UnityPlayer.dll"));

	cheatManager.init();

	//FreeConsole();
	//if (f) fclose(f);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD   ul_reason_for_call,
	LPVOID  lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		DirectX::Module = hModule;
		CreateThread(0, 0, MainThread, 0, 0, 0);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}