#include "JsonPersistence.h"
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
#include <filesystem>

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
    const auto items = library.getAllMediaConst();
    for (size_t i = 0; i < items.size(); ++i) {
        const Media* m = items[i];
        std::string type = library.getMediaType(m);
        out << "    {\n";
        out << "      \"type\": \"" << MinimalJson::escape(type) << "\",\n";
        out << "      \"id\": " << m->getID() << ",\n";
        out << "      \"title\": \"" << MinimalJson::escape(m->getTitle()) << "\",\n";
        out << "      \"author\": \"" << MinimalJson::escape(m->getAuthor()) << "\",\n";
        out << "      \"releaseDate\": \"" << MinimalJson::escape(m->getReleaseDate().toString()) << "\",\n";
        out << "      \"size\": " << m->getKbSize() << ",\n";
        out << "      \"available\": " << (m->getIsAvailable() ? "true" : "false") << ",\n";
        std::string storedImagePath = m->getImagePath();
        try {
            namespace fs = std::filesystem;
            fs::path baseDir = fs::path(filePath).parent_path();
            fs::path imgPath = fs::path(storedImagePath);
            if (imgPath.is_absolute()) {
                fs::path rel = fs::relative(imgPath, baseDir);
                storedImagePath = rel.generic_string();
            } else {
                storedImagePath = imgPath.generic_string();
            }
        } catch (...) {
        }
        out << "      \"imagePath\": \"" << MinimalJson::escape(storedImagePath) << "\"";

        struct JsonDetailsVisitor : MediaVisitor {
            std::ostream& out;
            JsonDetailsVisitor(std::ostream& o) : out(o) {}
            void visit(const Book& b) override {
                out << ",\n      \"book\": {\n";
                out << "        \"publisher\": \"" << MinimalJson::escape(b.getPublisher()) << "\",\n";
                out << "        \"pages\": " << b.getPages() << ",\n";
                out << "        \"isbn\": \"" << MinimalJson::escape(b.getIsbn()) << "\",\n";
                out << "        \"language\": " << static_cast<int>(b.getLanguage()) << ",\n";
                out << "        \"genre\": " << static_cast<int>(b.getGenre()) << "\n";
                out << "      }";
            }
            void visit(const Movie& mv) override {
                out << ",\n      \"movie\": {\n";
                out << "        \"director\": \"" << MinimalJson::escape(mv.getDirector()) << "\",\n";
                out << "        \"duration\": " << mv.getDuration() << ",\n";
                out << "        \"studio\": \"" << MinimalJson::escape(mv.getStudio()) << "\",\n";
                out << "        \"rating\": \"" << MinimalJson::escape(mv.getRating()) << "\",\n";
                out << "        \"language\": " << static_cast<int>(mv.getLanguage()) << ",\n";
                out << "        \"country\": \"" << MinimalJson::escape(mv.getCountry()) << "\",\n";
                out << "        \"genre\": " << static_cast<int>(mv.getGenre()) << "\n";
                out << "      }";
            }
            void visit(const Song& s) override {
                out << ",\n      \"song\": {\n";
                out << "        \"artist\": \"" << MinimalJson::escape(s.getArtist()) << "\",\n";
                out << "        \"album\": \"" << MinimalJson::escape(s.getAlbum()) << "\",\n";
                out << "        \"duration\": " << s.getDuration() << ",\n";
                out << "        \"format\": \"" << MinimalJson::escape(s.getFormat()) << "\",\n";
                out << "        \"label\": \"" << MinimalJson::escape(s.getLabel()) << "\",\n";
                out << "        \"track\": " << s.getTrackNumber() << ",\n";
                out << "        \"genre\": " << static_cast<int>(s.getGenre()) << "\n";
                out << "      }";
            }
            void visit(const Magazine& mg) override {
                out << ",\n      \"magazine\": {\n";
                out << "        \"publisher\": \"" << MinimalJson::escape(mg.getPublisher()) << "\",\n";
                out << "        \"issue\": " << mg.getIssueNumber() << ",\n";
                out << "        \"issn\": \"" << MinimalJson::escape(mg.getIssn()) << "\",\n";
                out << "        \"editor\": \"" << MinimalJson::escape(mg.getEditor()) << "\",\n";
                out << "        \"pages\": " << mg.getPages() << ",\n";
                out << "        \"frequency\": \"" << MinimalJson::escape(mg.getFrequency()) << "\",\n";
                out << "        \"genre\": " << static_cast<int>(mg.getGenre()) << "\n";
                out << "      }";
            }
            void visit(const Podcast& pc) override {
                out << ",\n      \"podcast\": {\n";
                out << "        \"host\": \"" << MinimalJson::escape(pc.getHost()) << "\",\n";
                out << "        \"episodes\": " << pc.getEpisodeNumber() << ",\n";
                out << "        \"platform\": \"" << MinimalJson::escape(pc.getPlatform()) << "\",\n";
                out << "        \"duration\": " << pc.getDuration() << ",\n";
                out << "        \"series\": \"" << MinimalJson::escape(pc.getSeries()) << "\",\n";
                out << "        \"description\": \"" << MinimalJson::escape(pc.getDescription()) << "\",\n";
                out << "        \"genre\": " << static_cast<int>(pc.getGenre()) << "\n";
                out << "      }";
            }
        } detailsVisitor(out);

        m->accept(detailsVisitor);

        out << "\n    }" << (i + 1 < items.size() ? "," : "") << "\n";
    }
    out << "  ]\n}\n";
    return true;
}

bool JsonPersistence::load(Library& library, const std::string& filePath) const {
    std::ifstream in(filePath);
    if (!in.is_open()) return false;
    library.clear();

    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    size_t pos = 0;
    while ((pos = content.find("\"type\"", pos)) != std::string::npos) {
        size_t start = content.rfind('{', pos);
        size_t end = content.find('}', pos);
        if (start == std::string::npos || end == std::string::npos) break;
        std::string obj = content.substr(start, end - start + 1);

        auto getStr = [&](const char* key) -> std::string {
            std::string k = std::string("\"") + key + "\"";
            size_t p = obj.find(k);
            if (p == std::string::npos) return {};
            size_t colon = obj.find(':', p);
            size_t q1 = obj.find('"', colon + 1);
            size_t q2 = obj.find('"', q1 + 1);
            if (q1 == std::string::npos || q2 == std::string::npos) return {};
            return obj.substr(q1 + 1, q2 - q1 - 1);
        };
        
        auto getInt = [&](const char* key, int def = 0) -> int {
            std::string k = std::string("\"") + key + "\"";
            size_t p = obj.find(k);
            if (p == std::string::npos) return def;
            size_t colon = obj.find(':', p);
            size_t comma = obj.find_first_of(",}\n", colon + 1);
            std::string num = obj.substr(colon + 1, comma - (colon + 1));
            num.erase(0, num.find_first_not_of(" \t\n\r"));
            num.erase(num.find_last_not_of(" \t\n\r") + 1);
            try { return std::stoi(num); } catch (...) { return def; }
        };
        
        auto getBool = [&](const char* key, bool def = false) -> bool {
            std::string k = std::string("\"") + key + "\"";
            size_t p = obj.find(k);
            if (p == std::string::npos) return def;
            size_t colon = obj.find(':', p);
            size_t comma = obj.find_first_of(",}\n", colon + 1);
            std::string val = obj.substr(colon + 1, comma - (colon + 1));
            return val.find("true") != std::string::npos;
        };

        std::string type = getStr("type");
        std::string title = getStr("title");
        std::string author = getStr("author");
        std::string imagePath = getStr("imagePath");
        try {
            namespace fs = std::filesystem;
            fs::path imgPath = fs::path(imagePath);
            if (!imgPath.is_absolute()) {
                fs::path baseDir = fs::path(filePath).parent_path();
                fs::path candidate = fs::weakly_canonical(baseDir / imgPath);
                if (fs::exists(candidate)) {
                    imagePath = candidate.generic_string();
                } 
            } else {
                if (!std::filesystem::exists(imgPath)) { 
                    // caso cover NON trovata: UI mostra placeholder di default
                    }
        } catch (...) {}
        unsigned id = static_cast<unsigned>(getInt("id"));
        unsigned sizeKb = static_cast<unsigned>(getInt("size"));
        bool available = getBool("available");
        
        Date releaseDate; 
        std::string dateStr = getStr("releaseDate");
        Date::parseIso(dateStr, releaseDate); 

        auto findSection = [&](const char* key) -> std::string {
            std::string k = std::string("\"") + key + "\"";
            size_t p = obj.find(k);
            if (p == std::string::npos) return {};
            size_t brace = obj.find('{', p);
            if (brace == std::string::npos) return {};
            int depth = 0;
            for (size_t i = brace; i < obj.size(); ++i) {
                if (obj[i] == '{') depth++; else if (obj[i] == '}') { depth--; if (depth==0) return obj.substr(brace, i-brace+1); }
            }
            return {};
        };
        
        auto getStrIn = [&](const std::string& sec, const char* key)->std::string{
            std::string k = std::string("\"") + key + "\"";
            size_t p = sec.find(k);
            if (p==std::string::npos) return {};
            size_t c = sec.find(':', p);
            size_t q1 = sec.find('"', c+1);
            size_t q2 = (q1==std::string::npos) ? std::string::npos : sec.find('"', q1+1);
            if (q1==std::string::npos || q2==std::string::npos) return {};
            return sec.substr(q1+1, q2-q1-1);
        };
        
        auto getIntIn = [&](const std::string& sec, const char* key, int def=0)->int{
            std::string k = std::string("\"") + key + "\"";
            size_t p = sec.find(k); if (p==std::string::npos) return def;
            size_t c = sec.find(':', p); size_t comma = sec.find_first_of(",}\n", c+1);
            std::string num = sec.substr(c+1, comma-(c+1));
            num.erase(0, num.find_first_not_of(" \t\n\r"));
            num.erase(num.find_last_not_of(" \t\n\r") + 1);
            try { return std::stoi(num); } catch (...) { return def; }
        };

        std::unique_ptr<Media> media;
        if (type == "Book") {
            std::string sec = findSection("book");
            auto book = std::make_unique<Book>(title, author,
                static_cast<Enums::BookGenre>(getIntIn(sec, "genre", 0)), releaseDate, id, sizeKb, available, imagePath,
                getStrIn(sec, "publisher"), static_cast<unsigned>(getIntIn(sec, "pages", 0)), getStrIn(sec, "isbn"),
                static_cast<Enums::Language>(getIntIn(sec, "language", 0)));
            media = std::move(book);
        } else if (type == "Movie") {
            std::string sec = findSection("movie");
            auto movie = std::make_unique<Movie>(title, author,
                static_cast<Enums::MovieGenre>(getIntIn(sec, "genre", 0)), releaseDate, id, sizeKb, available, imagePath,
                getStrIn(sec, "director"), static_cast<unsigned>(getIntIn(sec, "duration", 0)), getStrIn(sec, "studio"), getStrIn(sec, "rating"),
                static_cast<Enums::Language>(getIntIn(sec, "language", 1)), getStrIn(sec, "country"));
            media = std::move(movie);
        } else if (type == "Song") {
            std::string sec = findSection("song");
            auto song = std::make_unique<Song>(title, author,
                static_cast<Enums::MusicGenre>(getIntIn(sec, "genre", 0)), releaseDate, id, sizeKb, available, imagePath,
                getStrIn(sec, "artist"), getStrIn(sec, "album"), static_cast<unsigned>(getIntIn(sec, "duration", 0)), getStrIn(sec, "format"), getStrIn(sec, "label"), static_cast<unsigned>(getIntIn(sec, "track", 0)));
            media = std::move(song);
        } else if (type == "Magazine") {
            std::string sec = findSection("magazine");
            auto magazine = std::make_unique<Magazine>(title, author,
                static_cast<Enums::MagazineGenre>(getIntIn(sec, "genre", 0)), releaseDate, id, sizeKb, available, imagePath,
                getStrIn(sec, "publisher"), static_cast<unsigned>(getIntIn(sec, "issue", 0)), getStrIn(sec, "issn"), getStrIn(sec, "editor"), static_cast<unsigned>(getIntIn(sec, "pages", 0)), getStrIn(sec, "frequency"));
            media = std::move(magazine);
        } else if (type == "Podcast") {
            std::string sec = findSection("podcast");
            auto podcast = std::make_unique<Podcast>(title, author,
                static_cast<Enums::PodcastGenre>(getIntIn(sec, "genre", 0)), releaseDate, id, sizeKb, available, imagePath,
                getStrIn(sec, "host"), static_cast<unsigned>(getIntIn(sec, "episodes", 0)), getStrIn(sec, "platform"), static_cast<unsigned>(getIntIn(sec, "duration", 0)), getStrIn(sec, "series"), getStrIn(sec, "description"));
            media = std::move(podcast);
        }
        if (media) library.addMedia(std::move(media));
        pos = end + 1;
    }
    return true;
}


