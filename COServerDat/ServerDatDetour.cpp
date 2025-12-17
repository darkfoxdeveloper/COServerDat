#include "Common.h"
#include "ServerDatDetour.h"

typedef char* (__cdecl* FuncTQServer)(char*, int);

DWORD FnSubA63C75 = 0x00A63C75;

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
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)FnSubA63C75, TQServer);
    DetourTransactionCommit();
}