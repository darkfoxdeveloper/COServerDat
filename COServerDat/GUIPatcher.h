#pragma once
#include <string>
#include <vector>

namespace GuiIniPatcher
{
    enum class Mode
    {
        Normal,   // old -> new
        Inverse   // new -> old
    };

    struct Result
    {
        int applied = 0;
        int examined = 0;
        std::vector<std::string> log; // only filled if keepLog=true
    };

    // Patches ".\\ini\\GUI.ini" using the internal update table.
    Result Patch(Mode mode, bool createBackup = true, bool keepLog = false);

    inline Result Apply(bool createBackup = true, bool keepLog = false)
    {
        return Patch(Mode::Normal, createBackup, keepLog);
    }

    inline Result Revert(bool createBackup = true, bool keepLog = false)
    {
        return Patch(Mode::Inverse, createBackup, keepLog);
    }
}