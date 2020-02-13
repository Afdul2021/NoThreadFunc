#include "Include.h"

using namespace std;

bool Hentais(void* toHook, void* ourFunct, int len) {
	if (len < 5) {
		return false;
	}
	DWORD curProtection;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
	memset(toHook, 0x90, len);
	DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;
	*(BYTE*)toHook = 0xE9;
	*(DWORD*)((DWORD)toHook + 1) = relativeAddress;
	DWORD temp;
	VirtualProtect(toHook, len, curProtection, &temp);
	return true;
}




void HackFunctions()
{
	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		cout << "HP Hack - F1 Pressed" << endl;
		//LocalHacks(Health, 99999, false);
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		cout << "F2 Pressed" << endl;
	}
}

DWORD AddressReturn;
void __declspec(naked) OurRoutines() 
{
	__asm
	{
		mov esi, [ebp + 8]
		mov ecx, esi
		PUSHAD
	}
	HackFunctions();
	__asm
	{
		POPAD
		jmp[AddressReturn]
	}
}


void CreateAlternativeThreads()
{
	DWORD Address = 0x6CE563EB;//0x6CD946AC;
	DWORD length = 5;
	AddressReturn = Address + length;
	Hentais((void*)Address, OurRoutines, length);
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	// ??\x6F\x??\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x??\x??\x00\x00\x??\x??\x??\x00\x00\x00\x00\x00\x0B
}

BOOL APIENTRY DllMain(HMODULE modulers, DWORD reason_trap_loli, LPVOID loliFBI)
{
	if (reason_trap_loli == DLL_PROCESS_ATTACH)
	{
		Sleep(1000);
		CreateAlternativeThreads();
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackFunctions, 0, 0, 0);
	}
	return true;
}
