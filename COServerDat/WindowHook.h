#include <Windows.h>
#include "detours.h"

class WindowHook
{
public:
	static bool InstallMoveWindowHook(INT VERSION);
	static bool RemoveMoveWindowHook();
};