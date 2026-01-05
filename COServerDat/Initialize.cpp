#include "Initialize.h"
#include "ServerDatDetour.h"
#include "GUICalculator.h"

DWORD VersionClientGet(const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("Cannot open: " + path);

    std::string line;
    while (std::getline(f, line)) {
        size_t i = 0;
        while (i < line.size() && std::isspace(static_cast<unsigned char>(line[i]))) ++i;

        if (i < line.size() && line[i] == '#') {
            ++i;
            while (i < line.size() && std::isspace(static_cast<unsigned char>(line[i]))) ++i;
            unsigned long long v = 0;
            bool any = false;
            while (i < line.size() && std::isdigit(static_cast<unsigned char>(line[i]))) {
                any = true;
                v = v * 10 + (line[i] - '0');
                ++i;
            }
            if (!any)
                throw std::runtime_error("Not has server version.");
            if (v > 0xFFFFFFFFULL)
                throw std::runtime_error("Range value out DWORD.");
            return static_cast<DWORD>(v);
        }
    }

    throw std::runtime_error("No found version with '#'.");
}

VOID Initialize::Install() {
	DWORD version = VersionClientGet("version.dat");
    if (version == 5187) {
        GUICalculator::ChangeScreenSize();
    }
	ServerDatDetour::Init(version);
}