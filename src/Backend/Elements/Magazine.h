#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"


class Magazine : public Media {
    private:
        std::string publisher;      
        unsigned int issueNumber;   
        std::string issn;          
        std::string editor;        
        unsigned int pages;         
        std::string frequency;      
        Enums::MagazineGenre genre; 
        
    public:
        
        Magazine(std::string title, std::string author, Enums::MagazineGenre genre, Date releaseDate, 
                unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
                std::string publisher, unsigned int issueNumber, std::string issn, std::string editor,
                unsigned int pages, std::string frequency);
        
        
        Magazine(const Magazine& magazine);
        
        
        Magazine();
        
        
        virtual ~Magazine();

        
        virtual bool isValid() const override;
        
        
        virtual void accept(MediaVisitor& visitor) const override;

        
        std::string getPublisher() const;
        Magazine& setPublisher(const std::string& pub);
        unsigned int getIssueNumber() const;
        Magazine& setIssueNumber(unsigned int issue);
        std::string getIssn() const;
        Magazine& setIssn(const std::string& issn);
        std::string getEditor() const;
        Magazine& setEditor(const std::string& ed);
        unsigned int getPages() const;
        Magazine& setPages(unsigned int p);
        std::string getFrequency() const;
        Magazine& setFrequency(const std::string& freq);
        
        
        Enums::MagazineGenre getGenre() const;
        Magazine& setGenre(Enums::MagazineGenre genre);
        std::string getGenreString() const;
};

#endif 
