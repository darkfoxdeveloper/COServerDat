#include "Config.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config& Config::Instance()
{
    static Config instance;
    return instance;
}

bool Config::Load(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return false;

    json root;
    try
    {
        file >> root;
    }
    catch (...)
    {
        return false;
    }

    if (!root.is_object())
        return false;

    m_highResolution =
        root.value("HighResolution", m_highResolution);

    m_FHDResolution =
        root.value("FHDResolution", m_FHDResolution);

    m_fullscreen =
        root.value("FullScreen", m_fullscreen);

    m_disableScreenChanges =
        root.value("DisableScreenChanges", m_disableScreenChanges);

    return true;
}

bool Config::IsHighResolutionEnabled() const
{
    return m_highResolution;
}

bool Config::IsFHDResolutionEnabled() const
{
    return m_FHDResolution;
}

bool Config::IsFullscreenEnabled() const
{
    return m_fullscreen;
}

bool Config::AreScreenChangesDisabled() const
{
    return m_disableScreenChanges;
}

int Config::GetWidth() const
{
    return m_FHDResolution ? 1920 : 1024;
}

int Config::GetHeight() const
{
    return m_FHDResolution ? 1080 : 768;
}
