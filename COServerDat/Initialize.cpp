#include "Initialize.h"
#include "ServerDatDetour.h"
#include "GUICalculator.h"
#include "Config.h"
#include "GuiPatcher.h"

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
    bool loaded = Config::Instance().Load("config.json");
    bool blockChanges = Config::Instance().AreScreenChangesDisabled();
    bool FHDMode = Config::Instance().IsFHDResolutionEnabled();

	DWORD VERSION = VersionClientGet("version.dat");

    if (!blockChanges) {
        // Specific replaces with matches from GUI.ini - Screen Resolution fix
        if (VERSION == 5187) {
            if (FHDMode) {
                auto res = GuiIniPatcher::Apply(true, true);
                GUICalculator::ChangeScreenSize(VERSION);
            }
            else {
                auto res = GuiIniPatcher::Revert(false, true);
            }
        }
    }
	ServerDatDetour::Init(VERSION);
}