#include "CheatManager.h"
#include "directHelper.h"

DWORD WINAPI MainThread(LPVOID lpParameter) {

	// DirectX Related Code
	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetCurrentProcessId() == ForegroundWindowProcessID) {

			Process::ID = GetCurrentProcessId();
			Process::Handle = GetCurrentProcess();
			Process::Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Process::Hwnd, &TempRect);
			Process::WindowWidth = TempRect.right - TempRect.left;
			Process::WindowHeight = TempRect.bottom - TempRect.top;

			char TempTitle[MAX_PATH];
			GetWindowText(Process::Hwnd, TempTitle, sizeof(TempTitle));
			Process::Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Process::Hwnd, TempClassName, sizeof(TempClassName));
			Process::ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Process::Handle, NULL, TempPath, sizeof(TempPath));
			Process::Path = TempPath;

			WindowFocus = true;
		}
	}
	bool InitHook = false;
	while (InitHook == false) {
		if (DirectX11::Init() == true) {
		    CreateHook(8, (void**)&oIDXGISwapChainPresent, MJPresent);
			CreateHook(12, (void**)&oID3D11DrawIndexed, MJDrawIndexed);
			InitHook = true;
		}
	}

	// Cheats Related Code
	Sleep(1000);

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	functions = Functions((uintptr_t)GetModuleHandle("GameAssembly.dll"));

	cheatManager.init();
	cheatManager.updateCheats(&functions);

	FreeConsole();
	if (f) fclose(f);

	RemoveAll();
	FreeLibraryAndExitThread((HMODULE)lpParameter, TRUE);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, 
					   DWORD   ul_reason_for_call,
					   LPVOID  lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		Process::Module = hModule;
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