#include "Common.h"
#include "WindowHook.h"

static BOOL(WINAPI* TrueMoveWindow)(
    HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint
    ) = MoveWindow;

const char CONFIG_FILE[]{ ".\\Settings.ini" };
int widthGUI = GetPrivateProfileIntA("GameResolution", "Width", 1024, CONFIG_FILE);
int heightGUI = GetPrivateProfileIntA("GameResolution", "Height", 768, CONFIG_FILE);
int ClientVersion = 0;

static void Log(const std::string& msg)
{
    std::ofstream file("hook.log", std::ios::app);
    if (!file.is_open())
        return;

    file << msg << std::endl;
}

static bool IsTargetCall(HWND hWnd, int X, int Y, int W, int H, BOOL repaint)
{
    Log("MoveWindow called: X=" + std::to_string(X) + " Y=" + std::to_string(Y) + " W=" + std::to_string(W) + " H=" + std::to_string(H));
    if (ClientVersion == 5165) {
        if (X == 0 && W == 1024 && H == 768) {
            return true;
        }
    }
    if (ClientVersion == 5187) {
        if (H == 141) {
            return true;
        }
    }
    return false;
}


static BOOL WINAPI HookMoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
    if (IsTargetCall(hWnd, X, Y, nWidth, nHeight, bRepaint))
    {
        nWidth = widthGUI;
        nHeight = heightGUI;
        //X = (widthGUI - 1024) / 2;
        //Y = heightGUI - 141;
    }

    return TrueMoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

bool WindowHook::InstallMoveWindowHook(INT VERSION)
{
    ClientVersion = VERSION;
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    DetourAttach(&(PVOID&)TrueMoveWindow, HookMoveWindow);

    LONG err = DetourTransactionCommit();
    if (err != NO_ERROR) {
        char buf[128];
        wsprintfA(buf, "DetourTransactionCommit error: %ld", err);
        MessageBoxA(nullptr, buf, "Detours", MB_OK);
        return false;
    }
    return true;
}

bool WindowHook::RemoveMoveWindowHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)TrueMoveWindow, HookMoveWindow);
    return DetourTransactionCommit() == NO_ERROR;
}