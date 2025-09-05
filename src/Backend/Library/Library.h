#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>


class Media;
class Book;
class Movie;
class Song;
class Magazine;
class Podcast;
class IPersistence;


class Library
{
public:
    
    Library();
    
    
    ~Library() = default;

    
    void addMedia(std::unique_ptr<Media> media);
    
    
    void removeMedia(int id);
    
    
    Media* findMediaById(int id);
    
    
    std::vector<Media*> getAllMedia() const;
    
    
    std::vector<Media*> searchByTitle(const std::string& title) const;
    
    
    std::vector<Media*> searchByAuthor(const std::string& author) const;
    
    
    std::vector<Media*> filterByType(const std::string& type) const;
    
    
    std::vector<Media*> filterByAvailability(bool available) const;

    
    bool saveJson(const std::string& filePath) const;
    
    
    bool loadJson(const std::string& filePath);
    
    
    bool saveXml(const std::string& filePath) const;
    
    
    bool loadXml(const std::string& filePath);
    
    
    size_t getTotalCount() const;
    
    
    size_t getAvailableCount() const;
    
    
    size_t getCountByType(const std::string& type) const;
    
    
    std::map<std::string, size_t> getMediaTypeStats() const;
    
    
    int getNextId();
    
    
    void clear();
    
    
    bool isEmpty() const;
    
    
    std::string getMediaType(const Media* media) const;

private:
    std::vector<std::unique_ptr<Media>> mediaCollection;  
    unsigned int nextId;                                   
    
    
    void generateNextId();
};

#endif 
