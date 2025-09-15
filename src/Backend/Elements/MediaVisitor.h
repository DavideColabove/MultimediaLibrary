#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class Book;
class Movie;
class Song;
class Magazine;
class Podcast;

class MediaVisitor {
public:
    virtual ~MediaVisitor() = default;
    virtual void visit(const Book& book) = 0;
    virtual void visit(const Movie& movie) = 0;
    virtual void visit(const Song& song) = 0;
    virtual void visit(const Magazine& magazine) = 0;
    virtual void visit(const Podcast& podcast) = 0;
};

class MediaVisitorMutable {
public:
    virtual ~MediaVisitorMutable() = default;
    virtual void visit(Book& book) = 0;
    virtual void visit(Movie& movie) = 0;
    virtual void visit(Song& song) = 0;
    virtual void visit(Magazine& magazine) = 0;
    virtual void visit(Podcast& podcast) = 0;
};

#endif 


