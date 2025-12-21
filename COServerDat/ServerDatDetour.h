#include "detours.h"
#include <windows.h>
#include <iostream>
#pragma once

class ServerDatDetour
{
	typedef HMODULE(_stdcall* HookLoadLibrary)(_In_ LPCWSTR lpLibFileName,
		_Reserved_ HANDLE hFile,
		_In_ DWORD dwFlags);
public:
	static void Init();
};