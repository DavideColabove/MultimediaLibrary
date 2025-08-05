#ifndef MOVIE_H
#define MOVIE_H

#include "Date.h"
#include "Media.h"
#include<string>

class Movie : public Media {
    private:
        std::string director;
        unsigned int duration;
        std::string language;
        
    public:
        Movie(std::string t, std::string a, std::string g, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im, std::string dir, unsigned int dur, std::string lang);
        Movie(const Movie& movie);
        Movie();
        ~Movie();

        Movie& setDirector(const std::string& dir);
        const std::string& getDirector() const;
        Movie& setDuration(unsigned int dur);
        unsigned int getDuration() const;
        Movie& setLanguage(const std::string& lang);
        const std::string& getLanguage() const;
};

#endif // MOVIE_H