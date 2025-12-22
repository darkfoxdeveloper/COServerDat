#include "Initialize.h"

//Dll Export To Allow IAT Loading
__declspec(dllexport) INT Initialize() { return NULL; }

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
        CreateThread(nullptr, 0, [](LPVOID)->DWORD {
            Initialize::Install();
            return 0;
            }, nullptr, 0, nullptr);
    }
    return TRUE;
}