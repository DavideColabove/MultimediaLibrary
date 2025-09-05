#ifndef XMLPERSISTENCE_H
#define XMLPERSISTENCE_H

#include "IPersistence.h"


class XmlPersistence : public IPersistence {
public:

    bool save(const Library& library, const std::string& filePath) const override;

    bool load(Library& library, const std::string& filePath) const override;
};

#endif 


