#include "MediaFactory.h"
#include "../Elements/Media.h"
#include "../Elements/Book.h"
#include "../Elements/Movie.h"
#include "../Elements/Song.h"
#include "../Elements/Magazine.h"
#include "../Elements/Podcast.h"
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

#include <QJsonObject>
#include <QXmlStreamAttributes>
#include <QString>

namespace MediaFactory {
    std::unique_ptr<Media> fromJson(const QString& type, const Common& c, const QJsonObject& o) {
        const Date& releaseDate = *c.releaseDatePtr;
        if (type == "Book") {
            const QJsonObject b = o.value("book").toObject();
            return std::make_unique<Book>(c.title, c.author,
                static_cast<Enums::BookGenre>(b.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                b.value("publisher").toString().toStdString(), static_cast<unsigned>(b.value("pages").toInt()), b.value("isbn").toString().toStdString(),
                static_cast<Enums::Language>(b.value("language").toInt()));
        }
        if (type == "Movie") {
            const QJsonObject mv = o.value("movie").toObject();
            return std::make_unique<Movie>(c.title, c.author,
                static_cast<Enums::MovieGenre>(mv.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                mv.value("director").toString().toStdString(), static_cast<unsigned>(mv.value("duration").toInt()), mv.value("studio").toString().toStdString(), mv.value("rating").toString().toStdString(),
                static_cast<Enums::Language>(mv.value("language").toInt()), mv.value("country").toString().toStdString());
        }
        if (type == "Song") {
            const QJsonObject s = o.value("song").toObject();
            return std::make_unique<Song>(c.title, c.author,
                static_cast<Enums::MusicGenre>(s.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                s.value("artist").toString().toStdString(), s.value("album").toString().toStdString(), static_cast<unsigned>(s.value("duration").toInt()), s.value("format").toString().toStdString(), s.value("label").toString().toStdString(), static_cast<unsigned>(s.value("track").toInt()));
        }
        if (type == "Magazine") {
            const QJsonObject mg = o.value("magazine").toObject();
            return std::make_unique<Magazine>(c.title, c.author,
                static_cast<Enums::MagazineGenre>(mg.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                mg.value("publisher").toString().toStdString(), static_cast<unsigned>(mg.value("issue").toInt()), mg.value("issn").toString().toStdString(), mg.value("editor").toString().toStdString(), static_cast<unsigned>(mg.value("pages").toInt()), mg.value("frequency").toString().toStdString());
        }
        if (type == "Podcast") {
            const QJsonObject pc = o.value("podcast").toObject();
            return std::make_unique<Podcast>(c.title, c.author,
                static_cast<Enums::PodcastGenre>(pc.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                pc.value("host").toString().toStdString(), static_cast<unsigned>(pc.value("episodes").toInt()), pc.value("platform").toString().toStdString(), static_cast<unsigned>(pc.value("duration").toInt()), pc.value("series").toString().toStdString(), pc.value("description").toString().toStdString());
        }
        return nullptr;
    }

    std::unique_ptr<Media> fromXml(const QString& type, const Common& c, const QXmlStreamAttributes& attrs) {
        const Date& releaseDate = *c.releaseDatePtr;
        if (type == "Book") {
            return std::make_unique<Book>(c.title, c.author,
                static_cast<Enums::BookGenre>(attrs.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                attrs.value("publisher").toString().toStdString(), static_cast<unsigned>(attrs.value("pages").toUInt()), attrs.value("isbn").toString().toStdString(),
                static_cast<Enums::Language>(attrs.value("language").toInt()));
        }
        if (type == "Movie") {
            return std::make_unique<Movie>(c.title, c.author,
                static_cast<Enums::MovieGenre>(attrs.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                attrs.value("director").toString().toStdString(), static_cast<unsigned>(attrs.value("duration").toUInt()), attrs.value("studio").toString().toStdString(), attrs.value("rating").toString().toStdString(),
                static_cast<Enums::Language>(attrs.value("language").toInt()), attrs.value("country").toString().toStdString());
        }
        if (type == "Song") {
            return std::make_unique<Song>(c.title, c.author,
                static_cast<Enums::MusicGenre>(attrs.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                attrs.value("artist").toString().toStdString(), attrs.value("album").toString().toStdString(), static_cast<unsigned>(attrs.value("duration").toUInt()), attrs.value("format").toString().toStdString(), attrs.value("label").toString().toStdString(), static_cast<unsigned>(attrs.value("track").toUInt()));
        }
        if (type == "Magazine") {
            return std::make_unique<Magazine>(c.title, c.author,
                static_cast<Enums::MagazineGenre>(attrs.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                attrs.value("publisher").toString().toStdString(), static_cast<unsigned>(attrs.value("issue").toUInt()), attrs.value("issn").toString().toStdString(), attrs.value("editor").toString().toStdString(), static_cast<unsigned>(attrs.value("pages").toUInt()), attrs.value("frequency").toString().toStdString());
        }
        if (type == "Podcast") {
            return std::make_unique<Podcast>(c.title, c.author,
                static_cast<Enums::PodcastGenre>(attrs.value("genre").toInt()), releaseDate, c.id, c.sizeKb, c.available, c.imagePath,
                attrs.value("host").toString().toStdString(), static_cast<unsigned>(attrs.value("episodes").toUInt()), attrs.value("platform").toString().toStdString(), static_cast<unsigned>(attrs.value("duration").toUInt()), attrs.value("series").toString().toStdString(), attrs.value("description").toString().toStdString());
        }
        return nullptr;
    }
}
