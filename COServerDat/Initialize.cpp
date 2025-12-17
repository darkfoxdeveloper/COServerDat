#include "Initialize.h"
#include "ServerDatDetour.h"

VOID Initialize::Install() {
	ServerDatDetour::Init();
}