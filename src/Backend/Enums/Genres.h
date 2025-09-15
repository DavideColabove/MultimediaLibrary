#ifndef GENRES_H
#define GENRES_H

#include <string>
#include <vector>


namespace Enums {
    enum class MusicGenre {
        ROCK,           
        POP,            
        JAZZ,           
        CLASSICAL,      
        HIP_HOP,        
        ELECTRONIC,     
        COUNTRY,        
        FOLK,           
        BLUES,          
        REGGAE,         
        METAL,          
        PUNK,           
        INDIE,          
        RAP,            
        SOUL,           
        FUNK,           
        DISCO,          
        GOSPEL,         
        LATIN,          
        WORLD_MUSIC     
    };

    enum class BookGenre {
        FICTION,            
        NON_FICTION,        
        MYSTERY,            
        THRILLER,           
        ROMANCE,            
        SCIENCE_FICTION,    
        FANTASY,            
        HORROR,             
        HISTORICAL_FICTION, 
        BIOGRAPHY,          
        AUTOBIOGRAPHY,      
        MEMOIR,             
        SELF_HELP,          
        BUSINESS,           
        PHILOSOPHY,         
        RELIGION,           
        SCIENCE,            
        TECHNOLOGY,         
        COOKING,            
        TRAVEL,             
        POETRY,             
        DRAMA,              
        CHILDREN,           
        YOUNG_ADULT,        
        ACADEMIC            
    };

    enum class MovieGenre {
        ACTION,         
        ADVENTURE,      
        COMEDY,         
        DRAMA,          
        HORROR,         
        THRILLER,       
        SCIENCE_FICTION, 
        FANTASY,        
        ROMANCE,        
        MYSTERY,        
        CRIME,          
        WESTERN,        
        WAR,            
        HISTORICAL,     
        DOCUMENTARY,    
        ANIMATION,      
        FAMILY,         
        MUSICAL,        
        SPORTS,         
        BIOGRAPHY,      
        FILM_NOIR,      
        EXPERIMENTAL,   
        SHORT_FILM      
    };

    enum class MagazineGenre {
        NEWS,           
        POLITICS,       
        BUSINESS,       
        TECHNOLOGY,     
        SCIENCE,        
        HEALTH,         
        FITNESS,        
        FOOD,           
        TRAVEL,         
        FASHION,        
        BEAUTY,         
        HOME,           
        GARDEN,         
        AUTOMOTIVE,     
        SPORTS,         
        ENTERTAINMENT,  
        ARTS,           
        LITERATURE,     
        EDUCATION,      
        ACADEMIC,       
        TRADE,          
        HOBBIES,        
        CRAFTS,         
        PHOTOGRAPHY     
    };

    enum class PodcastGenre {
        NEWS,           
        POLITICS,       
        BUSINESS,       
        TECHNOLOGY,     
        SCIENCE,        
        HEALTH,         
        FITNESS,        
        EDUCATION,      
        HISTORY,        
        TRUE_CRIME,     
        COMEDY,         
        ENTERTAINMENT,  
        SPORTS,         
        ARTS,           
        LITERATURE,     
        PHILOSOPHY,     
        RELIGION,       
        SELF_HELP,      
        INTERVIEW,      
        STORYTELLING,   
        MUSIC,          
        FOOD,           
        TRAVEL,         
        PARENTING,      
        GAMING          
    };

    std::string musicGenreToString(MusicGenre genre);
    std::string bookGenreToString(BookGenre genre);
    std::string movieGenreToString(MovieGenre genre);
    std::string magazineGenreToString(MagazineGenre genre);
    std::string podcastGenreToString(PodcastGenre genre);

    MusicGenre stringToMusicGenre(const std::string& genre);
    BookGenre stringToBookGenre(const std::string& genre);
    MovieGenre stringToMovieGenre(const std::string& genre);
    MagazineGenre stringToMagazineGenre(const std::string& genre);
    PodcastGenre stringToPodcastGenre(const std::string& genre);

    std::vector<std::string> getAllBookGenres();
    std::vector<std::string> getAllMovieGenres();
    std::vector<std::string> getAllMusicGenres();
    std::vector<std::string> getAllMagazineGenres();
    std::vector<std::string> getAllPodcastGenres();
}

#endif 