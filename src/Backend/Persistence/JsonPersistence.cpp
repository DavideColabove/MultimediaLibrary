#include "JsonPersistence.h"
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
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace MinimalJson {

    static std::string escape(const std::string& s) {
        std::string out; out.reserve(s.size()+8);
        for (char c : s) {
            switch (c) {
                case '"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default: out += c; break;
            }
        }
        return out;
    }
}

bool JsonPersistence::save(const Library& library, const std::string& filePath) const {
    std::ofstream out(filePath);
    if (!out.is_open()) return false;

    out << "{\n  \"media\": [\n";
    const auto items = library.getAllMedia();
    for (size_t i = 0; i < items.size(); ++i) {
        const Media* m = items[i];
        
        class JsonWriteVisitor final : public MediaVisitor {
        public:
            std::string typeName;
            std::string extra; 
            void visit(const Book& b) override {
                typeName = "Book";
                extra  = ",\n      \"book\": {\n";
                extra += "        \"publisher\": \"" + MinimalJson::escape(b.getPublisher()) + "\",\n";
                extra += "        \"pages\": " + std::to_string(b.getPages()) + ",\n";
                extra += "        \"isbn\": \"" + MinimalJson::escape(b.getIsbn()) + "\",\n";
                extra += "        \"language\": " + std::to_string(static_cast<int>(b.getLanguage())) + ",\n";
                extra += "        \"genre\": " + std::to_string(static_cast<int>(b.getGenre())) + "\n      }";
            }
            void visit(const Movie& mv) override {
                typeName = "Movie";
                extra  = ",\n      \"movie\": {\n";
                extra += "        \"director\": \"" + MinimalJson::escape(mv.getDirector()) + "\",\n";
                extra += "        \"duration\": " + std::to_string(mv.getDuration()) + ",\n";
                extra += "        \"studio\": \"" + MinimalJson::escape(mv.getStudio()) + "\",\n";
                extra += "        \"rating\": \"" + MinimalJson::escape(mv.getRating()) + "\",\n";
                extra += "        \"language\": " + std::to_string(static_cast<int>(mv.getLanguage())) + ",\n";
                extra += "        \"country\": \"" + MinimalJson::escape(mv.getCountry()) + "\",\n";
                extra += "        \"genre\": " + std::to_string(static_cast<int>(mv.getGenre())) + "\n      }";
            }
            void visit(const Song& s) override {
                typeName = "Song";
                extra  = ",\n      \"song\": {\n";
                extra += "        \"artist\": \"" + MinimalJson::escape(s.getArtist()) + "\",\n";
                extra += "        \"album\": \"" + MinimalJson::escape(s.getAlbum()) + "\",\n";
                extra += "        \"duration\": " + std::to_string(s.getDuration()) + ",\n";
                extra += "        \"format\": \"" + MinimalJson::escape(s.getFormat()) + "\",\n";
                extra += "        \"label\": \"" + MinimalJson::escape(s.getLabel()) + "\",\n";
                extra += "        \"track\": " + std::to_string(s.getTrackNumber()) + ",\n";
                extra += "        \"genre\": " + std::to_string(static_cast<int>(s.getGenre())) + "\n      }";
            }
            void visit(const Magazine& mg) override {
                typeName = "Magazine";
                extra  = ",\n      \"magazine\": {\n";
                extra += "        \"publisher\": \"" + MinimalJson::escape(mg.getPublisher()) + "\",\n";
                extra += "        \"issue\": " + std::to_string(mg.getIssueNumber()) + ",\n";
                extra += "        \"issn\": \"" + MinimalJson::escape(mg.getIssn()) + "\",\n";
                extra += "        \"editor\": \"" + MinimalJson::escape(mg.getEditor()) + "\",\n";
                extra += "        \"pages\": " + std::to_string(mg.getPages()) + ",\n";
                extra += "        \"frequency\": \"" + MinimalJson::escape(mg.getFrequency()) + "\",\n";
                extra += "        \"genre\": " + std::to_string(static_cast<int>(mg.getGenre())) + "\n      }";
            }
            void visit(const Podcast& pc) override {
                typeName = "Podcast";
                extra  = ",\n      \"podcast\": {\n";
                extra += "        \"host\": \"" + MinimalJson::escape(pc.getHost()) + "\",\n";
                extra += "        \"episodes\": " + std::to_string(pc.getEpisodeNumber()) + ",\n";
                extra += "        \"platform\": \"" + MinimalJson::escape(pc.getPlatform()) + "\",\n";
                extra += "        \"duration\": " + std::to_string(pc.getDuration()) + ",\n";
                extra += "        \"series\": \"" + MinimalJson::escape(pc.getSeries()) + "\",\n";
                extra += "        \"description\": \"" + MinimalJson::escape(pc.getDescription()) + "\",\n";
                extra += "        \"genre\": " + std::to_string(static_cast<int>(pc.getGenre())) + "\n      }";
            }
        };

        JsonWriteVisitor v; m->accept(v);
        out << "    {\n";
        out << "      \"type\": \"" << MinimalJson::escape(v.typeName) << "\",\n";
        out << "      \"id\": " << m->getID() << ",\n";
        out << "      \"title\": \"" << MinimalJson::escape(m->getTitle()) << "\",\n";
        out << "      \"author\": \"" << MinimalJson::escape(m->getAuthor()) << "\",\n";
        out << "      \"releaseDate\": \"" << MinimalJson::escape(m->getReleaseDate().toString()) << "\",\n";
        out << "      \"size\": " << m->getKbSize() << ",\n";
        out << "      \"available\": " << (m->getIsAvailable() ? "true" : "false") << ",\n";
        out << "      \"imagePath\": \"" << MinimalJson::escape(m->getImagePath()) << "\"";
        
        out << v.extra;

        out << "\n    }" << (i + 1 < items.size() ? "," : "") << "\n";
    }
    out << "  ]\n}\n";
    return true;
}



bool JsonPersistence::load(Library& library, const std::string& filePath) const {
    QFile f(QString::fromStdString(filePath));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    const QByteArray data = f.readAll();
    f.close();

    QJsonParseError pe;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &pe);
    if (pe.error != QJsonParseError::NoError || !doc.isObject()) return false;

    const QJsonObject root = doc.object();
    const QJsonValue mediaVal = root.value("media");
    if (!mediaVal.isArray()) return false;

    library.clear();
    const QJsonArray arr = mediaVal.toArray();
    for (const QJsonValue& v : arr) {
        if (!v.isObject()) continue;
        const QJsonObject o = v.toObject();
        const QString type = o.value("type").toString();

    MediaFactory::Common c;
    c.title = o.value("title").toString().toStdString();
    c.author = o.value("author").toString().toStdString();
    c.id = static_cast<unsigned>(o.value("id").toInt());
    c.sizeKb = static_cast<unsigned>(o.value("size").toInt());
    c.available = o.value("available").toBool();
    c.imagePath = o.value("imagePath").toString().toStdString();
    const QString dateStr = o.value("releaseDate").toString();
    Date releaseDate; Date::parseIso(dateStr.toStdString(), releaseDate);
    c.releaseDatePtr = &releaseDate;

    auto media = MediaFactory::fromJson(type, c, o);
        if (media) library.addMedia(std::move(media));
    }
    return true;
}


