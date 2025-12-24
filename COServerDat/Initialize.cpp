#include "Initialize.h"
#include "ServerDatDetour.h"
#include "GUICalculator.h"

VOID Initialize::Install() {
	ServerDatDetour::Init();
	//GUICalculator::FullScreen();
	GUICalculator::ChangeScreenSize();
}