#include "XmlPersistence.h"
#include "../Library/Library.h"
#include "../Elements/MediaVisitor.h"
#include "MediaFactory.h"
#include "../Elements/Book.h"
#include "../Elements/Movie.h"
#include "../Elements/Song.h"
#include "../Elements/Magazine.h"
#include "../Elements/Podcast.h"
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

#include <fstream>
#include <sstream>
#include <QFile>
#include <QXmlStreamReader>

static std::string xmlEscape(const std::string& s) {
    std::string out; out.reserve(s.size()+8);
    for (char c : s) {
        switch (c) {
            case '&': out += "&amp;"; break;
            case '<': out += "&lt;"; break;
            case '>': out += "&gt;"; break;
            case '"': out += "&quot;"; break;
            case '\'': out += "&apos;"; break;
            default: out += c; break;
        }
    }
    return out;
}

bool XmlPersistence::save(const Library& library, const std::string& filePath) const {
    std::ofstream out(filePath);
    if (!out.is_open()) return false;
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    out << "<library>\n";
    for (auto m : library.getAllMedia()) {
        class XmlWriteVisitor final : public MediaVisitor {
        public:
            std::string typeName;
            std::string node; 
            void visit(const Book& b) override {
                typeName = "Book";
                node = "    <book publisher=\"" + xmlEscape(b.getPublisher()) +
                       "\" pages=\"" + std::to_string(b.getPages()) +
                       "\" isbn=\"" + xmlEscape(b.getIsbn()) +
                       "\" language=\"" + std::to_string(static_cast<int>(b.getLanguage())) +
                       "\" genre=\"" + std::to_string(static_cast<int>(b.getGenre())) + "\"/>\n";
            }
            void visit(const Movie& mv) override {
                typeName = "Movie";
                node = "    <movie director=\"" + xmlEscape(mv.getDirector()) +
                       "\" duration=\"" + std::to_string(mv.getDuration()) +
                       "\" studio=\"" + xmlEscape(mv.getStudio()) +
                       "\" rating=\"" + xmlEscape(mv.getRating()) +
                       "\" language=\"" + std::to_string(static_cast<int>(mv.getLanguage())) +
                       "\" country=\"" + xmlEscape(mv.getCountry()) +
                       "\" genre=\"" + std::to_string(static_cast<int>(mv.getGenre())) + "\"/>\n";
            }
            void visit(const Song& s) override {
                typeName = "Song";
                node = "    <song artist=\"" + xmlEscape(s.getArtist()) +
                       "\" album=\"" + xmlEscape(s.getAlbum()) +
                       "\" duration=\"" + std::to_string(s.getDuration()) +
                       "\" format=\"" + xmlEscape(s.getFormat()) +
                       "\" label=\"" + xmlEscape(s.getLabel()) +
                       "\" track=\"" + std::to_string(s.getTrackNumber()) +
                       "\" genre=\"" + std::to_string(static_cast<int>(s.getGenre())) + "\"/>\n";
            }
            void visit(const Magazine& mg) override {
                typeName = "Magazine";
                node = "    <magazine publisher=\"" + xmlEscape(mg.getPublisher()) +
                       "\" issue=\"" + std::to_string(mg.getIssueNumber()) +
                       "\" issn=\"" + xmlEscape(mg.getIssn()) +
                       "\" editor=\"" + xmlEscape(mg.getEditor()) +
                       "\" pages=\"" + std::to_string(mg.getPages()) +
                       "\" frequency=\"" + xmlEscape(mg.getFrequency()) +
                       "\" genre=\"" + std::to_string(static_cast<int>(mg.getGenre())) + "\"/>\n";
            }
            void visit(const Podcast& pc) override {
                typeName = "Podcast";
                node = "    <podcast host=\"" + xmlEscape(pc.getHost()) +
                       "\" episodes=\"" + std::to_string(pc.getEpisodeNumber()) +
                       "\" platform=\"" + xmlEscape(pc.getPlatform()) +
                       "\" duration=\"" + std::to_string(pc.getDuration()) +
                       "\" series=\"" + xmlEscape(pc.getSeries()) +
                       "\" description=\"" + xmlEscape(pc.getDescription()) +
                       "\" genre=\"" + std::to_string(static_cast<int>(pc.getGenre())) + "\"/>\n";
            }
        };

        XmlWriteVisitor v; m->accept(v);
        out << "  <media type=\"" << xmlEscape(v.typeName) << "\" id=\"" << m->getID() << "\">\n";
        out << "    <title>" << xmlEscape(m->getTitle()) << "</title>\n";
        out << "    <author>" << xmlEscape(m->getAuthor()) << "</author>\n";
        out << "    <releaseDate>" << xmlEscape(m->getReleaseDate().toString()) << "</releaseDate>\n";
        out << "    <size>" << m->getKbSize() << "</size>\n";
        out << "    <available>" << (m->getIsAvailable() ? "true" : "false") << "</available>\n";
        out << "    <imagePath>" << xmlEscape(m->getImagePath()) << "</imagePath>\n";
        out << v.node;
        out << "  </media>\n";
    }
    out << "</library>\n";
    return true;
}

bool XmlPersistence::load(Library& library, const std::string& filePath) const {
    QFile f(QString::fromStdString(filePath));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&f);

    library.clear();

    auto readText = [&]() -> QString { return xml.readElementText(QXmlStreamReader::ErrorOnUnexpectedElement); };

    while (!xml.atEnd()) {
        xml.readNext();
        if (!xml.isStartElement()) continue;
        if (xml.name() == QLatin1String("library")) {
            
            while (!xml.atEnd()) {
                xml.readNext();
                if (xml.isEndElement() && xml.name() == QLatin1String("library")) break;
                if (!xml.isStartElement()) continue;
                if (xml.name() == QLatin1String("media")) {
                    const QString type = xml.attributes().value("type").toString();
                    const unsigned id = xml.attributes().value("id").toUInt();

                    std::string title, author, imagePath;
                    Date releaseDate; unsigned sizeKb{}; bool available{};
                    QXmlStreamAttributes typeAttrs;

                    
                    while (!xml.atEnd()) {
                        xml.readNext();
                        if (xml.isEndElement() && xml.name() == QLatin1String("media")) break;
                        if (!xml.isStartElement()) continue;
                        const QString n = xml.name().toString();
                        if (n == QLatin1String("title")) { title = readText().toStdString(); }
                        else if (n == QLatin1String("author")) { author = readText().toStdString(); }
                        else if (n == QLatin1String("releaseDate")) { QString ds = readText(); Date::parseIso(ds.toStdString(), releaseDate); }
                        else if (n == QLatin1String("size")) { sizeKb = readText().toUInt(); }
                        else if (n == QLatin1String("available")) { available = readText().trimmed() == QLatin1String("true"); }
                        else if (n == QLatin1String("imagePath")) { imagePath = readText().toStdString(); }
                        else if (n == QLatin1String("book") || n == QLatin1String("movie") || n == QLatin1String("song") || n == QLatin1String("magazine") || n == QLatin1String("podcast")) {
                            typeAttrs = xml.attributes();
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }

                    
                    MediaFactory::Common c; c.title = title; c.author = author; c.id = id; c.sizeKb = sizeKb; c.available = available; c.imagePath = imagePath; c.releaseDatePtr = &releaseDate;
                    auto media = MediaFactory::fromXml(QString(type), c, typeAttrs);
                    if (media) library.addMedia(std::move(media));
                } else {
                    xml.skipCurrentElement();
                }
            }
        } else {
            xml.skipCurrentElement();
        }
    }

    return !xml.hasError();
}


