
#include <stdint.h>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <Windows.h>
#include <sstream>
#include <ostream>
#include <wininet.h>
#include <algorithm>
#include <functional>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <istream>
#include <iterator>
#include <stdio.h>
#include <iostream>
#include <Psapi.h>
#include <intrin.h>
#include <iphlpapi.h>
#include <thread>
#include <iostream>
#include <string>
#include <thread>
#include <iomanip>
#include <time.h>
#include <WinUser.h>
#include <sstream>
#define snprintf _snprintf
#pragma warning(disable:4996)

//soo basically __stdcall is WINAPI (just use WINAPI more shorter)
#pragma region others stuff

MODULEINFO GetModuleInfo(HMODULE hModule)
{
	MODULEINFO mInfo = { 0 };
	GetModuleInformation(GetCurrentProcess(), hModule, &mInfo, sizeof(MODULEINFO));
	return mInfo;
}

uintptr_t FindPattern(uintptr_t lpBaseOfDll, uintptr_t SizeOfImage, const UCHAR* pattern, const CHAR* mask)
{
	uintptr_t Length = (uintptr_t)(strlen(mask));

	for (size_t i = 0; i < SizeOfImage - Length; i++)
	{
		INT Found = TRUE;
		for (size_t x = 0; x < Length; x++)
			Found &= mask[x] == '?' || pattern[x] == *(const UCHAR*)(lpBaseOfDll + i + x);
		if (Found)
			return (uintptr_t)(lpBaseOfDll + i);
	}
	return -1;
}

uintptr_t FindPattern(HMODULE hModule, const UCHAR* pattern, const CHAR* mask)
{
	MODULEINFO mInfo = GetModuleInfo(hModule);
	uintptr_t lpBaseOfDll = (uintptr_t)(mInfo.lpBaseOfDll);
	uintptr_t SizeOfImage = (uintptr_t)(mInfo.SizeOfImage);
	return FindPattern(lpBaseOfDll, SizeOfImage, pattern, mask);
}


#pragma endregion
