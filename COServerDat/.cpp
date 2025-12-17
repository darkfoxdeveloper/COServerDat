#include "MyMemoryEdit.h"
#include "CFlashFix.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include "ServerDatDetour.h"

int UsePattern = 0;

DWORD Encryption = Memory::FindPattern("", "xxxxxxxx");
DWORD CallAddress = Memory::FindPattern("", "xxxxxxxxxxxx");
DWORD WriteAddress = Memory::FindPattern("", "xx????xx????xx????xx");
CHAR * PathServer = "./Servers.dat";
CFlashFix flash;
__declspec (naked) VOID Asm_ServerDat() {
	__asm push PathServer
	__asm call CallAddress
	__asm nop
	__asm nop
}

//void InspectMemoryWithMessageBox(uintptr_t address, size_t bytesToRead) {
//	if (address == 0) {
//		MessageBoxA(NULL, "Dirección no válida.", "Error", MB_ICONERROR);
//		return;
//	}
//
//	// Leer la memoria desde la dirección encontrada
//	unsigned char* buffer = reinterpret_cast<unsigned char*>(address);
//
//	// Construir el contenido en un string para el MessageBox
//	std::ostringstream contentStream;
//	contentStream << "Contenido en la dirección 0x" << std::hex << address << ":\n\n";
//
//	for (size_t i = 0; i < bytesToRead; ++i) {
//		contentStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(buffer[i]) << " ";
//		if ((i + 1) % 16 == 0) contentStream << "\n"; // Salto de línea cada 16 bytes
//	}
//
//	// Convierte el contenido a cadena C para usar en MessageBoxA
//	std::string content = contentStream.str();
//	MessageBoxA(NULL, content.c_str(), "Contenido en Memoria", MB_ICONINFORMATION);
//}

VOID MyMemoryEdit::ServerData() {
	switch (UsePattern) {
		case 0: // V6022 TO V6175 (5827 - 6021 Error login but working Server.dat pattern)
			flash.Hook();
			Encryption = Memory::FindPattern("\x74\x1F\x6A\x02\x53\xFF\x75\xE0", "xxxxxxxx");
			CallAddress = Memory::FindPattern("\x8B\x44\x24\x08\x8B\x4C\x24\x04\x6A\xFF\x50\x51", "xxxxxxxxxxxx");
			WriteAddress = Memory::FindPattern("\xFF\x15\x00\x00\x00\x00\x50\xE8\x00\xFF\x50\x00\x8B\x3D\x00\x00\x00\x00\x8B\xD8", "xx????xx????xx????xx");
			break;
		case 1: // V6176 TO V6370 (V6187 not need flash fix)
			Encryption = Memory::FindPattern("\x74\x1F\x6A\x02\x53\xFF\x75\xD4", "xxxxxxxx");
			CallAddress = Memory::FindPattern("\x8B\x44\x24\x08\x8B\x4C\x24\x04\x6A\xFF\x50\x51", "xxxxxxxxxxxx");
			WriteAddress = Memory::FindPattern("\xFF\x15\x00\x00\x00\x00\x50\xE8\x00\xFF\x50\x00\x8B\x3D\x00\x00\x00\x00\x8B\xD8", "xx????xx????xx????xx");
			break;
		case 2: // V6371 TO V6736 (In this patch starting using Env_DX8 & Env_DX9 folder)
			Encryption = Memory::FindPattern("\x74\x1F\x6A\x02\x53\xFF\x75\xD4", "xxxxxxxx");
			CallAddress = Memory::FindPattern("\x8B\x44\x24\x08\x8B\x4C\x24\x04\x6A\xFF\x50\x51", "xxxxxxxxxxxx");
			WriteAddress = Memory::FindPattern("\xFF\x15\x00\x00\x00\x00\x50\xE8\x00\x00\x00\x00\x8B\x3D\x00\x00\x00\x00\x8B\xD8", "xx????xx????xx????xx");
			break;
	}

	ServerDatDetour::Init();
	//TEST 5695
	//InspectMemoryWithMessageBox(0x00A63C75, 64); // 6609 server.dat string xml
	/*Encryption = Memory::FindPattern("\x74\x1F\x6A\x02\x6A\x01\x8D\x45", "xxxxxxxx");
	CallAddress = Memory::FindPattern("\x8B\x44\x24\x08\x8B\x4C\x24\x04\x6A\xFF\x50\x51", "xxxxxxxxxxxx");
	WriteAddress = Memory::FindPattern("\xFF\x15\x00\x00\x00\x00\x50\xE8\x00\x92\x0B\x00\x8B\x3D\x00\x00\x00\x00\x8B\xD8", "xx????xx????xx????xx");*/

	//MessageBoxA(false, (LPCSTR)WriteAddress, "WriteAddress", 0);
	//InspectMemoryWithMessageBox(WriteAddress, 64);

	//BYTE Jmp[] = { 0xEB, 0x00 }; // Byte OF Skip Encryption
	//Memory::WriteMemory(Encryption, Jmp, sizeof(Jmp));
	//Memory::WriteMemory(WriteAddress, Asm_ServerDat, 12);
}