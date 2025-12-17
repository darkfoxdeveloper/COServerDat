#include "Memory.h"

#pragma comment(lib, "psapi.lib")

BYTE FHeader1[] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC };
BYTE FHeader2[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC };

DWORD Memory::FindPattern(CHAR * Pattern, CHAR * Mask) {
	MODULEINFO ModuleInfo = { 0 };
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &ModuleInfo, sizeof(MODULEINFO));
	DWORD Base = (DWORD)ModuleInfo.lpBaseOfDll;
	DWORD Size = (DWORD)ModuleInfo.SizeOfImage;
	DWORD PatternLength = strlen(Mask);
	for (DWORD I = 0; I < Size - PatternLength; I++) {
		BOOL Found = TRUE;
		for (DWORD J = 0; J < PatternLength; J++) {
			Found &= Mask[J] == '?' || Pattern[J] == *(CHAR *)(Base + I + J);
		}
		if (Found) return Base + I;
	}
	return NULL;
}

VOID Memory::PlaceJMP(BYTE * Address, DWORD JumpTo, DWORD Length) {
	DWORD Protect, BackUp, RelAddress;
	VirtualProtect(Address, Length, PAGE_EXECUTE_READWRITE, &Protect);
	RelAddress = (DWORD)(JumpTo - (DWORD)Address) - 5;
	* Address = JMP_OPCODE;
	*((DWORD *)(Address + 0x1)) = RelAddress;
	for (DWORD A = 0x5; A < Length; A++) { * (Address + A) = NOP_OPCODE; }
	VirtualProtect(Address, Length, Protect, &BackUp);
}

VOID Memory::WriteMemory(DWORD Address, VOID * Buffer, INT Size) {
	DWORD Protect = NULL;
	VirtualProtect((VOID *)Address, Size, PAGE_EXECUTE_READWRITE, &Protect);
	WriteProcessMemory(GetCurrentProcess(), (VOID *)Address, Buffer, Size, NULL);
	VirtualProtect((VOID *)Address, Size, Protect, &Protect);
}