#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"


class Podcast : public Media {
    private:
        std::string host;           
        unsigned int episodeNumber; 
        std::string platform;       
        unsigned int duration;      
        std::string series;         
        std::string description;    
        Enums::PodcastGenre genre;  
        
    public:
        
        Podcast(std::string title, std::string author, Enums::PodcastGenre genre, Date releaseDate, 
               unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
               std::string host, unsigned int episodeNumber, std::string platform, unsigned int duration,
               std::string series, std::string description);
        
        
        Podcast(const Podcast& podcast);
        
        
        Podcast();
        
        
        virtual ~Podcast();

        
        virtual bool isValid() const override;
        
        
        virtual void accept(MediaVisitor& visitor) const override;

        
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
        
        
        Enums::PodcastGenre getGenre() const;
        Podcast& setGenre(Enums::PodcastGenre genre);
        std::string getGenreString() const;
};

#endif 
