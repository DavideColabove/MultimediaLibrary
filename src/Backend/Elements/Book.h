#ifndef BOOK_H
#define BOOK_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"


class Book : public Media {
    private:
        std::string publisher;      
        unsigned int pages;         
        std::string isbn;          
        Enums::Language language;   
        Enums::BookGenre genre;     
        
    public:
        
        Book(std::string title, std::string author, Enums::BookGenre genre, Date releaseDate, 
             unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
             std::string publisher, unsigned int pages, std::string isbn, Enums::Language language);
        
        
        Book(const Book& book);
        
        
        Book();
        
        
        virtual ~Book();

        
        virtual bool isValid() const override;
        
        
        virtual void accept(MediaVisitor& visitor) const override;

        
        std::string getPublisher() const;
        Book& setPublisher(const std::string& pub);
        unsigned int getPages() const;
        Book& setPages(unsigned int p);
        std::string getIsbn() const;
        Book& setIsbn(const std::string& isbn);
        Enums::Language getLanguage() const;
        Book& setLanguage(Enums::Language lang);
        std::string getLanguageString() const;
        
        
        Enums::BookGenre getGenre() const;
        Book& setGenre(Enums::BookGenre genre);
        std::string getGenreString() const;
};

#endif 
