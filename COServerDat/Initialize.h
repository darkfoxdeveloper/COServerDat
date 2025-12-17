#pragma once
#include "Common.h"
#include "Memory.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "user32.lib")

class Initialize
{
public:
	static VOID Install();
};