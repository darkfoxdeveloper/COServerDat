#include "GUICalculator.h"
#include "Memory.h"
#include "WindowHook.h"

const char CONFIG_FILE[]{ ".\\Settings.ini" };
int width = GetPrivateProfileIntA("GameResolution", "Width", 1024, CONFIG_FILE);
int height = GetPrivateProfileIntA("GameResolution", "Height", 768, CONFIG_FILE);
std::string msg = "";

VOID ChangeScreenByAddresses(LPVOID BASE_W_ADDR, LPVOID BASE_H_ADDR, LPVOID BASE_W2_ADDR, LPVOID BASE_H2_ADDR, LPVOID BASE_PUZZLE_W_ADDR, LPVOID BASE_PUZZLE_H_ADDR, LPVOID BASE_PUZZLE_H2_ADDR, LPVOID BASE_MAIN_UI0_ADDR, LPVOID BASE_MAIN_UI1_ADDR, LPVOID BASE_ARROW_ADDR, LPVOID BASE_HELP_BUTTON_ADDR) {
	HANDLE hProcess = GetCurrentProcess();
	DWORD dwProc = (DWORD)hProcess;
	int read = 0;
	SIZE_T bytes_read = 0, bytes_written = 0;
	if (ReadProcessMemory(hProcess, BASE_W_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
		if (bytes_read == 0)
			MessageBoxA(NULL, "Could not get width memory offset. 1", "ReadProcessMemory error", MB_OK);

		if (!WriteProcessMemory(hProcess, BASE_W_ADDR, &width, 4, &bytes_written)) {
			/*sprintf_s(msg, "Error writing to memory! 1 %d", GetLastError());
			MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
		}
	}

	if (ReadProcessMemory(hProcess, BASE_H_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
		if (bytes_read == 0)
			MessageBoxA(NULL, "Could not get height memory offset. 2", "ReadProcessMemory error", MB_OK);

		if (!WriteProcessMemory(hProcess, BASE_H_ADDR, &height, 4, &bytes_written)) {
			/*	sprintf_s(msg, "Error writing to memory! 2 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
		}
	}

	if (BASE_W2_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_W2_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get width memory offset. 1", "ReadProcessMemory error", MB_OK);

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

			if (!WriteProcessMemory(hProcess, BASE_H2_ADDR, &height, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 2 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (ReadProcessMemory(hProcess, BASE_PUZZLE_W_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
		if (bytes_read == 0)
			MessageBoxA(NULL, "Could not get width memory offset. 3", "ReadProcessMemory error", MB_OK);

		if (!WriteProcessMemory(hProcess, BASE_PUZZLE_W_ADDR, &width, 4, &bytes_written)) {
			/*	sprintf_s(msg, "Error writing to memory! 3 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
		}
	}

	if (ReadProcessMemory(hProcess, BASE_PUZZLE_H_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
		if (bytes_read == 0)
			MessageBoxA(NULL, "Could not get height memory offset. 4", "ReadProcessMemory error", MB_OK);

		if (!WriteProcessMemory(hProcess, BASE_PUZZLE_H_ADDR, &height, 4, &bytes_written)) {
			/*	sprintf_s(msg, "Error writing to memory! 4 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
		}
	}

	if (ReadProcessMemory(hProcess, BASE_PUZZLE_H2_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
		if (bytes_read == 0)
			MessageBoxA(NULL, "Could not get height memory offset. 4", "ReadProcessMemory error", MB_OK);

		if (!WriteProcessMemory(hProcess, BASE_PUZZLE_H2_ADDR, &height, 4, &bytes_written)) {
			/*sprintf_s(msg, "Error writing to memory! 4 %d", GetLastError());
			MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
		}
	}

	//if (ReadProcessMemory(hProcess, BASE_MAIN_UI0_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
	//	if (bytes_read == 0)
	//		MessageBoxA(NULL, "Could not get height memory offset. 6", "ReadProcessMemory error", MB_OK);

	//	//sprintf_s(msg, "Old UI POS X Value: %d", read);
	//	//MessageBoxA(NULL, msg, "Main UI", MB_OK);

	//	int position = height - 141;
	//	if (!WriteProcessMemory(hProcess, BASE_MAIN_UI0_ADDR, &position, 4, &bytes_written)) {
	//		/*	sprintf_s(msg, "Error writing to memory! 6 %d", GetLastError());
	//			MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
	//	}
	//}

	//if (ReadProcessMemory(hProcess, BASE_MAIN_UI1_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
	//	if (bytes_read == 0)
	//		MessageBoxA(NULL, "Could not get height memory offset. 5", "ReadProcessMemory error", MB_OK);

	//	//sprintf_s(msg, "Old UI POS X Value: %d", read);
	//	//MessageBoxA(NULL, msg, "Main UI", MB_OK);

	//	int position = (width - 1024) / 2;
	//	if (!WriteProcessMemory(hProcess, BASE_MAIN_UI1_ADDR, &position, 4, &bytes_written)) {
	//		/*sprintf_s(msg, "Error writing to memory! 5 %d", GetLastError());
	//		MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
	//	}
	//}

	if (BASE_ARROW_ADDR > 0) {
		if (ReadProcessMemory(hProcess, BASE_ARROW_ADDR, &read, 4, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
			if (bytes_read == 0)
				MessageBoxA(NULL, "Could not get height memory offset. 6", "ReadProcessMemory error", MB_OK);

			int position = ((width - 1024) / 2) + 131;
			if (!WriteProcessMemory(hProcess, BASE_ARROW_ADDR, &position, 4, &bytes_written)) {
				/*sprintf_s(msg, "Error writing to memory! 6 %d", GetLastError());
				MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
			}
		}
	}

	if (ReadProcessMemory(hProcess, BASE_HELP_BUTTON_ADDR, &read, 1, &bytes_read) || GetLastError() == ERROR_PARTIAL_COPY) {
		if (bytes_read == 0)
			MessageBoxA(NULL, "Could not get height memory offset. 9", "ReadProcessMemory error", MB_OK);

		int position = -30;
		if (!WriteProcessMemory(hProcess, BASE_HELP_BUTTON_ADDR, &position, 1, &bytes_written)) {
			/*sprintf_s(msg, "Error writing to memory! 9 %d", GetLastError());
			MessageBoxA(NULL, msg, "WriteProcessMemory error", MB_OK);*/
		}
	}
}

VOID GUICalculator::ChangeScreenSize(DWORD VERSION) {
	bool ApplyScreenChanges = VERSION == 5187;// VERSION = 5103 || VERSION == 5078 || VERSION == 5165 || VERSION == 5187;
	if (ApplyScreenChanges) {
		const LPVOID BASE_W_ADDR = (LPVOID)(0x004EB22F + 6);
		const LPVOID BASE_H_ADDR = (LPVOID)(0x004EB239 + 6);
		const LPVOID BASE_W2_ADDR = (LPVOID)(0x004ED815 + 6);// new location pos=width
		const LPVOID BASE_H2_ADDR = (LPVOID)(0x004ED81F + 6);// new location pos=height
		const LPVOID BASE_PUZZLE_W_ADDR = (LPVOID)(0x00539C34 + 1);
		const LPVOID BASE_PUZZLE_H_ADDR = (LPVOID)(0x00539C4B + 1);
		const LPVOID BASE_PUZZLE_H2_ADDR = (LPVOID)(0x00539C6B + 1);
		const LPVOID BASE_MAIN_UI0_ADDR = (LPVOID)(0x004F7B8A + 1);
		const LPVOID BASE_MAIN_UI1_ADDR = (LPVOID)(0x004F7B8F + 1);
		const LPVOID BASE_ARROW_ADDR = (LPVOID)(0x00553B2D + 3); // int position = ((width - 1024) / 2) + 131;
		const LPVOID BASE_HELP_BUTTON_ADDR = (LPVOID)(0x0045649C + 1);
		ChangeScreenByAddresses(BASE_W_ADDR, BASE_H_ADDR, BASE_W2_ADDR, BASE_H2_ADDR, BASE_PUZZLE_W_ADDR, BASE_PUZZLE_H_ADDR, BASE_PUZZLE_H2_ADDR, BASE_MAIN_UI0_ADDR, BASE_MAIN_UI1_ADDR, BASE_ARROW_ADDR, BASE_HELP_BUTTON_ADDR);
		WindowHook::InstallMoveWindowHook();
		// El resultado es ligeramente diferente pero quizas adaptando la GUI de otra forma ya lo tenemos,
		//falta probar mas, asi usaria el Conquer.exe nativo y solo seria hacer estos cambios de memoria sin afectar al exe
	}
}
