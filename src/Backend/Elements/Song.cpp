#include "Song.h"
#include <sstream>
#include "../Enums/Genres.h"

Song::Song(std::string title, std::string author, Enums::MusicGenre genre, Date releaseDate, 
           unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
           std::string artist, std::string album, unsigned int duration, std::string format,
           std::string label, unsigned int trackNumber)
    : Media(title, author, releaseDate, id, kbSize, isAvailable, imagePath),
      artist(artist), album(album), duration(duration), format(format), label(label), trackNumber(trackNumber), genre(genre) {}

Song::Song(const Song& song) : Media(song), artist(song.artist), album(song.album), duration(song.duration), format(song.format), label(song.label), trackNumber(song.trackNumber), genre(song.genre) {}

Song::Song() : Media(), artist(""), album(""), duration(0), format(""), label(""), trackNumber(0), genre(Enums::MusicGenre::POP) {}

Song::~Song() {}

bool Song::isValid() const {
    return !getTitle().empty() && !artist.empty() && !album.empty() && duration > 0 && !format.empty() && !label.empty() && trackNumber > 0;
}

std::string Song::getArtist() const {
    return artist;
}

Song& Song::setArtist(const std::string& art) {
    artist = art;
    return *this;
}

std::string Song::getAlbum() const {
    return album;
}

Song& Song::setAlbum(const std::string& alb) {
    album = alb;
    return *this;
}

unsigned int Song::getDuration() const {
    return duration;
}

Song& Song::setDuration(unsigned int dur) {
    duration = dur;
    return *this;
}

std::string Song::getFormat() const {
    return format;
}

Song& Song::setFormat(const std::string& fmt) {
    format = fmt;
    return *this;
}

std::string Song::getLabel() const {
    return label;
}

Song& Song::setLabel(const std::string& lab) {
    label = lab;
    return *this;
}

unsigned int Song::getTrackNumber() const {
    return trackNumber;
}

Song& Song::setTrackNumber(unsigned int track) {
    trackNumber = track;
    return *this;
}

Enums::MusicGenre Song::getGenre() const {
    return genre;
}

Song& Song::setGenre(Enums::MusicGenre g) {
    genre = g;
    return *this;
}

std::string Song::getGenreString() const {
    return Enums::musicGenreToString(genre);
}

void Song::accept(MediaVisitor& visitor) const {
    visitor.visit(*this);
}

