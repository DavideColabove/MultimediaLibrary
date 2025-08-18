#include "Library.h"
#include "../Persistence/JsonPersistence.h"
#include "../Persistence/XmlPersistence.h"
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
    
    media->setID(getNextId());
    mediaCollection.push_back(std::move(media));
}

void Library::removeMedia(int id)
{
    auto it = std::find_if(
        mediaCollection.begin(), mediaCollection.end(),
        [id](const std::unique_ptr<Media>& media) {
            return media->getID() == static_cast<unsigned int>(id);
        }
    );
    
    if (it != mediaCollection.end()) {
        mediaCollection.erase(it);
    }
}

Media* Library::findMediaById(int id)
{
    auto it = std::find_if(
        mediaCollection.begin(), mediaCollection.end(),
        [id](const std::unique_ptr<Media>& media) {
            return media->getID() == static_cast<unsigned int>(id);
        }
    );
    
    return (it != mediaCollection.end()) ? it->get() : nullptr;
}

const Media* Library::findMediaById(int id) const
{
    auto it = std::find_if(
        mediaCollection.begin(), mediaCollection.end(),
        [id](const std::unique_ptr<Media>& media) {
            return media->getID() == static_cast<unsigned int>(id);
        }
    );
    return (it != mediaCollection.end()) ? it->get() : nullptr;
}

// Removed non-const getAllMedia(); use getAllMediaConst()

std::vector<const Media*> Library::getAllMediaConst() const
{
    std::vector<const Media*> result;
    result.reserve(mediaCollection.size());
    for (const auto& media : mediaCollection) {
        result.push_back(media.get());
    }
    return result;
}

// Removed non-const searchByTitle(); use searchByTitleConst()

std::vector<const Media*> Library::searchByTitleConst(const std::string& title) const
{
    std::vector<const Media*> result;
    for (const auto& media : mediaCollection) {
        std::string mediaTitle = media->getTitle();
        if (mediaTitle.find(title) != std::string::npos) {
            result.push_back(media.get());
        }
    }
    return result;
}

// Removed non-const searchByAuthor(); use searchByAuthorConst()

std::vector<const Media*> Library::searchByAuthorConst(const std::string& author) const
{
    std::vector<const Media*> result;
    for (const auto& media : mediaCollection) {
        std::string mediaAuthor = media->getAuthor();
        if (mediaAuthor.find(author) != std::string::npos) {
            result.push_back(media.get());
        }
    }
    return result;
}

// Removed non-const filterByType(); use filterByTypeConst()

std::vector<const Media*> Library::filterByTypeConst(const std::string& type) const
{
    std::vector<const Media*> result;
    for (const auto& media : mediaCollection) {
        if (getMediaType(media.get()) == type) {
            result.push_back(media.get());
        }
    }
    return result;
}

// Removed non-const filterByAvailability(); use filterByAvailabilityConst()

std::vector<const Media*> Library::filterByAvailabilityConst(bool available) const
{
    std::vector<const Media*> result;
    for (const auto& media : mediaCollection) {
        if (media->getIsAvailable() == available) {
            result.push_back(media.get());
        }
    }
    return result;
}


bool Library::saveJson(const std::string& filePath) const
{
    JsonPersistence pers;
    return pers.save(*this, filePath);
}

bool Library::loadJson(const std::string& filePath)
{
    JsonPersistence pers;
    return pers.load(*this, filePath);
}

bool Library::saveXml(const std::string& filePath) const
{
    XmlPersistence pers;
    return pers.save(*this, filePath);
}

bool Library::loadXml(const std::string& filePath)
{
    XmlPersistence pers;
    return pers.load(*this, filePath);
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

// Use Visitor pattern to get media type without dynamic_cast
class TypeNameVisitor : public MediaVisitor {
public:
    std::string typeName;
    void visit(const Book&) override { typeName = "Book"; }
    void visit(const Movie&) override { typeName = "Movie"; }
    void visit(const Song&) override { typeName = "Song"; }
    void visit(const Magazine&) override { typeName = "Magazine"; }
    void visit(const Podcast&) override { typeName = "Podcast"; }
};

// Get media type using Visitor pattern instead of type checking
std::string Library::getMediaType(const Media* media) const
{
    if (!media) return "Unknown";
    TypeNameVisitor v;
    media->accept(v);
    return v.typeName.empty() ? std::string("Unknown") : v.typeName;
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
