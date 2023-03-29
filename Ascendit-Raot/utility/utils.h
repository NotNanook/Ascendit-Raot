#pragma once
#include <iostream>
#include <Windows.h>
#include <cassert>
#include <vector>

typedef const char* cstring;

namespace utils {

	void waitBaseModuleLoaded();
	void createDebugConsole();
	void closeDebugConsole();

	bool CreateHook(uint16_t Index, void** Original, void* Function);
	void DisableHook(uint16_t Index);
	void RemoveAllHooks();
	void DestroyImGui();

	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	DWORD __stdcall EjectThread(LPVOID lpParameter);

	inline uint64_t* MethodsTable;
	inline HMODULE hModule;
	inline FILE* consoleFile;
}

