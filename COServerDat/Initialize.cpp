#include "Initialize.h"
#include "ServerDatDetour.h"
#include "GUICalculator.h"
#include "Config.h"

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
	DWORD VERSION = VersionClientGet("version.dat");

    int  width = Config::Instance().GetWidth();
    int  height = Config::Instance().GetHeight();
    bool fullscreen = Config::Instance().IsFullscreenEnabled();
    std::string msg =
        loaded ? "Config loaded\n\n" : "Config not found, defaults used\n\n";

    msg +=
        "Resolution: " + std::to_string(width) + "x" + std::to_string(height) + "\n" +
        "Fullscreen: " + std::string(fullscreen ? "true" : "false") + "\n" +
        "Screen changes disabled: " + std::string(blockChanges ? "true" : "false");

    MessageBoxA(nullptr, msg.c_str(), "Shared Config Test", MB_OK);

    if (!blockChanges) {
        GUICalculator::ChangeScreenSize(VERSION);
    }
	ServerDatDetour::Init(VERSION);
}