#include "Magazine.h"
#include <sstream>
#include "../Enums/Genres.h"

Magazine::Magazine(std::string title, std::string author, Enums::MagazineGenre genre, Date releaseDate, 
                   unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
                   std::string publisher, unsigned int issueNumber, std::string issn, std::string editor,
                   unsigned int pages, std::string frequency)
    : Media(title, author, releaseDate, id, kbSize, isAvailable, imagePath),
      publisher(publisher), issueNumber(issueNumber), issn(issn), editor(editor), pages(pages), frequency(frequency), genre(genre) {}

Magazine::Magazine(const Magazine& magazine) 
    : Media(magazine), publisher(magazine.publisher), issueNumber(magazine.issueNumber), issn(magazine.issn), 
      editor(magazine.editor), pages(magazine.pages), frequency(magazine.frequency), genre(magazine.genre) {}

Magazine::Magazine() : Media(), publisher(""), issueNumber(0), issn(""), editor(""), pages(0), frequency(""), genre(Enums::MagazineGenre::NEWS) {}

Magazine::~Magazine() {}

bool Magazine::isValid() const {
    return !getTitle().empty() && !publisher.empty() && issueNumber > 0 && 
           !issn.empty() && !editor.empty() && pages > 0 && !frequency.empty();
}

const std::string& Magazine::getPublisher() const {
    return publisher;
}

Magazine& Magazine::setPublisher(const std::string& pub) {
    publisher = pub;
    return *this;
}

unsigned int Magazine::getIssueNumber() const {
    return issueNumber;
}

Magazine& Magazine::setIssueNumber(unsigned int issue) {
    issueNumber = issue;
    return *this;
}

const std::string& Magazine::getIssn() const {
    return issn;
}

Magazine& Magazine::setIssn(const std::string& issn) {
    this->issn = issn;
    return *this;
}

const std::string& Magazine::getEditor() const {
    return editor;
}

Magazine& Magazine::setEditor(const std::string& ed) {
    editor = ed;
    return *this;
}

unsigned int Magazine::getPages() const {
    return pages;
}

Magazine& Magazine::setPages(unsigned int p) {
    pages = p;
    return *this;
}

const std::string& Magazine::getFrequency() const {
    return frequency;
}

Magazine& Magazine::setFrequency(const std::string& freq) {
    frequency = freq;
    return *this;
}

Enums::MagazineGenre Magazine::getGenre() const {
    return genre;
}

Magazine& Magazine::setGenre(Enums::MagazineGenre g) {
    genre = g;
    return *this;
}

std::string Magazine::getGenreString() const {
    return Enums::magazineGenreToString(genre);
}

void Magazine::accept(MediaVisitor& visitor) const {
    visitor.visit(*this);
}
