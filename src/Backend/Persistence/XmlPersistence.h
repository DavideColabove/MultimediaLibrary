#ifndef XMLPERSISTENCE_H
#define XMLPERSISTENCE_H

#include "IPersistence.h"

/**
 * @brief XML format persistence implementation
 * 
 * This class implements the IPersistence interface to provide XML format
 * data persistence for the library system. It serializes and deserializes
 * media objects to/from XML format, providing a structured and extensible
 * data format for library storage and interoperability with other systems.
 * 
 * The implementation includes:
 * - Custom XML parsing without external dependencies
 * - Proper XML escaping and formatting
 * - Support for all media types and their specific attributes
 * - Robust error handling for malformed XML data
 */
class XmlPersistence : public IPersistence {
public:
    /**
     * @brief Saves library data to an XML file
     * @param library The library object to save
     * @param filePath The output XML file path
     * @return true if save successful, false otherwise
     */
    bool save(const Library& library, const std::string& filePath) const override;
    
    /**
     * @brief Loads library data from an XML file
     * @param library The library object to populate
     * @param filePath The input XML file path
     * @return true if load successful, false otherwise
     */
    bool load(Library& library, const std::string& filePath) const override;
};

#endif // XMLPERSISTENCE_H


