#ifndef MEDIA_H
#define MEDIA_H

#include<string>
#include "Date.h"

class Media{ 
    protected:
        std::string title;
        std::string author;
        std::string genre;
        Date relaseDate;
        unsigned int kbSize;
        bool isAvailable;
        //int Rating;
        //string Review;
    public:
        Media(std::string t, std::string a, std::string g, Date rD, unsigned int kb, bool isAv);
        Media(const Media& media);
        Media();
        virtual ~Media() = 0; // Pure virtual destructor

        void setTile(const std::string& t);
        const std::string& getTitle() const;
        void setAuthor(const std::string& a);
        const std::string& getAuthor() const;
        void setGenre(const std::string& g);
        const std::string& getGenre() const;
        void setReleaseDate(const Date& rD);
        const Date& getReleaseDate() const;
        void setKbSize(unsigned int kb);
        unsigned int getKbSize() const;
        void setIsAvailable(bool isAv);
        bool getIsAvailable() const;
};

#endif // MEDIA_H