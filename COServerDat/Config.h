#pragma once
#include <string>

class Config
{
public:
    static Config& Instance();

    // Reads shared JSON config if present, ignores missing file
    bool Load(const std::string& filePath = "config.json");

    // Read-only access
    bool IsHighResolutionEnabled() const;
    bool IsFullscreenEnabled() const;
    bool AreScreenChangesDisabled() const;

    int  GetWidth() const;
    int  GetHeight() const;

    // No copy
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

private:
    Config() = default;

private:
    // Defaults (safe)
    bool m_highResolution = false;
    bool m_fullscreen = false;
    bool m_disableScreenChanges = false;
};
