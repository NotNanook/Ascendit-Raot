#pragma once
#include "mem.h"
#include <Windows.h>
#include <iostream>

void* TrampHook64(BYTE* src, BYTE* dst, uintptr_t len);

struct Hook
{
	bool bStatus{ false };

	BYTE* src{ nullptr };
	BYTE* dst{ nullptr };
	BYTE* ptrToGatewayPtr{ nullptr };
	int len{ 0 };

	BYTE originalBytes[15]{ 0 };

	Hook();
	Hook(std::string exportName, std::string modName, BYTE* dst, BYTE* ptrToGatewayPtr, uintptr_t len);

	void enable();
	void disable();
};