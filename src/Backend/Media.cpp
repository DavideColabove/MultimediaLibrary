#include "Media.h"
#include "Date.h"

#include<string>
#include<iostream>

Media::Media(std::string t, std::string a, std::string g, Date rD, unsigned int kb, bool isAv)
    : title(t), author(a), genre(g), relaseDate(rD), kbSize(kb), isAvailable(isAv) {}

Media::Media(const Media& media)
    : title(media.title), author(media.author), genre(media.genre),
      relaseDate(media.relaseDate), kbSize(media.kbSize), isAvailable(media.isAvailable) {}

Media::Media() : title(""), author(""), genre(""), relaseDate(Date()), kbSize(0), isAvailable(false) {}

Media::~Media() {} // Pure virtual destructor

void Media::setTile(const std::string& title) {
    
}