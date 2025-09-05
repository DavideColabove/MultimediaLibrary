#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include <string>

class Library;

class IPersistence {
public:

    virtual ~IPersistence() = default;

    virtual bool save(const Library& library, const std::string& filePath) const = 0;

    virtual bool load(Library& library, const std::string& filePath) const = 0;
};

#endif 


