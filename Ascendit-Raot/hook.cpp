#include "hook.h"

BYTE shellJump[] = {
	0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
};

void* TrampHook64(BYTE* pSource, BYTE* pDestination, const uintptr_t dwLen)
{
	// Code copied but fully understood

	DWORD minLen = 14;

	if (dwLen < minLen) return NULL;

	void* gateway = VirtualAlloc(0, dwLen + sizeof(shellJump), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD dwOld = 0;
	VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);

	DWORD64 addressOfJump = (DWORD64)pSource + dwLen;

	// gateway
	memcpy(shellJump + 6, &addressOfJump, 8);
	memcpy((void*)((DWORD_PTR)gateway), pSource, dwLen);
	memcpy((void*)((DWORD_PTR)gateway + dwLen), shellJump, sizeof(shellJump));

	// detour
	memcpy(shellJump + 6, &pDestination, 8);
	memcpy(pSource, shellJump, sizeof(shellJump));

	for (int i = minLen; i < dwLen; i++)
	{
		*(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
	}

	VirtualProtect(pSource, dwLen, dwOld, &dwOld);
	return (void*)((DWORD_PTR)gateway);
}

void* TrampHook32(BYTE* pSource, BYTE* pDestination, const uintptr_t dwLen)
{
	DWORD minLen = 5;

	if (dwLen < minLen) return NULL;

	BYTE* gateway = (BYTE*)VirtualAlloc(0, dwLen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(gateway, dwLen, pSource, dwLen);

	uintptr_t gatewayRelativeAddr = pSource - gateway - 5;

	*(gateway + dwLen) = 0xE9;

	*(uintptr_t*)((uintptr_t)gateway + dwLen + 1) = gatewayRelativeAddr;

	// detour
	DWORD curProtection;
	VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t relativeAddress = pDestination - pSource - 5;

	*pSource = 0xE9;

	*(uintptr_t*)(pSource + 1) = relativeAddress;

	VirtualProtect(pSource, dwLen, curProtection, &curProtection);
	return gateway;
}

Hook::Hook(std::string exportName, std::string modName, BYTE* dst, BYTE* ptrToGatewayPtr, uintptr_t len)
{
	HMODULE hMod = GetModuleHandleA(modName.c_str());

	this->src = (BYTE*)GetProcAddress(hMod, exportName.c_str());
	this->dst = dst;
	this->len = len;
	this->ptrToGatewayPtr = ptrToGatewayPtr;
} 

void Hook::enable()
{
	memcpy(originalBytes, src, len);
	*(uintptr_t*)ptrToGatewayPtr = (uintptr_t)TrampHook64(src, dst, len);
	bStatus = true;
}

void Hook::disable()
{
	mem::Patch(src, originalBytes, len);
	bStatus = false;
}