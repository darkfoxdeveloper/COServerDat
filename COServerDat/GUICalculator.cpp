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
	const LPVOID BASE_W_ADDR = (LPVOID)(Memory::FindPatternN("\xC7\x05\x3C\xB8\x70\x00\x00\x04\x00\x00", "xxxxxxxxxx", 1) + 6);
	const LPVOID BASE_H_ADDR = (LPVOID)(Memory::FindPatternN("\xC7\x05\x3C\xB8\x70\x00\x00\x04\x00\x00", "xxxxxxxxxx", 2) + 6);

	const LPVOID BASE_PUZZLE_W_ADDR = (LPVOID)(0x004AD21A + 1);
	const LPVOID BASE_PUZZLE_H_ADDR = (LPVOID)(0x004AD231 + 1);
	const LPVOID BASE_PUZZLE_H2_ADDR = (LPVOID)(0x004AD251 + 1);

	const LPVOID BASE_MAIN_UI0_ADDR = (LPVOID)(0x00488D09 + 1);
	const LPVOID BASE_MAIN_UI1_ADDR = (LPVOID)(0x00488D0E + 1);
	//Memory::WriteMemory();
}