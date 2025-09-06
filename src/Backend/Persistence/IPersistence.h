#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include <string>

class Library;

/**
 * @brief Abstract interface for data persistence strategies
 * 
 * This interface defines the contract for different data persistence
 * implementations using the Strategy design pattern. It allows the
 * library system to save and load data in various formats (JSON, XML)
 * without being coupled to specific implementation details.
 * 
 * The Strategy pattern enables:
 * - Interchangeable persistence formats
 * - Easy addition of new formats
 * - Separation of persistence logic from business logic
 */
class IPersistence {
public:
    /**
     * @brief Virtual destructor for polymorphic deletion
     */
    virtual ~IPersistence() = default;

    /**
     * @brief Saves library data to a file
     * @param library The library object to save
     * @param filePath The output file path
     * @return true if save successful, false otherwise
     */
    virtual bool save(const Library& library, const std::string& filePath) const = 0;
    
    /**
     * @brief Loads library data from a file
     * @param library The library object to populate
     * @param filePath The input file path
     * @return true if load successful, false otherwise
     */
    virtual bool load(Library& library, const std::string& filePath) const = 0;
};

#endif // IPERSISTENCE_H


