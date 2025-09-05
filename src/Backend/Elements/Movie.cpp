#include "Movie.h"
#include <sstream>
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

Movie::Movie(std::string title, std::string author, Enums::MovieGenre genre, Date releaseDate, 
             unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
             std::string director, unsigned int duration, std::string studio, std::string rating,
             Enums::Language language, std::string country)
    : Media(title, author, releaseDate, id, kbSize, isAvailable, imagePath),
      director(director), duration(duration), studio(studio), rating(rating), language(language), country(country), genre(genre) {}

Movie::Movie(const Movie& movie) 
    : Media(movie), director(movie.director), duration(movie.duration), studio(movie.studio), 
      rating(movie.rating), language(movie.language), country(movie.country), genre(movie.genre) {}

Movie::Movie() : Media(), director(""), duration(0), studio(""), rating(""), language(Enums::Language::ENGLISH), country(""), genre(Enums::MovieGenre::DRAMA) {}

Movie::~Movie() {}

bool Movie::isValid() const {
    return !getTitle().empty() && !director.empty() && !studio.empty() && 
           duration > 0 && !rating.empty() && !country.empty();
}

std::string Movie::getDirector() const {
    return director;
}

Movie& Movie::setDirector(const std::string& dir) {
    director = dir;
    return *this;
}

unsigned int Movie::getDuration() const {
    return duration;
}

Movie& Movie::setDuration(unsigned int dur) {
    duration = dur;
    return *this;
}

std::string Movie::getStudio() const {
    return studio;
}

Movie& Movie::setStudio(const std::string& stu) {
    studio = stu;
    return *this;
}

std::string Movie::getRating() const {
    return rating;
}

Movie& Movie::setRating(const std::string& rat) {
    rating = rat;
    return *this;
}

Enums::Language Movie::getLanguage() const {
    return language;
}

Movie& Movie::setLanguage(Enums::Language lang) {
    language = lang;
    return *this;
}

std::string Movie::getLanguageString() const {
    return Enums::languageToString(language);
}

std::string Movie::getCountry() const {
    return country;
}

Movie& Movie::setCountry(const std::string& cou) {
    country = cou;
    return *this;
}

Enums::MovieGenre Movie::getGenre() const {
    return genre;
}

Movie& Movie::setGenre(Enums::MovieGenre g) {
    genre = g;
    return *this;
}

std::string Movie::getGenreString() const {
    return Enums::movieGenreToString(genre);
}

void Movie::accept(MediaVisitor& visitor) const {
    visitor.visit(*this);
}

