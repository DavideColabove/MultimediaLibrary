#include "Movie.h"
#include "Date.h"
#include "Media.h"
#include<string>

Movie::Movie(std::string t, std::string a, std::string g, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im, std::string dir, unsigned int dur, std::string lang)
    : Media(t, a, g, rD, id, kb, isAv, im), director(dir), duration(dur), language(lang) {}

Movie::Movie(const Movie& movie)
    : Media(movie), director(movie.director), duration(movie.duration), language(movie.language) {}

Movie::Movie() : Media(), director(""), duration(0), language("") {}

Movie::~Movie() {}

Movie& Movie::setDirector(const std::string& dir) {
    this->director = dir;
    return *this;
}
const std::string& Movie::getDirector() const {
    return director;
}

Movie& Movie::setDuration(unsigned int dur) {
    this->duration = dur;
    return *this;
}
unsigned int Movie::getDuration() const {
    return duration;
}

Movie& Movie::setLanguage(const std::string& lang) {
    this->language = lang;
    return *this;
}
const std::string& Movie::getLanguage() const {
    return language;
}


