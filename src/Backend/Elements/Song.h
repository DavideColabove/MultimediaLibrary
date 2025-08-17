#ifndef SONG_H
#define SONG_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"

/**
 * @brief Concrete media class representing a music track or song
 * 
 * This class extends the Media base class to represent songs with specific
 * musical metadata such as artist, album, duration, audio format, record
 * label, track number, and musical genre. It implements song-specific
 * validation rules and provides methods for accessing and modifying
 * song attributes.
 */
class Song : public Media {
    private:
        std::string artist;         // Performing artist or band
        std::string album;          // Album the song belongs to
        unsigned int duration;      // Track duration in seconds
        std::string format;         // Audio format (MP3, FLAC, WAV, etc.)
        std::string label;          // Record label or distribution company
        unsigned int trackNumber;   // Position of track within the album
        Enums::MusicGenre genre;    // Musical genre classification
        
    public:
        /**
         * @brief Constructs a Song with all required attributes
         * @param title Song title
         * @param author Composer or songwriter
         * @param genre Musical genre
         * @param releaseDate Release date
         * @param id Unique identifier
         * @param kbSize File size in kilobytes
         * @param isAvailable Availability status
         * @param imagePath Path to album art
         * @param artist Performing artist
         * @param album Album name
         * @param duration Track length in seconds
         * @param format Audio format
         * @param label Record label
         * @param trackNumber Track position in album
         */
        Song(std::string title, std::string author, Enums::MusicGenre genre, Date releaseDate, 
             unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
             std::string artist, std::string album, unsigned int duration, std::string format,
             std::string label, unsigned int trackNumber);
        
        /**
         * @brief Copy constructor
         * @param song Song object to copy from
         */
        Song(const Song& song);
        
        /**
         * @brief Default constructor
         */
        Song();
        
        /**
         * @brief Virtual destructor
         */
        virtual ~Song();

        /**
         * @brief Validates song-specific attributes
         * 
         * Ensures that the song has valid musical information:
         * - Title and artist are not empty
         * - Duration is positive
         * - Audio format is specified
         * - Record label is provided
         * - Track number is valid
         * 
         * @return true if all song attributes are valid
         */
        virtual bool isValid() const override;
        
        /**
         * @brief Accepts a visitor for type-safe operations
         * @param visitor The visitor object to accept
         */
        virtual void accept(MediaVisitor& visitor) const override;

        // Song-specific attribute accessors
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
        
        // Genre management methods
        Enums::MusicGenre getGenre() const;
        Song& setGenre(Enums::MusicGenre genre);
        std::string getGenreString() const;
};

#endif // SONG_H
