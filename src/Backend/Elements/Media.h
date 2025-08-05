#ifndef MEDIA_H
#define MEDIA_H

#include<string>
#include "Date.h"

class Media{ 
    protected:
        std::string title;
        std::string author;
        std::string genre;
        Date releaseDate;
        unsigned int id;
        unsigned int kbSize;
        bool isAvailable;
        std::string imagePath;
        //int Rating;
        //string Review;
    public:
        Media(std::string t, std::string a, std::string g, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im);
        Media(const Media& media);
        Media();
        virtual ~Media() = 0; // Pure virtual destructor

        Media& setTitle(const std::string& t);
        const std::string& getTitle() const;
        Media& setAuthor(const std::string& a);
        const std::string& getAuthor() const;
        Media& setGenre(const std::string& g);
        const std::string& getGenre() const;
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