#include "Media.h"
#include "Date.h"

#include<string>
#include<iostream>

Media::Media(std::string t, std::string a, std::string g, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im): title(t), author(a), genre(g), relaseDate(rD), id(id), kbSize(kb), isAvailable(isAv), imagePath(im) {}

Media::Media(const Media& media): title(media.title), id(media.id), author(media.author), genre(media.genre), relaseDate(media.relaseDate), kbSize(media.kbSize), isAvailable(media.isAvailable), imagePath(media.imagePath) {}

Media::Media() : title(""), id(0), author(""), genre(""), relaseDate(Date()), kbSize(0), isAvailable(false), imagePath("") {}

Media::~Media() {} // Pure virtual destructor

void Media::setTile(const std::string& t) {
    title = t;
}

const std::string& Media::getTitle() const {
    return title;
}
void Media::setAuthor(const std::string& a) {
    author = a;
}
const std::string& Media::getAuthor() const {
    return author;
}

void Media::setGenre(const std::string& g) {
    genre = g;
}

const std::string& Media::getGenre() const {
    return genre;
}

void Media::setReleaseDate(const Date& rD) {
    relaseDate = rD;
}

const Date& Media::getReleaseDate() const {
    return relaseDate;
}

void Media::setKbSize(unsigned int kb) {
    kbSize = kb;
}

unsigned int Media::getKbSize() const {
    return kbSize;
}

void Media::setIsAvailable(bool isAv) {
    isAvailable = isAv;
}

bool Media::getIsAvailable() const {
    return isAvailable;
}