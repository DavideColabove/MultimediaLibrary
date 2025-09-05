#include "Persistence.h"
#include "JsonPersistence.h"
#include "XmlPersistence.h"
#include "../Library/Library.h"
#include <algorithm>

namespace Persistence {
    static inline bool endsWith(const std::string& s, const char* suf) {
        const size_t n = std::char_traits<char>::length(suf);
        return s.size() >= n && std::equal(s.end()-n, s.end(), suf,
            [](char a, char b){ return std::tolower(a)==std::tolower(b); });
    }

    bool saveJson(const Library& library, const std::string& filePath) {
        JsonPersistence p; return p.save(library, filePath);
    }
    bool loadJson(Library& library, const std::string& filePath) {
        JsonPersistence p; return p.load(library, filePath);
    }
    bool saveXml(const Library& library, const std::string& filePath) {
        XmlPersistence p; return p.save(library, filePath);
    }
    bool loadXml(Library& library, const std::string& filePath) {
        XmlPersistence p; return p.load(library, filePath);
    }

    bool save(const Library& library, const std::string& filePath) {
        if (endsWith(filePath, ".json")) return saveJson(library, filePath);
        if (endsWith(filePath, ".xml")) return saveXml(library, filePath);
        return false;
    }
    bool load(Library& library, const std::string& filePath) {
        if (endsWith(filePath, ".json")) return loadJson(library, filePath);
        if (endsWith(filePath, ".xml")) return loadXml(library, filePath);
        return false;
    }
}
