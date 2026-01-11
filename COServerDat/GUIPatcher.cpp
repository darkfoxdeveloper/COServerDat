#include "GuiPatcher.h"
#include <windows.h>
#include <string>
#include <unordered_map>
#include <cctype>

namespace
{
    const char* const kGuiIniPath = ".\\ini\\GUI.ini";
    const char* const kBackupPath = ".\\ini\\GUI.ini.bak";

    struct ci_hash {
        size_t operator()(const std::string& s) const {
            size_t h = 1469598103934665603ull;
            for (size_t i = 0; i < s.size(); ++i) {
                unsigned char c = (unsigned char)std::tolower((unsigned char)s[i]);
                h ^= (size_t)c;
                h *= 1099511628211ull;
            }
            return h;
        }
    };

    struct ci_equal {
        bool operator()(const std::string& a, const std::string& b) const {
            if (a.size() != b.size()) return false;
            for (size_t i = 0; i < a.size(); ++i) {
                unsigned char ca = (unsigned char)std::tolower((unsigned char)a[i]);
                unsigned char cb = (unsigned char)std::tolower((unsigned char)b[i]);
                if (ca != cb) return false;
            }
            return true;
        }
    };

    struct Update { int oldVal; int newVal; };

    typedef std::unordered_map<std::string, Update, ci_hash, ci_equal> KeyUpdates;
    typedef std::unordered_map<std::string, KeyUpdates, ci_hash, ci_equal> UpdatesMap;

    static const UpdatesMap g_updates = {
        { "0-3",    KeyUpdates{ { "x", {610, 1060} }, { "y", {650, 965} } } },
        { "0-130",  KeyUpdates{ { "x", {0, 448} },    { "y", {627, 939} } } },
        { "0-138",  KeyUpdates{ { "x", {327, 775} },  { "y", {237, 365} } } },
        { "0-140",  KeyUpdates{ { "x", {574, 880} },  { "y", {550, 855} } } },
        { "0-141",  KeyUpdates{ { "x", {380, 815} } } },
        { "0-145",  KeyUpdates{ { "x", {82, 530} },   { "y", {697, 1009} } } },
        { "0-148",  KeyUpdates{ { "x", {117, 565} },  { "y", {404, 715} } } },
        { "0-158",  KeyUpdates{ { "x", {365, 816} },  { "y", {300, 480} } } },
        { "0-174",  KeyUpdates{ { "x", {254, 702} },  { "y", {452, 755} } } },
        { "0-191",  KeyUpdates{ { "x", {734, 1030} }, { "y", {670, 980} } } },
        { "0-268",  KeyUpdates{ { "x", {499, 931} } } },
        { "0-274",  KeyUpdates{ { "x", {574, 880} },  { "y", {550, 865} } } },
        { "0-289",  KeyUpdates{ { "x", {132, 580} },  { "y", {653, 965} } } },
        { "0-303",  KeyUpdates{ { "x", {1000, 1390} } } },
        { "0-304",  KeyUpdates{ { "x", {935, 1810} } } },
        { "0-325",  KeyUpdates{ { "x", {165, 615} },  { "y", {639, 950} } } },
        { "0-328",  KeyUpdates{ { "x", {223, 675} },  { "y", {654, 970} } } },
        { "0-339",  KeyUpdates{ { "x", {276, 732} },  { "y", {650, 965} } } },
        { "0-357",  KeyUpdates{ { "y", {315, 628} } } },
        { "0-360",  KeyUpdates{ { "x", {574, 880} },  { "y", {550, 865} } } },
        { "0-367",  KeyUpdates{ { "x", {574, 880} },  { "y", {520, 835} } } },
        { "0-371",  KeyUpdates{ { "x", {680, 1130} }, { "y", {615, 940} } } },
        { "0-403",  KeyUpdates{ { "x", {325, 780} },  { "y", {650, 965} } } },
        { "0-1198", KeyUpdates{ { "y", {283, 603} } } },
        { "0-1199", KeyUpdates{ { "x", {984, 1880} } } },
        { "0-1200", KeyUpdates{ { "x", {1004, 1900} } } },
    };

    static bool ReadIniString(const char* iniPath,
        const std::string& section,
        const std::string& key,
        std::string& outValue)
    {
        const char* sentinel = "__MISSING__";
        char buf[256] = { 0 };

        DWORD n = GetPrivateProfileStringA(
            section.c_str(),
            key.c_str(),
            sentinel,
            buf,
            (DWORD)sizeof(buf),
            iniPath
        );

        if (n == 0) return false;
        if (std::string(buf) == sentinel) return false;

        outValue.assign(buf);
        return true;
    }

    static bool WriteIniString(const char* iniPath,
        const std::string& section,
        const std::string& key,
        const std::string& value)
    {
        return WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), iniPath) != 0;
    }

    static bool BackupIniIfRequested(bool createBackup)
    {
        if (!createBackup)
            return true;

        DWORD attrs = GetFileAttributesA(kGuiIniPath);
        if (attrs == INVALID_FILE_ATTRIBUTES)
            return false; // GUI.ini not found

        return CopyFileA(kGuiIniPath, kBackupPath, FALSE) != 0;
    }
}

namespace GuiIniPatcher
{
    Result Patch(Mode mode, bool createBackup, bool keepLog)
    {
        Result result;

        if (!BackupIniIfRequested(createBackup))
        {
            if (keepLog)
                result.log.push_back("Backup failed or GUI.ini not found.");
            return result;
        }

        for (UpdatesMap::const_iterator itSec = g_updates.begin(); itSec != g_updates.end(); ++itSec)
        {
            const std::string& section = itSec->first;
            const KeyUpdates& keyUpdates = itSec->second;

            for (KeyUpdates::const_iterator itKey = keyUpdates.begin(); itKey != keyUpdates.end(); ++itKey)
            {
                const std::string& key = itKey->first;
                const Update& upd = itKey->second;

                ++result.examined;

                const int expectedInt = (mode == Mode::Normal) ? upd.oldVal : upd.newVal;
                const int replacementInt = (mode == Mode::Normal) ? upd.newVal : upd.oldVal;

                const std::string expected = std::to_string(expectedInt);
                const std::string replacement = std::to_string(replacementInt);

                std::string current;
                if (!ReadIniString(kGuiIniPath, section, key, current))
                    continue;

                if (current == expected)
                {
                    if (WriteIniString(kGuiIniPath, section, key, replacement))
                    {
                        ++result.applied;
                        if (keepLog)
                            result.log.push_back("[" + section + "] " + key + ": " + current + " -> " + replacement);
                    }
                    else
                    {
                        if (keepLog)
                            result.log.push_back("[" + section + "] " + key + ": FAILED to write");
                    }
                }
            }
        }

        return result;
    }
}