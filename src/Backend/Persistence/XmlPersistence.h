#ifndef XMLPERSISTENCE_H
#define XMLPERSISTENCE_H

#include <string>

class Library; // forward declaration

class XmlPersistence {
public:
    bool save(const Library& library, const std::string& filePath) const;
    bool load(Library& library, const std::string& filePath) const;
};

#endif 


