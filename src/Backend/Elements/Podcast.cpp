#include "Podcast.h"
#include <sstream>
#include "../Enums/Genres.h"

Podcast::Podcast(std::string title, std::string author, Enums::PodcastGenre genre, Date releaseDate, 
                 unsigned int id, unsigned int kbSize, bool isAvailable, std::string imagePath,
                 std::string host, unsigned int episodeNumber, std::string platform, unsigned int duration,
                 std::string series, std::string description)
    : Media(title, author, releaseDate, id, kbSize, isAvailable, imagePath),
      host(host), episodeNumber(episodeNumber), platform(platform), duration(duration), 
      series(series), description(description), genre(genre) {}

Podcast::Podcast(const Podcast& podcast) 
    : Media(podcast), host(podcast.host), episodeNumber(podcast.episodeNumber), platform(podcast.platform), 
      duration(podcast.duration), series(podcast.series), description(podcast.description), genre(podcast.genre) {}

Podcast::Podcast() : Media(), host(""), episodeNumber(0), platform(""), duration(0), series(""), description(""), genre(Enums::PodcastGenre::EDUCATION) {}

Podcast::~Podcast() {}

bool Podcast::isValid() const {
    return !getTitle().empty() && !host.empty() && episodeNumber > 0 && 
           !platform.empty() && duration > 0 && !series.empty() && !description.empty();
}

std::string Podcast::getHost() const {
    return host;
}

Podcast& Podcast::setHost(const std::string& h) {
    host = h;
    return *this;
}

unsigned int Podcast::getEpisodeNumber() const {
    return episodeNumber;
}

Podcast& Podcast::setEpisodeNumber(unsigned int ep) {
    episodeNumber = ep;
    return *this;
}

std::string Podcast::getPlatform() const {
    return platform;
}

Podcast& Podcast::setPlatform(const std::string& plat) {
    platform = plat;
    return *this;
}

unsigned int Podcast::getDuration() const {
    return duration;
}

Podcast& Podcast::setDuration(unsigned int dur) {
    duration = dur;
    return *this;
}

std::string Podcast::getSeries() const {
    return series;
}

Podcast& Podcast::setSeries(const std::string& ser) {
    series = ser;
    return *this;
}

std::string Podcast::getDescription() const {
    return description;
}

Podcast& Podcast::setDescription(const std::string& desc) {
    description = desc;
    return *this;
}

Enums::PodcastGenre Podcast::getGenre() const {
    return genre;
}

Podcast& Podcast::setGenre(Enums::PodcastGenre g) {
    genre = g;
    return *this;
}

std::string Podcast::getGenreString() const {
    return Enums::podcastGenreToString(genre);
}

void Podcast::accept(MediaVisitor& visitor) const {
    visitor.visit(*this);
}

