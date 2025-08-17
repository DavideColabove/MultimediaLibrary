#include "Book.h"
#include <sstream>
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

Book::Book(std::string title, std::string author, Enums::BookGenre genre, Date releaseDate, 
           unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
           std::string publisher, unsigned int pages, std::string isbn, Enums::Language language)
    : Media(title, author, releaseDate, id, kbSize, isAvailable, imagePath),
      publisher(publisher), pages(pages), isbn(isbn), language(language), genre(genre) {}

Book::Book(const Book& book) 
    : Media(book), publisher(book.publisher), pages(book.pages), isbn(book.isbn), language(book.language), genre(book.genre) {}

Book::Book() : Media(), publisher(""), pages(0), isbn(""), language(Enums::Language::ITALIAN), genre(Enums::BookGenre::FICTION) {}

Book::~Book() {}

// Check if book has all required fields filled
bool Book::isValid() const {
    return !getTitle().empty() && !getAuthor().empty() && !publisher.empty() && 
           pages > 0 && !isbn.empty();
}

std::string Book::getPublisher() const {
    return publisher;
}

Book& Book::setPublisher(const std::string& pub) {
    publisher = pub;
    return *this;
}

unsigned int Book::getPages() const {
    return pages;
}

Book& Book::setPages(unsigned int p) {
    pages = p;
    return *this;
}

std::string Book::getIsbn() const {
    return isbn;
}

Book& Book::setIsbn(const std::string& isbn) {
    this->isbn = isbn;
    return *this;
}

Enums::Language Book::getLanguage() const {
    return language;
}

Book& Book::setLanguage(Enums::Language lang) {
    language = lang;
    return *this;
}

std::string Book::getLanguageString() const {
    return Enums::languageToString(language);
}

Enums::BookGenre Book::getGenre() const {
    return genre;
}

Book& Book::setGenre(Enums::BookGenre g) {
    genre = g;
    return *this;
}

std::string Book::getGenreString() const {
    return Enums::bookGenreToString(genre);
}

void Book::accept(MediaVisitor& visitor) const {
    visitor.visit(*this);
}
