#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"


class Movie : public Media {
    private:
        std::string director;       
        unsigned int duration;      
        std::string studio;         
        std::string rating;         
        Enums::Language language;   
        std::string country;        
        Enums::MovieGenre genre;    
        
    public:
        
        Movie(std::string title, std::string author, Enums::MovieGenre genre, Date releaseDate, 
              unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
              std::string director, unsigned int duration, std::string studio, std::string rating,
              Enums::Language language, std::string country);
        
        
        Movie(const Movie& movie);
        
        
        Movie();
        
        
        virtual ~Movie();

        
        virtual bool isValid() const override;
        
        
        virtual void accept(MediaVisitor& visitor) const override;
    virtual void accept(MediaVisitorMutable& visitor) override { visitor.visit(*this); }


        
        std::string getDirector() const;
        Movie& setDirector(const std::string& dir);
        unsigned int getDuration() const;
        Movie& setDuration(unsigned int dur);
        std::string getStudio() const;
        Movie& setStudio(const std::string& stu);
        std::string getRating() const;
        Movie& setRating(const std::string& rat);
        Enums::Language getLanguage() const;
        Movie& setLanguage(Enums::Language lang);
        std::string getLanguageString() const;
        std::string getCountry() const;
        Movie& setCountry(const std::string& cou);
        
        
        Enums::MovieGenre getGenre() const;
        Movie& setGenre(Enums::MovieGenre genre);
        std::string getGenreString() const;
};

#endif 
