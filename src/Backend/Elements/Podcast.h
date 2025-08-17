#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"
#include <string>
#include "../Enums/Genres.h"

/**
 * @brief Concrete media class representing a podcast episode
 * 
 * This class extends the Media base class to represent podcast episodes with specific
 * podcast metadata such as host, episode number, platform, duration, series name,
 * description, and podcast genre. It implements podcast-specific validation rules
 * and provides methods for accessing and modifying podcast attributes.
 */
class Podcast : public Media {
    private:
        std::string host;           // Podcast host or presenter
        unsigned int episodeNumber; // Sequential episode number
        std::string platform;       // Distribution platform (Spotify, Apple Podcasts, etc.)
        unsigned int duration;      // Episode duration in minutes
        std::string series;         // Podcast series name
        std::string description;    // Episode description or summary
        Enums::PodcastGenre genre;  // Podcast category or genre
        
    public:
        /**
         * @brief Constructs a Podcast with all required attributes
         * @param title Episode title
         * @param author Episode creator or contributor
         * @param genre Podcast genre
         * @param releaseDate Release date
         * @param id Unique identifier
         * @param kbSize File size in kilobytes
         * @param isAvailable Availability status
         * @param imagePath Path to episode artwork
         * @param host Podcast host
         * @param episodeNumber Episode number
         * @param platform Distribution platform
         * @param duration Episode length in minutes
         * @param series Podcast series name
         * @param description Episode description
         */
        Podcast(std::string title, std::string author, Enums::PodcastGenre genre, Date releaseDate, 
               unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
               std::string host, unsigned int episodeNumber, std::string platform, unsigned int duration,
               std::string series, std::string description);
        
        /**
         * @brief Copy constructor
         * @param podcast Podcast object to copy from
         */
        Podcast(const Podcast& podcast);
        
        /**
         * @brief Default constructor
         */
        Podcast();
        
        /**
         * @brief Virtual destructor
         */
        virtual ~Podcast();

        /**
         * @brief Validates podcast-specific attributes
         * 
         * Ensures that the podcast has valid episode information:
         * - Title and host are not empty
         * - Episode number is positive
         * - Platform is specified
         * - Duration is positive
         * - Series name is provided
         * - Description is available
         * 
         * @return true if all podcast attributes are valid
         */
        virtual bool isValid() const override;
        
        /**
         * @brief Accepts a visitor for type-safe operations
         * @param visitor The visitor object to accept
         */
        virtual void accept(MediaVisitor& visitor) const override;

        // Podcast-specific attribute accessors
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
        
        // Genre management methods
        Enums::PodcastGenre getGenre() const;
        Podcast& setGenre(Enums::PodcastGenre genre);
        std::string getGenreString() const;
};

#endif // PODCAST_H
