#include "Common.h"
#include "ServerDatDetour.h"
#include "Memory.h"
typedef signed char* (__cdecl* FuncTQServer)(char*, int);
DWORD GetVersionFromClient(const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("Cannot open: " + path);

    std::string line;
    while (std::getline(f, line)) {
        size_t i = 0;
        while (i < line.size() && std::isspace(static_cast<unsigned char>(line[i]))) ++i;

        if (i < line.size() && line[i] == '#') {
            ++i;
            while (i < line.size() && std::isspace(static_cast<unsigned char>(line[i]))) ++i;
            unsigned long long v = 0;
            bool any = false;
            while (i < line.size() && std::isdigit(static_cast<unsigned char>(line[i]))) {
                any = true;
                v = v * 10 + (line[i] - '0');
                ++i;
            }
            if (!any)
                throw std::runtime_error("Not has server version.");
            if (v > 0xFFFFFFFFULL)
                throw std::runtime_error("Range value out DWORD.");
            return static_cast<DWORD>(v);
        }
    }

    throw std::runtime_error("No found version with '#'.");
}
DWORD GetServerBufferAddress()
{
    DWORD ServerDatAddr = 0;
    DWORD version = GetVersionFromClient("version.dat");
    if (version >= 5517 && version < 6270) {
        ServerDatAddr = 0x772601; // 5517-6270
    }
    else if (version >= 6270) {
        ServerDatAddr = Memory::FindPattern("\xCC\x8B\x74\x24\x08\x85\xF6\x74\x62", "?xxxxxxxx"); // 6270+
    }
    return ServerDatAddr;
}

DWORD Server_ADDRESS = GetServerBufferAddress();
//DWORD Server_ADDRESS = Memory::FindPattern("\xCC\x8B\x74\x24\x08\x85\xF6\x74\x62", "?xxxxxxxx"); // ENV_DX9 = 0x00A63C75  | ENV_DX8 = 0x00A653F2 (Working 6609, 6270)
//DWORD Server_ADDRESS = 0x772601; // 5517
int hookdat = 0;
typedef signed char* (__cdecl* ServerHOOK)(char* a1, int a2);
signed char* __cdecl SERVER_HOOK(char* a1, int a2)
{
    hookdat++;
    if (hookdat == 4)
    {
        FILE* pFile;
        pFile = fopen("COServer.dat", "rb");
        if (pFile != NULL)
        {
            char currentline[10000];
            assert(pFile != NULL);
            char bufferServerDat[10000];
            int i = 0;
            while (fgets(currentline, sizeof(currentline), pFile) != NULL)
            {
                if (i == 0)
                {
                    strcpy(bufferServerDat, currentline);
                    i++;
                }
                else
                    strcat(bufferServerDat, currentline);
            }
            strcpy(a1, bufferServerDat);
            fclose(pFile);
        }
    }
    ServerHOOK originalIQ = (ServerHOOK)Server_ADDRESS;
    return originalIQ(a1, a2);
}
void ServerDatDetour::Init()
{
    // Find address by pattern
    /*char buffer[32];
    sprintf(buffer, "0x%08X", FnSubA63C75);
    MessageBoxA(nullptr, buffer, "Injected, MEMORYADDRESS", MB_OK);*/
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