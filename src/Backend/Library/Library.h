#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>

// Forward declarations
class Media;
class Book;
class Movie;
class Song;
class Magazine;
class Podcast;
class IPersistence;

/**
 * @brief Central library management class
 * 
 * This class serves as the main controller for the multimedia library system.
 * It manages a collection of media items, provides CRUD operations, search
 * and filtering capabilities, data persistence, and statistical analysis.
 * The class uses smart pointers for automatic memory management and
 * implements various algorithms for efficient data retrieval.
 */
class Library
{
public:
    /**
     * @brief Default constructor
     */
    Library();
    
    /**
     * @brief Default destructor
     */
    ~Library() = default;

    /**
     * @brief Adds a new media item to the library
     * @param media Unique pointer to the media item to add
     */
    void addMedia(std::unique_ptr<Media> media);
    
    /**
     * @brief Removes a media item by its unique identifier
     * @param id The unique identifier of the media to remove
     */
    void removeMedia(int id);
    
    /**
     * @brief Finds a media item by its unique identifier
     * @param id The unique identifier to search for
     * @return Pointer to the media item if found, nullptr otherwise
     */
    Media* findMediaById(int id);
    
    /**
     * @brief Retrieves all media items in the library
     * @return Vector of pointers to all media items
     */
    std::vector<Media*> getAllMedia() const;
    
    /**
     * @brief Searches for media items by title (case-insensitive partial match)
     * @param title The title to search for
     * @return Vector of media items matching the search criteria
     */
    std::vector<Media*> searchByTitle(const std::string& title) const;
    
    /**
     * @brief Searches for media items by author (case-insensitive partial match)
     * @param author The author to search for
     * @return Vector of media items matching the search criteria
     */
    std::vector<Media*> searchByAuthor(const std::string& author) const;
    
    /**
     * @brief Filters media items by their type
     * @param type The media type to filter by (Book, Movie, Song, etc.)
     * @return Vector of media items of the specified type
     */
    std::vector<Media*> filterByType(const std::string& type) const;
    
    /**
     * @brief Filters media items by availability status
     * @param available The availability status to filter by
     * @return Vector of media items with the specified availability
     */
    std::vector<Media*> filterByAvailability(bool available) const;

    /**
     * @brief Saves the library data to a JSON file
     * @param filePath The output file path
     * @return true if save successful, false otherwise
     */
    bool saveJson(const std::string& filePath) const;
    
    /**
     * @brief Loads library data from a JSON file
     * @param filePath The input file path
     * @return true if load successful, false otherwise
     */
    bool loadJson(const std::string& filePath);
    
    /**
     * @brief Saves the library data to an XML file
     * @param filePath The output file path
     * @return true if save successful, false otherwise
     */
    bool saveXml(const std::string& filePath) const;
    
    /**
     * @brief Loads library data from an XML file
     * @param filePath The input file path
     * @return true if load successful, false otherwise
     */
    bool loadXml(const std::string& filePath);
    
    /**
     * @brief Gets the total number of media items in the library
     * @return Total count of media items
     */
    size_t getTotalCount() const;
    
    /**
     * @brief Gets the number of available media items
     * @return Count of available media items
     */
    size_t getAvailableCount() const;
    
    /**
     * @brief Gets the count of media items of a specific type
     * @param type The media type to count
     * @return Count of media items of the specified type
     */
    size_t getCountByType(const std::string& type) const;
    
    /**
     * @brief Gets statistics about media types in the library
     * @return Map of media type names to their counts
     */
    std::map<std::string, size_t> getMediaTypeStats() const;
    
    /**
     * @brief Generates and returns the next available unique identifier
     * @return Next unique identifier
     */
    int getNextId();
    
    /**
     * @brief Clears all media items from the library
     */
    void clear();
    
    /**
     * @brief Checks if the library is empty
     * @return true if no media items exist, false otherwise
     */
    bool isEmpty() const;
    
    /**
     * @brief Determines the type of a media item using the Visitor pattern
     * @param media Pointer to the media item
     * @return String representation of the media type
     */
    std::string getMediaType(const Media* media) const;

private:
    std::vector<std::unique_ptr<Media>> mediaCollection;  // Collection of media items
    unsigned int nextId;                                   // Next available unique identifier
    
    /**
     * @brief Generates the next unique identifier
     */
    void generateNextId();
};

#endif // LIBRARY_H
