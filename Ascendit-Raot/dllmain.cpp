#include "pch.h"
#include "CheatManager.h"
#include "Functions.h"

DWORD WINAPI Thread(HMODULE hModule)
{
    Sleep(1000);

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    Functions functions = Functions((uintptr_t)GetModuleHandleW(L"GameAssembly.dll"));
    cheatManager.init();

    while (true)
    {
        if (GetAsyncKeyState(VK_NUMPAD0) & 1) { break; }

        cheatManager.onUpdate(&functions);

        Sleep(10);
    }  

    FreeConsole();
    if(f) fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

