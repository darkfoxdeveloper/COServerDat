#pragma once
#include "Common.h"

class GUICalculator
{
public:
	static VOID FullScreen();
public:
	static VOID ChangeScreenSize();
private:
	static VOID Calculator(INT Width, INT Height, BOOL IsFull);
};