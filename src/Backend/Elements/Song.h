#ifndef SONG_H
#define SONG_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"


class Song : public Media {
    private:
        std::string artist;         
        std::string album;          
        unsigned int duration;      
        std::string format;         
        std::string label;          
        unsigned int trackNumber;   
        Enums::MusicGenre genre;    
        
    public:
        
        Song(std::string title, std::string author, Enums::MusicGenre genre, Date releaseDate, 
             unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
             std::string artist, std::string album, unsigned int duration, std::string format,
             std::string label, unsigned int trackNumber);
        
        
        Song(const Song& song);
        
        
        Song();
        
        
        virtual ~Song();

        
        virtual bool isValid() const override;
        
        
        virtual void accept(MediaVisitor& visitor) const override;

        
        std::string getArtist() const;
        Song& setArtist(const std::string& art);
        std::string getAlbum() const;
        Song& setAlbum(const std::string& alb);
        unsigned int getDuration() const;
        Song& setDuration(unsigned int dur);
        std::string getFormat() const;
        Song& setFormat(const std::string& fmt);
        std::string getLabel() const;
        Song& setLabel(const std::string& lab);
        unsigned int getTrackNumber() const;
        Song& setTrackNumber(unsigned int track);
        
        
        Enums::MusicGenre getGenre() const;
        Song& setGenre(Enums::MusicGenre genre);
        std::string getGenreString() const;
};

#endif 
