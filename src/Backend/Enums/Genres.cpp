#include "Genres.h"
#include <map>

namespace Enums {
    
    std::string musicGenreToString(MusicGenre genre) {
        static const std::map<MusicGenre, std::string> genreMap = {
            {MusicGenre::ROCK, "Rock"},
            {MusicGenre::POP, "Pop"},
            {MusicGenre::JAZZ, "Jazz"},
            {MusicGenre::CLASSICAL, "Classical"},
            {MusicGenre::HIP_HOP, "Hip Hop"},
            {MusicGenre::ELECTRONIC, "Electronic"},
            {MusicGenre::COUNTRY, "Country"},
            {MusicGenre::FOLK, "Folk"},
            {MusicGenre::BLUES, "Blues"},
            {MusicGenre::REGGAE, "Reggae"},
            {MusicGenre::METAL, "Metal"},
            {MusicGenre::PUNK, "Punk"},
            {MusicGenre::INDIE, "Indie"},
            {MusicGenre::RAP, "Rap"},
            {MusicGenre::SOUL, "Soul"},
            {MusicGenre::FUNK, "Funk"},
            {MusicGenre::DISCO, "Disco"},
            {MusicGenre::GOSPEL, "Gospel"},
            {MusicGenre::LATIN, "Latin"},
            {MusicGenre::WORLD_MUSIC, "World Music"}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : "Unknown";
    }

    
    MusicGenre stringToMusicGenre(const std::string& genre) {
        static const std::map<std::string, MusicGenre> genreMap = {
            {"Rock", MusicGenre::ROCK},
            {"Pop", MusicGenre::POP},
            {"Jazz", MusicGenre::JAZZ},
            {"Classical", MusicGenre::CLASSICAL},
            {"Hip Hop", MusicGenre::HIP_HOP},
            {"Electronic", MusicGenre::ELECTRONIC},
            {"Country", MusicGenre::COUNTRY},
            {"Folk", MusicGenre::FOLK},
            {"Blues", MusicGenre::BLUES},
            {"Reggae", MusicGenre::REGGAE},
            {"Metal", MusicGenre::METAL},
            {"Punk", MusicGenre::PUNK},
            {"Indie", MusicGenre::INDIE},
            {"Rap", MusicGenre::RAP},
            {"Soul", MusicGenre::SOUL},
            {"Funk", MusicGenre::FUNK},
            {"Disco", MusicGenre::DISCO},
            {"Gospel", MusicGenre::GOSPEL},
            {"Latin", MusicGenre::LATIN},
            {"World Music", MusicGenre::WORLD_MUSIC}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : MusicGenre::ROCK;
    }

    std::string bookGenreToString(BookGenre genre) {
        static const std::map<BookGenre, std::string> genreMap = {
            {BookGenre::FICTION, "Fiction"},
            {BookGenre::NON_FICTION, "Non-Fiction"},
            {BookGenre::MYSTERY, "Mystery"},
            {BookGenre::THRILLER, "Thriller"},
            {BookGenre::ROMANCE, "Romance"},
            {BookGenre::SCIENCE_FICTION, "Science Fiction"},
            {BookGenre::FANTASY, "Fantasy"},
            {BookGenre::HORROR, "Horror"},
            {BookGenre::HISTORICAL_FICTION, "Historical Fiction"},
            {BookGenre::BIOGRAPHY, "Biography"},
            {BookGenre::AUTOBIOGRAPHY, "Autobiography"},
            {BookGenre::MEMOIR, "Memoir"},
            {BookGenre::SELF_HELP, "Self-Help"},
            {BookGenre::BUSINESS, "Business"},
            {BookGenre::PHILOSOPHY, "Philosophy"},
            {BookGenre::RELIGION, "Religion"},
            {BookGenre::SCIENCE, "Science"},
            {BookGenre::TECHNOLOGY, "Technology"},
            {BookGenre::COOKING, "Cooking"},
            {BookGenre::TRAVEL, "Travel"},
            {BookGenre::POETRY, "Poetry"},
            {BookGenre::DRAMA, "Drama"},
            {BookGenre::CHILDREN, "Children"},
            {BookGenre::YOUNG_ADULT, "Young Adult"},
            {BookGenre::ACADEMIC, "Academic"}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : "Unknown";
    }

    BookGenre stringToBookGenre(const std::string& genre) {
        static const std::map<std::string, BookGenre> genreMap = {
            {"Fiction", BookGenre::FICTION},
            {"Non-Fiction", BookGenre::NON_FICTION},
            {"Mystery", BookGenre::MYSTERY},
            {"Thriller", BookGenre::THRILLER},
            {"Romance", BookGenre::ROMANCE},
            {"Science Fiction", BookGenre::SCIENCE_FICTION},
            {"Fantasy", BookGenre::FANTASY},
            {"Horror", BookGenre::HORROR},
            {"Historical Fiction", BookGenre::HISTORICAL_FICTION},
            {"Biography", BookGenre::BIOGRAPHY},
            {"Autobiography", BookGenre::AUTOBIOGRAPHY},
            {"Memoir", BookGenre::MEMOIR},
            {"Self-Help", BookGenre::SELF_HELP},
            {"Business", BookGenre::BUSINESS},
            {"Philosophy", BookGenre::PHILOSOPHY},
            {"Religion", BookGenre::RELIGION},
            {"Science", BookGenre::SCIENCE},
            {"Technology", BookGenre::TECHNOLOGY},
            {"Cooking", BookGenre::COOKING},
            {"Travel", BookGenre::TRAVEL},
            {"Poetry", BookGenre::POETRY},
            {"Drama", BookGenre::DRAMA},
            {"Children", BookGenre::CHILDREN},
            {"Young Adult", BookGenre::YOUNG_ADULT},
            {"Academic", BookGenre::ACADEMIC}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : BookGenre::FICTION;
    }

    std::string movieGenreToString(MovieGenre genre) {
        static const std::map<MovieGenre, std::string> genreMap = {
            {MovieGenre::ACTION, "Action"},
            {MovieGenre::ADVENTURE, "Adventure"},
            {MovieGenre::COMEDY, "Comedy"},
            {MovieGenre::DRAMA, "Drama"},
            {MovieGenre::HORROR, "Horror"},
            {MovieGenre::THRILLER, "Thriller"},
            {MovieGenre::SCIENCE_FICTION, "Science Fiction"},
            {MovieGenre::FANTASY, "Fantasy"},
            {MovieGenre::ROMANCE, "Romance"},
            {MovieGenre::MYSTERY, "Mystery"},
            {MovieGenre::CRIME, "Crime"},
            {MovieGenre::WESTERN, "Western"},
            {MovieGenre::WAR, "War"},
            {MovieGenre::HISTORICAL, "Historical"},
            {MovieGenre::DOCUMENTARY, "Documentary"},
            {MovieGenre::ANIMATION, "Animation"},
            {MovieGenre::FAMILY, "Family"},
            {MovieGenre::MUSICAL, "Musical"},
            {MovieGenre::SPORTS, "Sports"},
            {MovieGenre::BIOGRAPHY, "Biography"},
            {MovieGenre::FILM_NOIR, "Film Noir"},
            {MovieGenre::EXPERIMENTAL, "Experimental"},
            {MovieGenre::SHORT_FILM, "Short Film"}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : "Unknown";
    }

    MovieGenre stringToMovieGenre(const std::string& genre) {
        static const std::map<std::string, MovieGenre> genreMap = {
            {"Action", MovieGenre::ACTION},
            {"Adventure", MovieGenre::ADVENTURE},
            {"Comedy", MovieGenre::COMEDY},
            {"Drama", MovieGenre::DRAMA},
            {"Horror", MovieGenre::HORROR},
            {"Thriller", MovieGenre::THRILLER},
            {"Science Fiction", MovieGenre::SCIENCE_FICTION},
            {"Fantasy", MovieGenre::FANTASY},
            {"Romance", MovieGenre::ROMANCE},
            {"Mystery", MovieGenre::MYSTERY},
            {"Crime", MovieGenre::CRIME},
            {"Western", MovieGenre::WESTERN},
            {"War", MovieGenre::WAR},
            {"Historical", MovieGenre::HISTORICAL},
            {"Documentary", MovieGenre::DOCUMENTARY},
            {"Animation", MovieGenre::ANIMATION},
            {"Family", MovieGenre::FAMILY},
            {"Musical", MovieGenre::MUSICAL},
            {"Sports", MovieGenre::SPORTS},
            {"Biography", MovieGenre::BIOGRAPHY},
            {"Film Noir", MovieGenre::FILM_NOIR},
            {"Experimental", MovieGenre::EXPERIMENTAL},
            {"Short Film", MovieGenre::SHORT_FILM}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : MovieGenre::DRAMA;
    }

    std::string magazineGenreToString(MagazineGenre genre) {
        static const std::map<MagazineGenre, std::string> genreMap = {
            {MagazineGenre::NEWS, "News"},
            {MagazineGenre::POLITICS, "Politics"},
            {MagazineGenre::BUSINESS, "Business"},
            {MagazineGenre::TECHNOLOGY, "Technology"},
            {MagazineGenre::SCIENCE, "Science"},
            {MagazineGenre::HEALTH, "Health"},
            {MagazineGenre::FITNESS, "Fitness"},
            {MagazineGenre::FOOD, "Food"},
            {MagazineGenre::TRAVEL, "Travel"},
            {MagazineGenre::FASHION, "Fashion"},
            {MagazineGenre::BEAUTY, "Beauty"},
            {MagazineGenre::HOME, "Home"},
            {MagazineGenre::GARDEN, "Garden"},
            {MagazineGenre::AUTOMOTIVE, "Automotive"},
            {MagazineGenre::SPORTS, "Sports"},
            {MagazineGenre::ENTERTAINMENT, "Entertainment"},
            {MagazineGenre::ARTS, "Arts"},
            {MagazineGenre::LITERATURE, "Literature"},
            {MagazineGenre::EDUCATION, "Education"},
            {MagazineGenre::ACADEMIC, "Academic"},
            {MagazineGenre::TRADE, "Trade"},
            {MagazineGenre::HOBBIES, "Hobbies"},
            {MagazineGenre::CRAFTS, "Crafts"},
            {MagazineGenre::PHOTOGRAPHY, "Photography"}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : "Unknown";
    }

    MagazineGenre stringToMagazineGenre(const std::string& genre) {
        static const std::map<std::string, MagazineGenre> genreMap = {
            {"News", MagazineGenre::NEWS},
            {"Politics", MagazineGenre::POLITICS},
            {"Business", MagazineGenre::BUSINESS},
            {"Technology", MagazineGenre::TECHNOLOGY},
            {"Science", MagazineGenre::SCIENCE},
            {"Health", MagazineGenre::HEALTH},
            {"Fitness", MagazineGenre::FITNESS},
            {"Food", MagazineGenre::FOOD},
            {"Travel", MagazineGenre::TRAVEL},
            {"Fashion", MagazineGenre::FASHION},
            {"Beauty", MagazineGenre::BEAUTY},
            {"Home", MagazineGenre::HOME},
            {"Garden", MagazineGenre::GARDEN},
            {"Automotive", MagazineGenre::AUTOMOTIVE},
            {"Sports", MagazineGenre::SPORTS},
            {"Entertainment", MagazineGenre::ENTERTAINMENT},
            {"Arts", MagazineGenre::ARTS},
            {"Literature", MagazineGenre::LITERATURE},
            {"Education", MagazineGenre::EDUCATION},
            {"Academic", MagazineGenre::ACADEMIC},
            {"Trade", MagazineGenre::TRADE},
            {"Hobbies", MagazineGenre::HOBBIES},
            {"Crafts", MagazineGenre::CRAFTS},
            {"Photography", MagazineGenre::PHOTOGRAPHY}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : MagazineGenre::NEWS;
    }

    std::string podcastGenreToString(PodcastGenre genre) {
        static const std::map<PodcastGenre, std::string> genreMap = {
            {PodcastGenre::NEWS, "News"},
            {PodcastGenre::POLITICS, "Politics"},
            {PodcastGenre::BUSINESS, "Business"},
            {PodcastGenre::TECHNOLOGY, "Technology"},
            {PodcastGenre::SCIENCE, "Science"},
            {PodcastGenre::HEALTH, "Health"},
            {PodcastGenre::FITNESS, "Fitness"},
            {PodcastGenre::EDUCATION, "Education"},
            {PodcastGenre::HISTORY, "History"},
            {PodcastGenre::TRUE_CRIME, "True Crime"},
            {PodcastGenre::COMEDY, "Comedy"},
            {PodcastGenre::ENTERTAINMENT, "Entertainment"},
            {PodcastGenre::SPORTS, "Sports"},
            {PodcastGenre::ARTS, "Arts"},
            {PodcastGenre::LITERATURE, "Literature"},
            {PodcastGenre::PHILOSOPHY, "Philosophy"},
            {PodcastGenre::RELIGION, "Religion"},
            {PodcastGenre::SELF_HELP, "Self-Help"},
            {PodcastGenre::INTERVIEW, "Interview"},
            {PodcastGenre::STORYTELLING, "Storytelling"},
            {PodcastGenre::MUSIC, "Music"},
            {PodcastGenre::FOOD, "Food"},
            {PodcastGenre::TRAVEL, "Travel"},
            {PodcastGenre::PARENTING, "Parenting"},
            {PodcastGenre::GAMING, "Gaming"}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : "Unknown";
    }

    PodcastGenre stringToPodcastGenre(const std::string& genre) {
        static const std::map<std::string, PodcastGenre> genreMap = {
            {"News", PodcastGenre::NEWS},
            {"Politics", PodcastGenre::POLITICS},
            {"Business", PodcastGenre::BUSINESS},
            {"Technology", PodcastGenre::TECHNOLOGY},
            {"Science", PodcastGenre::SCIENCE},
            {"Health", PodcastGenre::HEALTH},
            {"Fitness", PodcastGenre::FITNESS},
            {"Education", PodcastGenre::EDUCATION},
            {"History", PodcastGenre::HISTORY},
            {"True Crime", PodcastGenre::TRUE_CRIME},
            {"Comedy", PodcastGenre::COMEDY},
            {"Entertainment", PodcastGenre::ENTERTAINMENT},
            {"Sports", PodcastGenre::SPORTS},
            {"Arts", PodcastGenre::ARTS},
            {"Literature", PodcastGenre::LITERATURE},
            {"Philosophy", PodcastGenre::PHILOSOPHY},
            {"Religion", PodcastGenre::RELIGION},
            {"Self-Help", PodcastGenre::SELF_HELP},
            {"Interview", PodcastGenre::INTERVIEW},
            {"Storytelling", PodcastGenre::STORYTELLING},
            {"Music", PodcastGenre::MUSIC},
            {"Food", PodcastGenre::FOOD},
            {"Travel", PodcastGenre::TRAVEL},
            {"Parenting", PodcastGenre::PARENTING},
            {"Gaming", PodcastGenre::GAMING}
        };
        auto it = genreMap.find(genre);
        return (it != genreMap.end()) ? it->second : PodcastGenre::EDUCATION;
    }

    
    std::vector<std::string> getAllBookGenres() {
        return {"Fiction", "Non-Fiction", "Mystery", "Thriller", "Romance", 
                "Science Fiction", "Fantasy", "Horror", "Historical Fiction", 
                "Biography", "Autobiography", "Memoir", "Self-Help", "Business", 
                "Philosophy", "Religion", "Science", "Technology", "Cooking", 
                "Travel", "Poetry", "Drama", "Children", "Young Adult", "Academic"};
    }

    std::vector<std::string> getAllMovieGenres() {
        return {"Action", "Adventure", "Comedy", "Drama", "Horror", "Thriller", 
                "Science Fiction", "Fantasy", "Romance", "Mystery", "Crime", 
                "Western", "War", "Historical", "Documentary", "Animation", 
                "Family", "Musical", "Sports", "Biography", "Film Noir", 
                "Experimental", "Short Film"};
    }

    std::vector<std::string> getAllMusicGenres() {
        return {"Rock", "Pop", "Jazz", "Classical", "Hip Hop", "Electronic", 
                "Country", "Folk", "Blues", "Reggae", "Metal", "Punk", 
                "Indie", "Rap", "Soul", "Funk", "Disco", "Gospel", 
                "Latin", "World Music"};
    }

    std::vector<std::string> getAllMagazineGenres() {
        return {"News", "Politics", "Business", "Technology", "Science", 
                "Health", "Fitness", "Food", "Travel", "Fashion", "Beauty", 
                "Home", "Garden", "Automotive", "Sports", "Entertainment", 
                "Arts", "Literature", "Education", "Academic", "Trade", 
                "Hobbies", "Crafts", "Photography"};
    }

    std::vector<std::string> getAllPodcastGenres() {
        return {"News", "Politics", "Business", "Technology", "Science", 
                "Health", "Fitness", "Education", "History", "True Crime", 
                "Comedy", "Entertainment", "Sports", "Arts", "Literature", 
                "Philosophy", "Religion", "Self-Help", "Interview", 
                "Storytelling", "Music", "Food", "Travel", "Parenting", "Gaming"};
    }
} 