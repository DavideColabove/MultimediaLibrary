#ifndef MEDIA_H
#define MEDIA_H

#include<string>
#include "Date.h"
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"
#include "MediaVisitor.h"


class Media{ 
    protected:
        std::string title;          
        std::string author;         
        Date releaseDate;           
        unsigned int id;            
        unsigned int kbSize;        
        bool isAvailable;           
        std::string imagePath;      
        
    public:
        
        Media(std::string t, std::string a, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im);
        
        
        Media(const Media& media);
        
        
        Media();
        
        
        virtual ~Media() = default;

        
        virtual bool isValid() const = 0;
        
        
        virtual void accept(MediaVisitor& visitor) const = 0;

        
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

#endif 