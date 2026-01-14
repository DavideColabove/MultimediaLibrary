#include "Media.h"

#include<string>
#include<iostream>

Media::Media(std::string t, std::string a, Date rD, unsigned int id, unsigned int kb, bool isAv, std::string im): title(t), author(a), releaseDate(rD), id(id), kbSize(kb), isAvailable(isAv), imagePath(im) {}

Media::Media(const Media& media): title(media.title), id(media.id), author(media.author), releaseDate(media.releaseDate), kbSize(media.kbSize), isAvailable(media.isAvailable), imagePath(media.imagePath) {}

Media::Media() : title(""), id(0), author(""), releaseDate(), kbSize(0), isAvailable(false), imagePath("") {}



Media& Media::setTitle(const std::string& t) {
    this->title = t;
    return *this;
}
const std::string& Media::getTitle() const {
    return title;
}

Media& Media::setAuthor(const std::string& a) {
    this->author = a;
    return *this;
}
const std::string& Media::getAuthor() const {
    return author;
}



Media& Media::setReleaseDate(const Date& rD) {
    this->releaseDate = rD;
    return *this;
}
const Date& Media::getReleaseDate() const {
    return releaseDate;
}

Media& Media::setID(unsigned int id) {
    this->id = id;
    return *this;
}
unsigned int Media::getID() const {
    return id;
}

Media& Media::setKbSize(unsigned int kb) {
    this->kbSize = kb;
    return *this;
}
unsigned int Media::getKbSize() const {
    return kbSize;
}

Media& Media::setIsAvailable(bool isAv) {
    this->isAvailable = isAv;
    return *this;
}
bool Media::getIsAvailable() const {
    return isAvailable;
}

Media& Media::setImagePath(const std::string& im) {
    this->imagePath = im;
    return *this;
}
const std::string& Media::getImagePath() const {
    return imagePath;
}