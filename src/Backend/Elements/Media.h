#ifndef MEDIA_H
#define MEDIA_H

#include<string>
#include "Date.h"
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"
#include "MediaVisitor.h"

/**
 * @brief Abstract base class for all media types in the library
 * 
 * This class defines the common interface and shared attributes for all media items
 * (books, movies, songs, magazines, podcasts). It enforces polymorphic behavior
 * through pure virtual methods and provides a unified interface for media operations.
 * 
 * The class implements the Visitor pattern through the accept() method, allowing
 * type-safe operations on different media types without using type checking.
 */
class Media{ 
    protected:
        std::string title;          // Human-readable title of the media
        std::string author;         // Creator, artist, or author of the media
        Date releaseDate;           // Publication or release date
        unsigned int id;            // Unique identifier managed by the Library class
        unsigned int kbSize;        // Approximate file size in kilobytes
        bool isAvailable;           // Availability status for lending/borrowing
        std::string imagePath;      // Path to cover image or thumbnail
        
    public:
        /**
         * @brief Constructs a Media object with all required attributes
         * @param t Title of the media
         * @param a Author or creator
         * @param rD Release date
         * @param id Unique identifier
         * @param kb Size in kilobytes
         * @param isAv Availability status
         * @param im Path to cover image
         */
        Media(std::string t, std::string a, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im);
        
        /**
         * @brief Copy constructor
         * @param media Media object to copy from
         */
        Media(const Media& media);
        
        /**
         * @brief Default constructor
         */
        Media();
        
        /**
         * @brief Virtual destructor for polymorphic deletion
         */
        virtual ~Media() = default;

        /**
         * @brief Validates media-specific attributes
         * 
         * Each derived class must implement its own validation logic
         * to ensure data integrity and business rule compliance.
         * 
         * @return true if the media object is valid, false otherwise
         */
        virtual bool isValid() const = 0;
        
        /**
         * @brief Accepts a visitor for type-safe operations
         * 
         * Implements the Visitor pattern to allow external operations
         * on media objects without type checking or casting.
         * 
         * @param visitor The visitor object to accept
         */
        virtual void accept(MediaVisitor& visitor) const = 0;

        // Getters and setters for common attributes
        Media& setTitle(const std::string& t);
        const std::string& getTitle() const;
        Media& setAuthor(const std::string& a);
        const std::string& getAuthor() const;
        Media& setReleaseDate(const Date& rD);
        const Date& getReleaseDate() const;
        Media& setID(unsigned int id);
        unsigned int getID() const;
        Media& setKbSize(unsigned int kb);
        unsigned int getKbSize() const;
        Media& setIsAvailable(bool isAv);
        bool getIsAvailable() const;
        Media& setImagePath(const std::string& im);
        const std::string& getImagePath() const;
};

#endif // MEDIA_H