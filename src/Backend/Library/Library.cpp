#include "Library.h"
#include "../Elements/Media.h"
#include "../Elements/Book.h"
#include "../Elements/Movie.h"
#include "../Elements/Song.h"
#include "../Elements/Magazine.h"
#include "../Elements/Podcast.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

Library::Library() : nextId(1)
{
}

void Library::addMedia(std::unique_ptr<Media> media)
{
    if (!media) return;
    
    // Assign the next available ID
    media->setID(getNextId());
    mediaCollection.push_back(std::move(media));
}

void Library::removeMedia(int id)
{
    auto it = std::find_if(mediaCollection.begin(), mediaCollection.end(),
        [id](const std::unique_ptr<Media>& media) {
            return media->getID() == id;
        });
    
    if (it != mediaCollection.end()) {
        mediaCollection.erase(it);
    }
}

Media* Library::findMediaById(int id)
{
    auto it = std::find_if(mediaCollection.begin(), mediaCollection.end(),
        [id](const std::unique_ptr<Media>& media) {
            return media->getID() == id;
        });
    
    return (it != mediaCollection.end()) ? it->get() : nullptr;
}

std::vector<Media*> Library::getAllMedia() const
{
    std::vector<Media*> result;
    result.reserve(mediaCollection.size());
    
    for (const auto& media : mediaCollection) {
        result.push_back(media.get());
    }
    
    return result;
}

std::vector<Media*> Library::searchByTitle(const std::string& title) const
{
    std::vector<Media*> result;
    
    for (const auto& media : mediaCollection) {
        std::string mediaTitle = media->getTitle();
        if (mediaTitle.find(title) != std::string::npos) {
            result.push_back(media.get());
        }
    }
    
    return result;
}

std::vector<Media*> Library::searchByAuthor(const std::string& author) const
{
    std::vector<Media*> result;
    
    for (const auto& media : mediaCollection) {
        std::string mediaAuthor = media->getAuthor();
        if (mediaAuthor.find(author) != std::string::npos) {
            result.push_back(media.get());
        }
    }
    
    return result;
}

std::vector<Media*> Library::filterByType(const std::string& type) const
{
    std::vector<Media*> result;
    
    for (const auto& media : mediaCollection) {
        if (getMediaType(media.get()) == type) {
            result.push_back(media.get());
        }
    }
    
    return result;
}

std::vector<Media*> Library::filterByAvailability(bool available) const
{
    std::vector<Media*> result;
    
    for (const auto& media : mediaCollection) {
        if (media->getIsAvailable() == available) {
            result.push_back(media.get());
        }
    }
    
    return result;
}

bool Library::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Write header
    file << "ID,Type,Title,Author,ReleaseDate,Size,Available";
    
    // Write specific fields for each type
    file << ",Publisher,Pages,ISBN,Language,Genre"; // Book fields
    file << ",Director,Duration,Rating"; // Movie fields
    file << ",Artist,Album"; // Song fields
    file << ",Issue"; // Magazine fields
    file << ",Host,Episodes"; // Podcast fields
    file << "\n";
    
    for (const auto& media : mediaCollection) {
        // Common fields
        file << media->getID() << ","
             << getMediaType(media.get()) << ","
             << media->getTitle() << ","
             << media->getAuthor() << ","
             << media->getReleaseDate().toString() << ","
             << media->getKbSize() << ","
             << (media->getIsAvailable() ? "1" : "0");
        
        // Type-specific fields
        if (auto book = dynamic_cast<const Book*>(media.get())) {
            file << "," << book->getPublisher()
                 << "," << book->getPages()
                 << "," << book->getIsbn()
                 << "," << static_cast<int>(book->getLanguage())
                 << "," << static_cast<int>(book->getGenre());
        } else {
            file << ",,,,,"; // Empty fields for non-books
        }
        
        if (auto movie = dynamic_cast<const Movie*>(media.get())) {
            file << "," << movie->getDirector()
                 << "," << movie->getDuration()
                 << "," << movie->getRating();
        } else {
            file << ",,,"; // Empty fields for non-movies
        }
        
        if (auto song = dynamic_cast<const Song*>(media.get())) {
            file << "," << song->getArtist()
                 << "," << song->getAlbum();
        } else {
            file << ",,"; // Empty fields for non-songs
        }
        
        if (auto magazine = dynamic_cast<const Magazine*>(media.get())) {
            file << "," << magazine->getIssueNumber();
        } else {
            file << ","; // Empty field for non-magazines
        }
        
        if (auto podcast = dynamic_cast<const Podcast*>(media.get())) {
            file << "," << podcast->getHost()
                 << "," << podcast->getEpisodeNumber();
        } else {
            file << ",,"; // Empty fields for non-podcasts
        }
        
        file << "\n";
    }
    
    file.close();
    return true;
}

bool Library::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Clear existing data
    clear();
    
    std::string line;
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() < 7) continue; // Skip invalid lines
        
        // Parse common fields
        int id = std::stoi(tokens[0]);
        std::string type = tokens[1];
        std::string title = tokens[2];
        std::string author = tokens[3];
        Date releaseDate; // TODO: Parse date from string
        int size = std::stoi(tokens[5]);
        bool available = (tokens[6] == "1");
        
        // Create media based on type
        std::unique_ptr<Media> media;
        
        if (type == "Book" && tokens.size() >= 12) {
            auto book = std::make_unique<Book>();
            book->setPublisher(tokens[7]);
            book->setPages(std::stoi(tokens[8]));
            book->setIsbn(tokens[9]);
            book->setLanguage(static_cast<Enums::Language>(std::stoi(tokens[10])));
            book->setGenre(static_cast<Enums::BookGenre>(std::stoi(tokens[11])));
            media = std::move(book);
        } else if (type == "Movie" && tokens.size() >= 15) {
            auto movie = std::make_unique<Movie>();
            movie->setDirector(tokens[12]);
            movie->setDuration(std::stoi(tokens[13]));
            movie->setRating(tokens[14]);
            media = std::move(movie);
        } else if (type == "Song" && tokens.size() >= 17) {
            auto song = std::make_unique<Song>();
            song->setArtist(tokens[15]);
            song->setAlbum(tokens[16]);
            media = std::move(song);
        } else if (type == "Magazine" && tokens.size() >= 18) {
            auto magazine = std::make_unique<Magazine>();
            magazine->setIssueNumber(std::stoi(tokens[17]));
            media = std::move(magazine);
        } else if (type == "Podcast" && tokens.size() >= 20) {
            auto podcast = std::make_unique<Podcast>();
            podcast->setHost(tokens[18]);
            podcast->setEpisodeNumber(std::stoi(tokens[19]));
            media = std::move(podcast);
        }
        
        if (media) {
            media->setID(id);
            media->setTitle(title);
            media->setAuthor(author);
            media->setReleaseDate(releaseDate);
            media->setKbSize(size);
            media->setIsAvailable(available);
            
            mediaCollection.push_back(std::move(media));
            nextId = std::max(nextId, static_cast<unsigned int>(id + 1));
        }
    }
    
    file.close();
    return true;
}

size_t Library::getTotalCount() const
{
    return mediaCollection.size();
}

size_t Library::getAvailableCount() const
{
    return std::count_if(mediaCollection.begin(), mediaCollection.end(),
        [](const std::unique_ptr<Media>& media) {
            return media->getIsAvailable();
        });
}

size_t Library::getCountByType(const std::string& type) const
{
    return std::count_if(mediaCollection.begin(), mediaCollection.end(),
        [this, &type](const std::unique_ptr<Media>& media) {
            return getMediaType(media.get()) == type;
        });
}

std::map<std::string, size_t> Library::getMediaTypeStats() const
{
    std::map<std::string, size_t> stats;
    
    for (const auto& media : mediaCollection) {
        std::string type = getMediaType(media.get());
        stats[type]++;
    }
    
    return stats;
}

int Library::getNextId()
{
    return nextId++;
}

void Library::clear()
{
    mediaCollection.clear();
    nextId = 1;
}

bool Library::isEmpty() const
{
    return mediaCollection.empty();
}

std::string Library::getMediaType(const Media* media) const
{
    if (dynamic_cast<const Book*>(media)) return "Book";
    if (dynamic_cast<const Movie*>(media)) return "Movie";
    if (dynamic_cast<const Song*>(media)) return "Song";
    if (dynamic_cast<const Magazine*>(media)) return "Magazine";
    if (dynamic_cast<const Podcast*>(media)) return "Podcast";
    return "Unknown";
}

void Library::generateNextId()
{
    if (mediaCollection.empty()) {
        nextId = 1;
    } else {
        unsigned int maxId = 0;
        for (const auto& media : mediaCollection) {
            maxId = std::max(maxId, static_cast<unsigned int>(media->getID()));
        }
        nextId = maxId + 1;
    }
}
