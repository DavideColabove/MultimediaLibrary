#pragma once
#include <QString>
#include "../../Backend/Elements/MediaVisitor.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"

namespace FrontendVisitors {

struct TypeNameVisitor : MediaVisitor {
    QString typeName;
    void visit(const Book&) override { typeName = "Book"; }
    void visit(const Movie&) override { typeName = "Movie"; }
    void visit(const Song&) override { typeName = "Song"; }
    void visit(const Magazine&) override { typeName = "Magazine"; }
    void visit(const Podcast&) override { typeName = "Podcast"; }
};

struct IconKeyVisitor : MediaVisitor {
    QString iconKey;
    void visit(const Book&) override { iconKey = "book"; }
    void visit(const Movie&) override { iconKey = "movie"; }
    void visit(const Song&) override { iconKey = "music"; }
    void visit(const Magazine&) override { iconKey = "magazine"; }
    void visit(const Podcast&) override { iconKey = "podcast"; }
};

struct GenreCheckVisitor : MediaVisitor {
    int bookGenre{-1};
    int movieGenre{-1};
    int musicGenre{-1};
    int magazineGenre{-1};
    int podcastGenre{-1};
    bool ok{true};
    GenreCheckVisitor() = default;
    GenreCheckVisitor(int b, int mv, int mu, int mg, int pc)
        : bookGenre(b), movieGenre(mv), musicGenre(mu), magazineGenre(mg), podcastGenre(pc) {}
    void visit(const Book& b) override { if (bookGenre    >= 0) ok = ok && (static_cast<int>(b.getGenre())  == bookGenre); }
    void visit(const Movie& m) override { if (movieGenre   >= 0) ok = ok && (static_cast<int>(m.getGenre())  == movieGenre); }
    void visit(const Song& s) override { if (musicGenre   >= 0) ok = ok && (static_cast<int>(s.getGenre())  == musicGenre); }
    void visit(const Magazine& mg) override { if (magazineGenre>= 0) ok = ok && (static_cast<int>(mg.getGenre()) == magazineGenre); }
    void visit(const Podcast& p) override { if (podcastGenre >= 0) ok = ok && (static_cast<int>(p.getGenre()) == podcastGenre); }
};

}
