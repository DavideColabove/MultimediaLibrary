#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include <string>

class Library; // forward declaration

class JsonPersistence {
public:
    bool save(const Library& library, const std::string& filePath) const;
    bool load(Library& library, const std::string& filePath) const;
};

#endif 


