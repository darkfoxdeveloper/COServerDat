#include <Windows.h>
#include "detours.h"

class WindowHook
{
public:
	static bool InstallMoveWindowHook();
	static bool RemoveMoveWindowHook();
};