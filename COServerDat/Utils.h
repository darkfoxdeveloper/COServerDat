#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <climits>

namespace IniUtils
{
    inline std::vector<std::string> GetSectionNames(const char* iniPath)
    {
        std::vector<char> buffer(64 * 1024, '\0');

        DWORD chars = GetPrivateProfileSectionNamesA(
            buffer.data(),
            static_cast<DWORD>(buffer.size()),
            iniPath
        );

        if (chars == 0)
            return {};

        std::vector<std::string> sections;
        const char* p = buffer.data();

        while (*p)
        {
            sections.emplace_back(p);
            p += sections.back().size() + 1;
        }

        return sections;
    }

    inline std::vector<std::string> FindSectionsByRect(
        const char* iniPath,
        int x, int y, int w, int h,
        int defaultMissing = INT_MIN
    )
    {
        std::vector<std::string> matches;
        auto sections = GetSectionNames(iniPath);

        for (const auto& sec : sections)
        {
            int sx = GetPrivateProfileIntA(sec.c_str(), "x", defaultMissing, iniPath);
            int sy = GetPrivateProfileIntA(sec.c_str(), "y", defaultMissing, iniPath);
            int sw = GetPrivateProfileIntA(sec.c_str(), "w", defaultMissing, iniPath);
            int sh = GetPrivateProfileIntA(sec.c_str(), "h", defaultMissing, iniPath);

            if (sx == defaultMissing || sy == defaultMissing ||
                sw == defaultMissing || sh == defaultMissing)
                continue;

            if (sx == x && sy == y && sw == w && sh == h)
                matches.push_back(sec);
        }

        return matches;
    }
}
