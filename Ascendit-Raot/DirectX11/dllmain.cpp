#include "CheatManager.h"
#include "DirectX.h"

DWORD WINAPI MainThread(LPVOID lpParameter) {

	DirectX::preInit();

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

	Sleep(1000);

	DirectX::functions = Functions(GetModuleHandle("GameAssembly.dll"));

	cheatManager.init();
	cheatManager.updateCheats(&DirectX::functions);

	FreeConsole();
	if (f) fclose(f);

	DirectX::RemoveAll();
	FreeLibraryAndExitThread((HMODULE)lpParameter, TRUE);
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