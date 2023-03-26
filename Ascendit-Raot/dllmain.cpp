#include "CheatManager.h"
#include "DirectX.h"
#include "MinHook.h"
#include "Functions.h"
#include "utils.h"

DWORD WINAPI MainThread(LPVOID lpParameter) {

    utils::waitBaseModuleLoaded();

    MH_Initialize();
    CheatManager::init();
    Functions::init();
    
    DirectX::getWindowInformation();
    DirectX::hookDirectX();

#if defined _DEBUG
    utils::createDebugConsole();
#endif

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, MainThread, 0, 0, 0);
    }
    return TRUE;
}