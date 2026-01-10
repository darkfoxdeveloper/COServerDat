#include "GUICalculator.h"
#include "Memory.h"
#include "WindowHook.h"

const char CONFIG_FILE[]{ ".\\Settings.ini" };
int width = GetPrivateProfileIntA("GameResolution", "Width", 1024, CONFIG_FILE);
int height = GetPrivateProfileIntA("GameResolution", "Height", 768, CONFIG_FILE);
std::string msg = "";

VOID ChangeScreenSizes(LPVOID BASE_W_ADDR, LPVOID BASE_H_ADDR, LPVOID BASE_W2_ADDR, LPVOID BASE_H2_ADDR, LPVOID BASE_PUZZLE_W_ADDR, LPVOID BASE_PUZZLE_H_ADDR, LPVOID BASE_PUZZLE_H2_ADDR, LPVOID BASE_ARROW_ADDR, LPVOID BASE_HELP_BUTTON_ADDR, BOOL DEBUG_READ = false) {
	HANDLE hProcess = GetCurrentProcess();
	DWORD dwProc = (DWORD)hProcess;
	int read = 0;
	SIZE_T bytes_read = 0, bytes_written = 0;
	if (BASE_W_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_W_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get width memory offset. 1", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_W_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_W_ADDR, &width, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 1 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_H_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_H_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 2", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_H_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_H_ADDR, &height, 4, &bytes_written)) {
				/*	sprintf_s(msg, "Error writing to memory! 2 %d", GetLastError());
					MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_W2_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_W2_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get width memory offset. 1", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_W2_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_W2_ADDR, &width, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 1 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_H2_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_H2_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 2", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_H2_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_H2_ADDR, &height, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 2 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_PUZZLE_W_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_PUZZLE_W_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get width memory offset. 3", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_PUZZLE_W_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_PUZZLE_W_ADDR, &width, 4, &bytes_written)) {
				/*	sprintf_s(msg, "Error writing to memory! 3 %d", GetLastError());
					MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_PUZZLE_H_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_PUZZLE_H_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 4", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_PUZZLE_H_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_PUZZLE_H_ADDR, &height, 4, &bytes_written)) {
				/*	sprintf_s(msg, "Error writing to memory! 4 %d", GetLastError());
					MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_PUZZLE_H2_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_PUZZLE_H2_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 4", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_PUZZLE_H2_ADDR", MB_OK);
			}

			if (!WriteProcessMemory(hProcess, BASE_PUZZLE_H2_ADDR, &height, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 4 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_ARROW_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_ARROW_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 6", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_ARROW_ADDR", MB_OK);
			}

			int position = ((width - 1024) / 2) + 131;
			if (!WriteProcessMemory(hProcess, BASE_ARROW_ADDR, &position, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 6 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (BASE_HELP_BUTTON_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_HELP_BUTTON_ADDR, &read, 1, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 9", "ReadProcessMemory error", MB_OK);

			if (DEBUG_READ) {
				char buffer[64];
				sprintf_s(buffer, sizeof(buffer), "Read value: %d", read);
				MessageBoxA(NULL, buffer, "BASE_HELP_BUTTON_ADDR", MB_OK);
			}

			int position = -30;
			if (!WriteProcessMemory(hProcess, BASE_HELP_BUTTON_ADDR, &position, 1, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 9 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}
}

VOID GUICalculator::ChangeScreenSize(DWORD VERSION) {
	if(VERSION == 5187) {
		const LPVOID BASE_W_ADDR = (LPVOID)(0x004EB22F + 6);
		const LPVOID BASE_H_ADDR = (LPVOID)(0x004EB239 + 6);
		const LPVOID BASE_W2_ADDR = (LPVOID)(0x004ED815 + 6);// new location pos=width
		const LPVOID BASE_H2_ADDR = (LPVOID)(0x004ED81F + 6);// new location pos=height
		const LPVOID BASE_PUZZLE_W_ADDR = (LPVOID)(0x00539C34 + 1);
		const LPVOID BASE_PUZZLE_H_ADDR = (LPVOID)(0x00539C4B + 1);
		const LPVOID BASE_PUZZLE_H2_ADDR = (LPVOID)(0x00539C6B + 1);
		const LPVOID BASE_ARROW_ADDR = (LPVOID)(0x00553B2D + 3); // int position = ((width - 1024) / 2) + 131;
		const LPVOID BASE_HELP_BUTTON_ADDR = (LPVOID)(0x0045649C + 1);
		ChangeScreenSizes(BASE_W_ADDR, BASE_H_ADDR, BASE_W2_ADDR, BASE_H2_ADDR, BASE_PUZZLE_W_ADDR, BASE_PUZZLE_H_ADDR, BASE_PUZZLE_H2_ADDR, BASE_ARROW_ADDR, BASE_HELP_BUTTON_ADDR, false);
		WindowHook::InstallMoveWindowHook(VERSION);
	}
	else if (VERSION == 5165) {
		// Esta dando los mismos valores de lectura que v5187, no entiendo porque luego el resultado no es el mismo...
		const LPVOID BASE_W_ADDR = (LPVOID)(0x004D93CC + 6);
		const LPVOID BASE_H_ADDR = (LPVOID)(0x004D93D6 + 6);
		const LPVOID BASE_W2_ADDR = (LPVOID)(0x004D95F1 + 1);// new location pos=width
		const LPVOID BASE_H2_ADDR = (LPVOID)(0x004D9602 + 1);// new location pos=height
		const LPVOID BASE_PUZZLE_W_ADDR = (LPVOID)(0x004FEE88 + 1);
		const LPVOID BASE_PUZZLE_H_ADDR = (LPVOID)(0x004FEE9F + 1);
		const LPVOID BASE_PUZZLE_H2_ADDR = (LPVOID)(0x004FEEBF + 1);
		ChangeScreenSizes(BASE_W_ADDR, BASE_H_ADDR, BASE_W2_ADDR, BASE_H2_ADDR, BASE_PUZZLE_W_ADDR, BASE_PUZZLE_H_ADDR, BASE_PUZZLE_H2_ADDR, 0, 0, false);
		WindowHook::InstallMoveWindowHook(VERSION);
	}
}
