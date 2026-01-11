#include "Common.h"
#include "WindowHook.h"

static BOOL(WINAPI* TrueMoveWindow)(
    HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint
    ) = MoveWindow;

const char CONFIG_FILE[]{ ".\\Settings.ini" };
int widthGUI = GetPrivateProfileIntA("GameResolution", "Width", 1024, CONFIG_FILE);
int heightGUI = GetPrivateProfileIntA("GameResolution", "Height", 768, CONFIG_FILE);
int ClientVersion = 0;


//static void Log(const std::string& msg)
//{
//    std::ofstream file("hook.log", std::ios::app);
//    if (!file.is_open())
//        return;
//
//    file << msg << std::endl;
//}

static bool IsTargetCall(HWND hWnd, int X, int Y, int W, int H, BOOL repaint)
{
    //Log("MoveWindow called: X=" + std::to_string(X) + " Y=" + std::to_string(Y) + " W=" + std::to_string(W) + " H=" + std::to_string(H));
    return ClientVersion == 5187 && H == 141;
}

static void ForceGameLayout(HWND hWnd)
{
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    RECT rc{};
    GetClientRect(hWnd, &rc);
    int cw = rc.right - rc.left;
    int ch = rc.bottom - rc.top;
    SendMessage(hWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(cw, ch));
    SendMessage(hWnd, WM_EXITSIZEMOVE, 0, 0);
    RedrawWindow(hWnd, nullptr, nullptr,
        RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}


static BOOL WINAPI HookMoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
    if (IsTargetCall(hWnd, X, Y, nWidth, nHeight, bRepaint))
    {
        X = (widthGUI - 1024) / 2;
        Y = heightGUI - 141;
        HWND root = GetAncestor(hWnd, GA_ROOT);
        if (root) hWnd = root;
        ForceGameLayout(hWnd);
        return TRUE;
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