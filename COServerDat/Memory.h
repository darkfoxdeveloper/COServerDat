#pragma once
#include "stdio.h"
#include "Common.h"

#define NOP_OPCODE 0x90
#define JMP_OPCODE 0xE9

class Memory
{
public:	
	static DWORD FindPattern(CHAR * Pattern, CHAR * Mask);
	static VOID WriteMemory(DWORD Address, VOID * Buffer, INT Size);
	static VOID PlaceJMP(BYTE * Address, DWORD JumpTo, DWORD Length);	
};