#include "Common.h"
#include "Initialize.h"

//Dll Export To Allow IAT Loading
__declspec(dllexport) INT Initialize() { return NULL; }

BOOL WINAPI DllMain(HINSTANCE HInstance, DWORD DwReason, LPVOID lPReserved) {
	if (DwReason == DLL_PROCESS_ATTACH) {
		Initialize::Install();
		DisableThreadLibraryCalls(HInstance);
	}
	else if (DwReason == DLL_PROCESS_DETACH) {
		FreeLibraryAndExitThread(HInstance, NULL);
	}
	return TRUE;
}