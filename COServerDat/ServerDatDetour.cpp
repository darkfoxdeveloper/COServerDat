#include "Common.h"
#include "ServerDatDetour.h"
#include "Memory.h"
typedef signed char* (__cdecl* FuncTQServer)(char*, int);
DWORD GetServerBufferAddress(DWORD version)
{
    DWORD ServerDatAddr = 0;
    DWORD FPSAddr = 0;
    unsigned char NEWFPS[1] = { 0xEB }; // JMP FPS
	// IMPORTANT INFO ABOUT VERSIONS:
    // V6022 TO V6175 (5827 - 6021 Error login but working Server.dat pattern)
    // V6176 TO V6370 (V6187 not need flash fix)
    // V6371 TO V6736 (In this patch starting using Env_DX8 & Env_DX9 folder)
    // Pattern ranges: 5095-5589 | 5590-6099 | 6100-6711
    if (version >= 5095 && version <= 5589) {
        ServerDatAddr = Memory::FindPattern("\x56\x8B\x74\x24\x08\x85\xF6\x0F\x84", "xxxxxxxxx"); // 0x772601 - V5517
    }
    else if (version >= 5590 && version <= 6099) {
        ServerDatAddr = Memory::FindPattern("\x56\x8B\x74\x24\x08\x85\xF6\x74\x77\x8A\x06\x84\xC0", "xxxxxxxxxxxxx"); // 0x81E8AC - V5695
    }
    else if (version >= 6100 && version <= 6711) {
        ServerDatAddr = Memory::FindPattern("\xCC\x8B\x74\x24\x08\x85\xF6\x74\x62", "?xxxxxxxx"); // ENV_DX9 = 0x00A63C75  | ENV_DX8 = 0x00A653F2 (Working 6609, 6270)
    }
    FPSAddr = Memory::FindPattern("\x73\x0E\x2B\xC8\x83\xC1\x19", "x?xx??");
    if (FPSAddr > 0) {
        Memory::WriteMemory(FPSAddr, NEWFPS, 1);
    }
    return ServerDatAddr;
}
DWORD Server_ADDRESS;
int hookdat = 0;
bool ServerDatChanged = false;
typedef signed char* (__cdecl* ServerHOOK)(char* a1, int a2);
signed char* __cdecl SERVER_HOOK(char* a1, int a2)
{
    ServerHOOK originalTQ = (ServerHOOK)Server_ADDRESS;
    hookdat++;
    if (hookdat == 4 && !ServerDatChanged)
    {
        FILE* pFile;
        pFile = fopen("COServer.dat", "rb");
        if (pFile != NULL)
        {
            std::string bufferServerDat;
            char currentline[1024];
            while (fgets(currentline, sizeof(currentline), pFile) != NULL)
            {
                bufferServerDat += currentline;
            }
            strcpy(a1, bufferServerDat.c_str());
            fclose(pFile);
            ServerDatChanged = true;
            return originalTQ(a1, a2);
        }
        else {
            MessageBoxA(0, "Cannot load COServer.dat", "Error loading COServer.dat", MB_OK);
        }
    }
    return originalTQ(a1, a2);
}
void ServerDatDetour::Init(DWORD version)
{
    Server_ADDRESS = GetServerBufferAddress(version);
    bool debugInfo = false;
    if (debugInfo) {
        std::string versionStr = std::to_string(version);
        // Show debug address by pattern
        char buffer[32];
        sprintf(buffer, "0x%08X", Server_ADDRESS);
        MessageBoxA(nullptr, versionStr.c_str(), buffer, MB_OK);
    }
    if (Server_ADDRESS == 0) {
        MessageBoxA(0, "No compatible version with COServerDat", "OK", MB_OK);
        exit(0);
    }
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)Server_ADDRESS, SERVER_HOOK);
    if (DetourTransactionCommit() != NO_ERROR)
    {
        MessageBoxA(0, "SERVER_HOOK Not Found", "OK", MB_OK);
        exit(0);
    }
    return;
}