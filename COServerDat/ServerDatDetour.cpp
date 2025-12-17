#include "Common.h"
#include "ServerDatDetour.h"
#include "Memory.h"

typedef char* (__cdecl* FuncTQServer)(char*, int);

DWORD FnSubA63C75 = Memory::FindPattern("\xCC\x8B\x74\x24\x08\x85\xF6\x74\x62", "?xxxxxxxx"); // ENV_DX9 = 0x00A63C75  | ENV_DX8 = 0x00A653F2

static std::string LoadFileToString(const char* path)
{
    std::ifstream f(path, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

INT Count = 0;
char* __cdecl TQServer(char* data1, int data2)
{
    FuncTQServer TQ = (FuncTQServer)FnSubA63C75;

    Count++;

    if (std::strstr(data1, "<?xml version=") == nullptr)
    {
        return TQ(data1, data2);
    }

    if (Count != 4)
    {
        return TQ(data1, data2);
    }

    static std::string xml = LoadFileToString("COServer.dat");
    strncpy_s(data1, _TRUNCATE, xml.c_str(), xml.size());
    return TQ(data1, data2);
}

void ServerDatDetour::Init()
{
    // Test find by pattern
    /*char buffer[32];
    DWORD CallAddress = Memory::FindPattern(
        "\xCC\x8B\x74\x24\x08\x85\xF6\x74\x62",
        "?xxxxxxxx"
    );
    sprintf(buffer, "0x%08X", CallAddress);
    MessageBoxA(nullptr, buffer, "DWORD value", MB_OK);*/

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)FnSubA63C75, TQServer);
    DetourTransactionCommit();
}