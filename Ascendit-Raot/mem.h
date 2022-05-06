#pragma once
#include <windows.h>
#include <vector>

namespace mem
{
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	void Patch(BYTE* dst, BYTE* src, unsigned int size);
}