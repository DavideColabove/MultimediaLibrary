#pragma once
#include <string>

class Library;

namespace Persistence {
    
    bool save(const Library& library, const std::string& filePath);
    bool load(Library& library, const std::string& filePath);

    
    bool saveJson(const Library& library, const std::string& filePath);
    bool loadJson(Library& library, const std::string& filePath);
    bool saveXml(const Library& library, const std::string& filePath);
    bool loadXml(Library& library, const std::string& filePath);
}
