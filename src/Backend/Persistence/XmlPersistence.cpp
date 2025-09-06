#include "XmlPersistence.h"
#include "../Library/Library.h"
#include "../Elements/Book.h"
#include "../Elements/Movie.h"
#include "../Elements/Song.h"
#include "../Elements/Magazine.h"
#include "../Elements/Podcast.h"
#include "../Enums/Genres.h"
#include "../Enums/Languages.h"

#include <fstream>
#include <sstream>

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
    for (auto m : library.getAllMediaConst()) {
        std::string type = library.getMediaType(m);
        out << "  <media type=\"" << xmlEscape(type) << "\" id=\"" << m->getID() << "\">\n";
        out << "    <title>" << xmlEscape(m->getTitle()) << "</title>\n";
        out << "    <author>" << xmlEscape(m->getAuthor()) << "</author>\n";
        out << "    <releaseDate>" << xmlEscape(m->getReleaseDate().toString()) << "</releaseDate>\n";
        out << "    <size>" << m->getKbSize() << "</size>\n";
        out << "    <available>" << (m->getIsAvailable() ? "true" : "false") << "</available>\n";
        out << "    <imagePath>" << xmlEscape(m->getImagePath()) << "</imagePath>\n";

        if (auto b = dynamic_cast<const Book*>(m)) {
            out << "    <book publisher=\"" << xmlEscape(b->getPublisher()) << "\" pages=\"" << b->getPages() << "\" isbn=\"" << xmlEscape(b->getIsbn()) << "\" language=\"" << static_cast<int>(b->getLanguage()) << "\" genre=\"" << static_cast<int>(b->getGenre()) << "\"/>\n";
        } else if (auto mv = dynamic_cast<const Movie*>(m)) {
            out << "    <movie director=\"" << xmlEscape(mv->getDirector()) << "\" duration=\"" << mv->getDuration() << "\" studio=\"" << xmlEscape(mv->getStudio()) << "\" rating=\"" << xmlEscape(mv->getRating()) << "\" language=\"" << static_cast<int>(mv->getLanguage()) << "\" country=\"" << xmlEscape(mv->getCountry()) << "\" genre=\"" << static_cast<int>(mv->getGenre()) << "\"/>\n";
        } else if (auto s = dynamic_cast<const Song*>(m)) {
            out << "    <song artist=\"" << xmlEscape(s->getArtist()) << "\" album=\"" << xmlEscape(s->getAlbum()) << "\" duration=\"" << s->getDuration() << "\" format=\"" << xmlEscape(s->getFormat()) << "\" label=\"" << xmlEscape(s->getLabel()) << "\" track=\"" << s->getTrackNumber() << "\" genre=\"" << static_cast<int>(s->getGenre()) << "\"/>\n";
        } else if (auto mg = dynamic_cast<const Magazine*>(m)) {
            out << "    <magazine publisher=\"" << xmlEscape(mg->getPublisher()) << "\" issue=\"" << mg->getIssueNumber() << "\" issn=\"" << xmlEscape(mg->getIssn()) << "\" editor=\"" << xmlEscape(mg->getEditor()) << "\" pages=\"" << mg->getPages() << "\" frequency=\"" << xmlEscape(mg->getFrequency()) << "\" genre=\"" << static_cast<int>(mg->getGenre()) << "\"/>\n";
        } else if (auto pc = dynamic_cast<const Podcast*>(m)) {
            out << "    <podcast host=\"" << xmlEscape(pc->getHost()) << "\" episodes=\"" << pc->getEpisodeNumber() << "\" platform=\"" << xmlEscape(pc->getPlatform()) << "\" duration=\"" << pc->getDuration() << "\" series=\"" << xmlEscape(pc->getSeries()) << "\" description=\"" << xmlEscape(pc->getDescription()) << "\" genre=\"" << static_cast<int>(pc->getGenre()) << "\"/>\n";
        }
        out << "  </media>\n";
    }
    out << "</library>\n";
    return true;
}

bool XmlPersistence::load(Library& library, const std::string& filePath) const {
    std::ifstream in(filePath);
    if (!in.is_open()) return false;
    library.clear();
    // Minimal loader skipped for brevity: creating empty-attr objects like JSON loader
    // Minimal line-based parser for demo purposes
    std::string line;
    while (std::getline(in, line)) {
        if (line.find("<media") != std::string::npos) {
            auto getAttr = [&](const std::string& key) -> std::string {
                std::string k = key + "=\"";
                size_t p = line.find(k);
                if (p == std::string::npos) return {};
                size_t q1 = p + k.size();
                size_t q2 = line.find('"', q1);
                return line.substr(q1, q2 - q1);
            };
            std::string type = getAttr("type");
            std::string idStr = getAttr("id");
            unsigned id = idStr.empty() ? 0u : static_cast<unsigned>(std::stoi(idStr));

            // Read next lines until closing </media>
            std::string block = line + "\n";
            while (std::getline(in, line)) {
                block += line + "\n";
                if (line.find("</media>") != std::string::npos) break;
            }

            auto getTag = [&](const char* tag)->std::string{
                std::string open = std::string("<") + tag + ">";
                std::string close = std::string("</") + tag + ">";
                size_t p = block.find(open); if (p==std::string::npos) return {};
                size_t q = block.find(close, p); if (q==std::string::npos) return {};
                size_t s = p + open.size(); return block.substr(s, q - s);
            };

            std::string title = getTag("title");
            std::string author = getTag("author");
            std::string rdate = getTag("releaseDate");
            std::string sizeStr = getTag("size");
            std::string availStr = getTag("available");
            std::string imagePath = getTag("imagePath");

            unsigned sizeKb = sizeStr.empty()?0u:static_cast<unsigned>(std::stoi(sizeStr));
            bool available = availStr.find("true") != std::string::npos;
            Date releaseDate; Date::parseIso(rdate, releaseDate);

            std::unique_ptr<Media> media;
            if (type == "Book") {
                // Extract book attrs from singleton tag
                auto getAttrIn = [&](const std::string& t, const char* key)->std::string{
                    std::string k = std::string(key) + "=\"";
                    size_t p = t.find(k); if (p==std::string::npos) return {};
                    size_t s = p + k.size(); size_t e = t.find('"', s); return t.substr(s, e-s);
                };
                size_t p = block.find("<book "); size_t q = block.find("/>", p);
                std::string t = (p!=std::string::npos && q!=std::string::npos)? block.substr(p, q-p+2): std::string();
                auto book = std::make_unique<Book>(title, author,
                    static_cast<Enums::BookGenre>(std::stoi(getAttrIn(t, "genre").empty()?"0":getAttrIn(t, "genre"))), releaseDate,
                    id, sizeKb, available, imagePath,
                    getAttrIn(t, "publisher"), static_cast<unsigned>(std::stoi(getAttrIn(t, "pages").empty()?"0":getAttrIn(t, "pages"))), getAttrIn(t, "isbn"),
                    static_cast<Enums::Language>(std::stoi(getAttrIn(t, "language").empty()?"0":getAttrIn(t, "language"))));
                media = std::move(book);
            } else if (type == "Movie") {
                auto getAttrIn = [&](const std::string& t, const char* key)->std::string{ std::string k = std::string(key)+"=\""; size_t p=t.find(k); if(p==std::string::npos) return {}; size_t s=p+k.size(); size_t e=t.find('"',s); return t.substr(s,e-s); };
                size_t p = block.find("<movie "); size_t q = block.find("/>", p); std::string t = (p!=std::string::npos&&q!=std::string::npos)? block.substr(p,q-p+2): std::string();
                auto movie = std::make_unique<Movie>(title, author,
                    static_cast<Enums::MovieGenre>(std::stoi(getAttrIn(t, "genre").empty()?"0":getAttrIn(t, "genre"))), releaseDate, id, sizeKb, available, imagePath,
                    getAttrIn(t, "director"), static_cast<unsigned>(std::stoi(getAttrIn(t, "duration").empty()?"0":getAttrIn(t, "duration"))), getAttrIn(t, "studio"), getAttrIn(t, "rating"),
                    static_cast<Enums::Language>(std::stoi(getAttrIn(t, "language").empty()?"1":getAttrIn(t, "language"))), getAttrIn(t, "country"));
                media = std::move(movie);
            } else if (type == "Song") {
                auto getAttrIn = [&](const std::string& t, const char* key)->std::string{ std::string k = std::string(key)+"=\""; size_t p=t.find(k); if(p==std::string::npos) return {}; size_t s=p+k.size(); size_t e=t.find('"',s); return t.substr(s,e-s); };
                size_t p = block.find("<song "); size_t q = block.find("/>", p); std::string t = (p!=std::string::npos&&q!=std::string::npos)? block.substr(p,q-p+2): std::string();
                auto song = std::make_unique<Song>(title, author,
                    static_cast<Enums::MusicGenre>(std::stoi(getAttrIn(t, "genre").empty()?"0":getAttrIn(t, "genre"))), releaseDate, id, sizeKb, available, imagePath,
                    getAttrIn(t, "artist"), getAttrIn(t, "album"), static_cast<unsigned>(std::stoi(getAttrIn(t, "duration").empty()?"0":getAttrIn(t, "duration"))), getAttrIn(t, "format"), getAttrIn(t, "label"), static_cast<unsigned>(std::stoi(getAttrIn(t, "track").empty()?"0":getAttrIn(t, "track"))));
                media = std::move(song);
            } else if (type == "Magazine") {
                auto getAttrIn = [&](const std::string& t, const char* key)->std::string{ std::string k = std::string(key)+"=\""; size_t p=t.find(k); if(p==std::string::npos) return {}; size_t s=p+k.size(); size_t e=t.find('"',s); return t.substr(s,e-s); };
                size_t p = block.find("<magazine "); size_t q = block.find("/>", p); std::string t = (p!=std::string::npos&&q!=std::string::npos)? block.substr(p,q-p+2): std::string();
                auto magazine = std::make_unique<Magazine>(title, author,
                    static_cast<Enums::MagazineGenre>(std::stoi(getAttrIn(t, "genre").empty()?"0":getAttrIn(t, "genre"))), releaseDate, id, sizeKb, available, imagePath,
                    getAttrIn(t, "publisher"), static_cast<unsigned>(std::stoi(getAttrIn(t, "issue").empty()?"0":getAttrIn(t, "issue"))), getAttrIn(t, "issn"), getAttrIn(t, "editor"), static_cast<unsigned>(std::stoi(getAttrIn(t, "pages").empty()?"0":getAttrIn(t, "pages"))), getAttrIn(t, "frequency"));
                media = std::move(magazine);
            } else if (type == "Podcast") {
                auto getAttrIn = [&](const std::string& t, const char* key)->std::string{ std::string k = std::string(key)+"=\""; size_t p=t.find(k); if(p==std::string::npos) return {}; size_t s=p+k.size(); size_t e=t.find('"',s); return t.substr(s,e-s); };
                size_t p = block.find("<podcast "); size_t q = block.find("/>", p); std::string t = (p!=std::string::npos&&q!=std::string::npos)? block.substr(p,q-p+2): std::string();
                auto podcast = std::make_unique<Podcast>(title, author,
                    static_cast<Enums::PodcastGenre>(std::stoi(getAttrIn(t, "genre").empty()?"0":getAttrIn(t, "genre"))), releaseDate, id, sizeKb, available, imagePath,
                    getAttrIn(t, "host"), static_cast<unsigned>(std::stoi(getAttrIn(t, "episodes").empty()?"0":getAttrIn(t, "episodes"))), getAttrIn(t, "platform"), static_cast<unsigned>(std::stoi(getAttrIn(t, "duration").empty()?"0":getAttrIn(t, "duration"))), getAttrIn(t, "series"), getAttrIn(t, "description"));
                media = std::move(podcast);
            }
            if (media) library.addMedia(std::move(media));
        }
    }
    return true;
}


