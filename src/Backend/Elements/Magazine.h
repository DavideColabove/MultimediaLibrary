#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"

/**
 * @brief Concrete media class representing a magazine issue
 * 
 * This class extends the Media base class to represent magazine issues with specific
 * editorial metadata such as publisher, issue number, ISSN, editor, page count,
 * publication frequency, and magazine genre. It implements magazine-specific
 * validation rules and provides methods for accessing and modifying magazine
 * attributes.
 */
class Magazine : public Media {
    private:
        std::string publisher;      // Publishing company or organization
        unsigned int issueNumber;   // Sequential issue number
        std::string issn;          // International Standard Serial Number
        std::string editor;        // Editor-in-chief or managing editor
        unsigned int pages;         // Number of pages in the issue
        std::string frequency;      // Publication frequency (Monthly, Weekly, etc.)
        Enums::MagazineGenre genre; // Magazine category or genre
        
    public:
        /**
         * @brief Constructs a Magazine with all required attributes
         * @param title Magazine title
         * @param author Primary author or contributor
         * @param genre Magazine genre
         * @param releaseDate Publication date
         * @param id Unique identifier
         * @param kbSize File size in kilobytes
         * @param isAvailable Availability status
         * @param imagePath Path to cover image
         * @param publisher Publishing company
         * @param issueNumber Issue number
         * @param issn ISSN code
         * @param editor Editor-in-chief
         * @param pages Number of pages
         * @param frequency Publication frequency
         */
        Magazine(std::string title, std::string author, Enums::MagazineGenre genre, Date releaseDate, 
                unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
                std::string publisher, unsigned int issueNumber, std::string issn, std::string editor,
                unsigned int pages, std::string frequency);
        
        /**
         * @brief Copy constructor
         * @param magazine Magazine object to copy from
         */
        Magazine(const Magazine& magazine);
        
        /**
         * @brief Default constructor
         */
        Magazine();
        
        /**
         * @brief Virtual destructor
         */
        virtual ~Magazine();

        /**
         * @brief Validates magazine-specific attributes
         * 
         * Ensures that the magazine has valid editorial information:
         * - Title and publisher are not empty
         * - Issue number is positive
         * - ISSN is provided
         * - Editor is specified
         * - Page count is positive
         * - Publication frequency is specified
         * 
         * @return true if all magazine attributes are valid
         */
        virtual bool isValid() const override;
        
        /**
         * @brief Accepts a visitor for type-safe operations
         * @param visitor The visitor object to accept
         */
        virtual void accept(MediaVisitor& visitor) const override;

        // Magazine-specific attribute accessors
        const std::string& getPublisher() const;
        Magazine& setPublisher(const std::string& pub);
        unsigned int getIssueNumber() const;
        Magazine& setIssueNumber(unsigned int issue);
        const std::string& getIssn() const;
        Magazine& setIssn(const std::string& issn);
        const std::string& getEditor() const;
        Magazine& setEditor(const std::string& ed);
        unsigned int getPages() const;
        Magazine& setPages(unsigned int p);
        const std::string& getFrequency() const;
        Magazine& setFrequency(const std::string& freq);
        
        // Genre management methods
        Enums::MagazineGenre getGenre() const;
        Magazine& setGenre(Enums::MagazineGenre genre);
        std::string getGenreString() const;
};

#endif // MAGAZINE_H
