#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include "IPersistence.h"

/**
 * @brief JSON format persistence implementation
 * 
 * This class implements the IPersistence interface to provide JSON format
 * data persistence for the library system. It serializes and deserializes
 * media objects to/from JSON format, providing a human-readable and
 * widely-supported data format for library storage and exchange.
 * 
 * The implementation includes:
 * - Custom JSON parsing without external dependencies
 * - Robust error handling for malformed data
 * - Support for all media types and their specific attributes
 * - Proper escaping of special characters
 */
class JsonPersistence : public IPersistence {
public:
    /**
     * @brief Saves library data to a JSON file
     * @param library The library object to save
     * @param filePath The output JSON file path
     * @return true if save successful, false otherwise
     */
    bool save(const Library& library, const std::string& filePath) const override;
    
    /**
     * @brief Loads library data from a JSON file
     * @param library The library object to populate
     * @param filePath The input JSON file path
     * @return true if load successful, false otherwise
     */
    bool load(Library& library, const std::string& filePath) const override;
};

#endif // JSONPERSISTENCE_H


