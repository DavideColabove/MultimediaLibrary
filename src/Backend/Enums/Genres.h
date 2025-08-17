#ifndef GENRES_H
#define GENRES_H

#include <string>
#include <vector>

/**
 * @brief Namespace containing genre enumerations and utility functions
 * 
 * This namespace provides strongly-typed enumerations for different media genres
 * across all media types (books, movies, songs, magazines, podcasts). It includes
 * conversion functions between enum values and string representations, as well as
 * helper functions for frontend integration.
 */
namespace Enums {
    /**
     * @brief Enumeration of musical genres
     * 
     * Defines the available genres for music tracks and songs,
     * covering a wide range of musical styles and traditions.
     */
    enum class MusicGenre {
        ROCK,           // Rock music
        POP,            // Popular music
        JAZZ,           // Jazz music
        CLASSICAL,      // Classical music
        HIP_HOP,        // Hip-hop and rap
        ELECTRONIC,     // Electronic music
        COUNTRY,        // Country music
        FOLK,           // Folk music
        BLUES,          // Blues music
        REGGAE,         // Reggae music
        METAL,          // Heavy metal
        PUNK,           // Punk rock
        INDIE,          // Independent music
        RAP,            // Rap music
        SOUL,           // Soul music
        FUNK,           // Funk music
        DISCO,          // Disco music
        GOSPEL,         // Gospel music
        LATIN,          // Latin music
        WORLD_MUSIC     // World music
    };

    /**
     * @brief Enumeration of book genres
     * 
     * Defines the available genres for books and literature,
     * covering fiction, non-fiction, and specialized categories.
     */
    enum class BookGenre {
        FICTION,            // General fiction
        NON_FICTION,        // Non-fiction works
        MYSTERY,            // Mystery novels
        THRILLER,           // Thriller novels
        ROMANCE,            // Romance novels
        SCIENCE_FICTION,    // Science fiction
        FANTASY,            // Fantasy literature
        HORROR,             // Horror fiction
        HISTORICAL_FICTION, // Historical fiction
        BIOGRAPHY,          // Biographies
        AUTOBIOGRAPHY,      // Autobiographies
        MEMOIR,             // Memoirs
        SELF_HELP,          // Self-help books
        BUSINESS,           // Business literature
        PHILOSOPHY,         // Philosophy books
        RELIGION,           // Religious texts
        SCIENCE,            // Science books
        TECHNOLOGY,         // Technology books
        COOKING,            // Cookbooks
        TRAVEL,             // Travel books
        POETRY,             // Poetry collections
        DRAMA,              // Drama and plays
        CHILDREN,           // Children's books
        YOUNG_ADULT,        // Young adult fiction
        ACADEMIC            // Academic texts
    };

    /**
     * @brief Enumeration of movie genres
     * 
     * Defines the available genres for films and movies,
     * covering various cinematic styles and categories.
     */
    enum class MovieGenre {
        ACTION,         // Action films
        ADVENTURE,      // Adventure films
        COMEDY,         // Comedy films
        DRAMA,          // Drama films
        HORROR,         // Horror films
        THRILLER,       // Thriller films
        SCIENCE_FICTION, // Science fiction films
        FANTASY,        // Fantasy films
        ROMANCE,        // Romance films
        MYSTERY,        // Mystery films
        CRIME,          // Crime films
        WESTERN,        // Western films
        WAR,            // War films
        HISTORICAL,     // Historical films
        DOCUMENTARY,    // Documentary films
        ANIMATION,      // Animated films
        FAMILY,         // Family films
        MUSICAL,        // Musical films
        SPORTS,         // Sports films
        BIOGRAPHY,      // Biographical films
        FILM_NOIR,      // Film noir
        EXPERIMENTAL,   // Experimental films
        SHORT_FILM      // Short films
    };

    /**
     * @brief Enumeration of magazine genres
     * 
     * Defines the available categories for magazines and periodicals,
     * covering various topics and interests.
     */
    enum class MagazineGenre {
        NEWS,           // News magazines
        POLITICS,       // Political magazines
        BUSINESS,       // Business magazines
        TECHNOLOGY,     // Technology magazines
        SCIENCE,        // Science magazines
        HEALTH,         // Health magazines
        FITNESS,        // Fitness magazines
        FOOD,           // Food magazines
        TRAVEL,         // Travel magazines
        FASHION,        // Fashion magazines
        BEAUTY,         // Beauty magazines
        HOME,           // Home magazines
        GARDEN,         // Gardening magazines
        AUTOMOTIVE,     // Automotive magazines
        SPORTS,         // Sports magazines
        ENTERTAINMENT,  // Entertainment magazines
        ARTS,           // Arts magazines
        LITERATURE,     // Literature magazines
        EDUCATION,      // Education magazines
        ACADEMIC,       // Academic journals
        TRADE,          // Trade magazines
        HOBBIES,        // Hobby magazines
        CRAFTS,         // Craft magazines
        PHOTOGRAPHY     // Photography magazines
    };

    /**
     * @brief Enumeration of podcast genres
     * 
     * Defines the available categories for podcasts and audio content,
     * covering various topics and formats.
     */
    enum class PodcastGenre {
        NEWS,           // News podcasts
        POLITICS,       // Political podcasts
        BUSINESS,       // Business podcasts
        TECHNOLOGY,     // Technology podcasts
        SCIENCE,        // Science podcasts
        HEALTH,         // Health podcasts
        FITNESS,        // Fitness podcasts
        EDUCATION,      // Educational podcasts
        HISTORY,        // History podcasts
        TRUE_CRIME,     // True crime podcasts
        COMEDY,         // Comedy podcasts
        ENTERTAINMENT,  // Entertainment podcasts
        SPORTS,         // Sports podcasts
        ARTS,           // Arts podcasts
        LITERATURE,     // Literature podcasts
        PHILOSOPHY,     // Philosophy podcasts
        RELIGION,       // Religious podcasts
        SELF_HELP,      // Self-help podcasts
        INTERVIEW,      // Interview podcasts
        STORYTELLING,   // Storytelling podcasts
        MUSIC,          // Music podcasts
        FOOD,           // Food podcasts
        TRAVEL,         // Travel podcasts
        PARENTING,      // Parenting podcasts
        GAMING          // Gaming podcasts
    };

    // Enum to string conversion functions
    std::string musicGenreToString(MusicGenre genre);
    std::string bookGenreToString(BookGenre genre);
    std::string movieGenreToString(MovieGenre genre);
    std::string magazineGenreToString(MagazineGenre genre);
    std::string podcastGenreToString(PodcastGenre genre);

    // String to enum conversion functions
    MusicGenre stringToMusicGenre(const std::string& genre);
    BookGenre stringToBookGenre(const std::string& genre);
    MovieGenre stringToMovieGenre(const std::string& genre);
    MagazineGenre stringToMagazineGenre(const std::string& genre);
    PodcastGenre stringToPodcastGenre(const std::string& genre);

    // Helper functions for frontend integration
    std::vector<std::string> getAllBookGenres();
    std::vector<std::string> getAllMovieGenres();
    std::vector<std::string> getAllMusicGenres();
    std::vector<std::string> getAllMagazineGenres();
    std::vector<std::string> getAllPodcastGenres();
}

#endif // GENRES_H 