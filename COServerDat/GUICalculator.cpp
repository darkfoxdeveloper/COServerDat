#include "GUICalculator.h"
#include "Memory.h"

const char CONFIG_FILE[]{ ".\\Settings.ini" };
int width = GetPrivateProfileIntA("GameResolution", "Width", 1024, CONFIG_FILE);
int height = GetPrivateProfileIntA("GameResolution", "Height", 768, CONFIG_FILE);

VOID GUICalculator::FullScreen()
{
	struct tagRECT pInfo;
	GetWindowRect(GetDesktopWindow(), &pInfo);

	if (GetPrivateProfileInt(TEXT("Settings"), TEXT("FullScreen"), 0, TEXT("../Settings.ini")) > NULL)
		Calculator(pInfo.right, pInfo.bottom, TRUE);
	else Calculator(1024, 768, FALSE);
}

// TODO tengo que encontrar una version que funcione realmente bien
VOID GUICalculator::Calculator(INT Width, INT Height, BOOL IsFull)
{
	WCHAR NWidth[128];
	WCHAR NHeight[128];
	wsprintf(NWidth, TEXT("%d"), Width);
	wsprintf(NHeight, TEXT("%d"), Height);
	WritePrivateProfileString(TEXT("ScreenMode"), TEXT("ScrWidth"), NWidth, TEXT("../ini/GameSetup.ini"));
	WritePrivateProfileString(TEXT("ScreenMode"), TEXT("ScrHeight"), NHeight, TEXT("../ini/GameSetup.ini"));

	if (IsFull)
	{
		WritePrivateProfileString(TEXT("ScreenMode"), TEXT("FullScrType"), TEXT("1"), TEXT("../ini/GameSetup.ini"));
		WritePrivateProfileString(TEXT("ScreenMode"), TEXT("ScreenModeRecord"), TEXT("4"), TEXT("../ini/GameSetup.ini"));
	}
	else
	{
		WritePrivateProfileString(TEXT("ScreenMode"), TEXT("FullScrType"), TEXT("1"), TEXT("../ini/GameSetup.ini"));
		WritePrivateProfileString(TEXT("ScreenMode"), TEXT("ScreenModeRecord"), TEXT("2"), TEXT("../ini/GameSetup.ini"));
	}
}

VOID GUICalculator::ChangeScreenSize() {
	int width = GetPrivateProfileIntA("GameResolution", "Width", 1920, CONFIG_FILE); // 1024
	int height = GetPrivateProfileIntA("GameResolution", "Height", 1024, CONFIG_FILE); // 768
	const DWORD BASE_W_ADDR = (Memory::FindPatternN("\xC7\x05\x3C\xB8\x70\x00\x00\x04\x00\x00", "xxxxxxxxxx", 1) + 6);
	const DWORD BASE_H_ADDR = (Memory::FindPatternN("\xC7\x05\x3C\xB8\x70\x00\x00\x04\x00\x00", "xxxxxxxxxx", 2) + 6);
	const DWORD BASE_PUZZLE_W_ADDR = (Memory::FindPatternN("\xB9\x20\x03\x00\x00", "xxxxxxxxxx", 1) + 1);
	const DWORD BASE_PUZZLE_H_ADDR = (Memory::FindPatternN("\xB8\x58\x02\x00\x00", "xxxxxxxxxx", 1) + 1);
	const DWORD BASE_PUZZLE_H2_ADDR = (Memory::FindPatternN("\xB8\x58\x02\x00\x00", "xxxxxxxxxx", 2) + 1);
	const DWORD BASE_MAIN_UI0_ADDR = (Memory::FindPatternN("\xFF\x15\x00\x00\x00\x00\x2D\x00\x00\x00\x00\x8D\x8E\x00\x00\x00\x00\x50\x53\xE8\x00\x00\x00\x00", "xx????x????xx????xxx????", 1) + 1);
	const DWORD BASE_MAIN_UI1_ADDR = (Memory::FindPatternN("\xFF\x15\x00\x00\x00\x00\x2D\x00\x00\x00\x00\x8D\x8E\x00\x00\x00\x00\x50\x53\xE8\x00\x00\x00\x00", "xx????x????xx????xxx????", 1) + 5 + 1);
	Memory::WriteMemory(BASE_W_ADDR, &width, 4);
	Memory::WriteMemory(BASE_H_ADDR, &height, 4);
	Memory::WriteMemory(BASE_PUZZLE_W_ADDR, &width, 4);
	Memory::WriteMemory(BASE_PUZZLE_H_ADDR, &height, 4);
	Memory::WriteMemory(BASE_PUZZLE_H2_ADDR, &height, 4);
	int positionUI0 = height - 141;
	int positionUI1 = (width - 1024) / 2;
	Memory::WriteMemory(BASE_MAIN_UI0_ADDR, &positionUI0, 4);
	Memory::WriteMemory(BASE_MAIN_UI1_ADDR, &positionUI1, 4);
	// en 6609 no va pero... teoricamente deberia ir en 5065 o en 5187
}