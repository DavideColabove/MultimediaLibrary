#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"

class Podcast : public Media {
    private:
        std::string host;
        unsigned int episodeNumber;
        std::string platform; // Spotify, Apple Podcasts, etc.
        unsigned int duration; // in minutes
        std::string series;
        std::string description;
        Enums::PodcastGenre genre;
        
    public:
        // Constructors
        Podcast(std::string title, std::string author, Enums::PodcastGenre genre, Date releaseDate, 
               unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
               std::string host, unsigned int episodeNumber, std::string platform, unsigned int duration,
               std::string series, std::string description);
        Podcast(const Podcast& podcast);
        Podcast();
        virtual ~Podcast();

        // Virtual method implementations for non-trivial polymorphism
        virtual bool isValid() const override;

        // Podcast-specific getters and setters
        std::string getHost() const;
        Podcast& setHost(const std::string& h);
        unsigned int getEpisodeNumber() const;
        Podcast& setEpisodeNumber(unsigned int ep);
        std::string getPlatform() const;
        Podcast& setPlatform(const std::string& plat);
        unsigned int getDuration() const;
        Podcast& setDuration(unsigned int dur);
        std::string getSeries() const;
        Podcast& setSeries(const std::string& ser);
        std::string getDescription() const;
        Podcast& setDescription(const std::string& desc);
        
        // Genre-specific methods
        Enums::PodcastGenre getGenre() const;
        Podcast& setGenre(Enums::PodcastGenre genre);
        std::string getGenreString() const;
};

#endif // PODCAST_H
