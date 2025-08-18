#ifndef BOOK_H
#define BOOK_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

/**
 * @brief Concrete media class representing a book
 * 
 * This class extends the Media base class to represent books with specific
 * bibliographic metadata such as publisher, page count, ISBN, language,
 * and literary genre. It implements book-specific validation rules and
 * provides methods for accessing and modifying book attributes.
 */
class Book : public Media {
    private:
        std::string publisher;      // Publishing company or organization
        unsigned int pages;         // Number of pages in the book
        std::string isbn;          // International Standard Book Number
        Enums::Language language;   // Language the book is written in
        Enums::BookGenre genre;     // Literary genre classification
        
    public:
        /**
         * @brief Constructs a Book with all required attributes
         * @param title Book title
         * @param author Book author
         * @param genre Literary genre
         * @param releaseDate Publication date
         * @param id Unique identifier
         * @param kbSize File size in kilobytes
         * @param isAvailable Availability status
         * @param imagePath Path to cover image
         * @param publisher Publishing company
         * @param pages Number of pages
         * @param isbn ISBN code
         * @param language Book language
         */
        Book(std::string title, std::string author, Enums::BookGenre genre, Date releaseDate, 
             unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
             std::string publisher, unsigned int pages, std::string isbn, Enums::Language language);
        
        /**
         * @brief Copy constructor
         * @param book Book object to copy from
         */
        Book(const Book& book);
        
        /**
         * @brief Default constructor
         */
        Book();
        
        /**
         * @brief Virtual destructor
         */
        virtual ~Book();

        /**
         * @brief Validates book-specific attributes
         * 
         * Ensures that the book has valid bibliographic information:
         * - Title and author are not empty
         * - Publisher is specified
         * - Page count is positive
         * - ISBN is provided
         * 
         * @return true if all book attributes are valid
         */
        virtual bool isValid() const override;
        
        /**
         * @brief Accepts a visitor for type-safe operations
         * @param visitor The visitor object to accept
         */
        virtual void accept(MediaVisitor& visitor) const override;

        // Book-specific attribute accessors
        const std::string& getPublisher() const;
        Book& setPublisher(const std::string& pub);
        unsigned int getPages() const;
        Book& setPages(unsigned int p);
        const std::string& getIsbn() const;
        Book& setIsbn(const std::string& isbn);
        Enums::Language getLanguage() const;
        Book& setLanguage(Enums::Language lang);
        std::string getLanguageString() const;
        
        // Genre management methods
        Enums::BookGenre getGenre() const;
        Book& setGenre(Enums::BookGenre genre);
        std::string getGenreString() const;
};

#endif // BOOK_H
