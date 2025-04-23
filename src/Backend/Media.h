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

        virtual void setTile(const std::string& title);
        virtual const std::string& getTitle() const;
        virtual void setAuthor(const std::string& author);
        virtual const std::string& getAuthor() const;
        virtual void setGenre(const std::string& genre);
        virtual const std::string& getGenre() const;
        virtual void setReleaseDate(const Date& releaseDate);
        virtual const Date& getReleaseDate() const;
        virtual void setKbSize(unsigned int kbSize);
        virtual unsigned int getKbSize() const;
        virtual void setIsAvailable(bool isAvailable);
        virtual bool getIsAvailable() const;
};