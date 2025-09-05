#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include "IPersistence.h"


class JsonPersistence : public IPersistence {
public:

    bool save(const Library& library, const std::string& filePath) const override;

    bool load(Library& library, const std::string& filePath) const override;
};

#endif 


