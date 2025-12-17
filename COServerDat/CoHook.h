#pragma once
#include "stdio.h"
#include "Common.h"
#include "shellapi.h"
#include "MyMemoryEdit.h"

class CoHook
{
public:
	static VOID MemoryWrite();
};