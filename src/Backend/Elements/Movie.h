#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

/**
 * @brief Concrete media class representing a movie or film
 * 
 * This class extends the Media base class to represent movies with specific
 * cinematic metadata such as director, duration, production studio, content
 * rating, language, country of origin, and film genre. It implements
 * movie-specific validation rules and provides methods for accessing and
 * modifying movie attributes.
 */
class Movie : public Media {
    private:
        std::string director;       // Film director or primary filmmaker
        unsigned int duration;      // Runtime duration in minutes
        std::string studio;         // Production studio or company
        std::string rating;         // Content rating (PG, PG-13, R, etc.)
        Enums::Language language;   // Primary language of the film
        std::string country;        // Country of origin or production
        Enums::MovieGenre genre;    // Cinematic genre classification
        
    public:
        /**
         * @brief Constructs a Movie with all required attributes
         * @param title Movie title
         * @param author Screenwriter or primary creator
         * @param genre Cinematic genre
         * @param releaseDate Release date
         * @param id Unique identifier
         * @param kbSize File size in kilobytes
         * @param isAvailable Availability status
         * @param imagePath Path to poster image
         * @param director Film director
         * @param duration Runtime in minutes
         * @param studio Production studio
         * @param rating Content rating
         * @param language Primary language
         * @param country Country of origin
         */
        Movie(std::string title, std::string author, Enums::MovieGenre genre, Date releaseDate, 
              unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
              std::string director, unsigned int duration, std::string studio, std::string rating,
              Enums::Language language, std::string country);
        
        /**
         * @brief Copy constructor
         * @param movie Movie object to copy from
         */
        Movie(const Movie& movie);
        
        /**
         * @brief Default constructor
         */
        Movie();
        
        /**
         * @brief Virtual destructor
         */
        virtual ~Movie();

        /**
         * @brief Validates movie-specific attributes
         * 
         * Ensures that the movie has valid cinematic information:
         * - Title and director are not empty
         * - Duration is positive
         * - Studio is specified
         * - Rating is provided
         * - Country of origin is specified
         * 
         * @return true if all movie attributes are valid
         */
        virtual bool isValid() const override;
        
        /**
         * @brief Accepts a visitor for type-safe operations
         * @param visitor The visitor object to accept
         */
        virtual void accept(MediaVisitor& visitor) const override;

        // Movie-specific attribute accessors
        const std::string& getDirector() const;
        Movie& setDirector(const std::string& dir);
        unsigned int getDuration() const;
        Movie& setDuration(unsigned int dur);
        const std::string& getStudio() const;
        Movie& setStudio(const std::string& stu);
        const std::string& getRating() const;
        Movie& setRating(const std::string& rat);
        Enums::Language getLanguage() const;
        Movie& setLanguage(Enums::Language lang);
        std::string getLanguageString() const;
        const std::string& getCountry() const;
        Movie& setCountry(const std::string& cou);
        
        // Genre management methods
        Enums::MovieGenre getGenre() const;
        Movie& setGenre(Enums::MovieGenre genre);
        std::string getGenreString() const;
};

#endif // MOVIE_H
