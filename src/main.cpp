#include <iostream>
#include "Backend/Elements/Media.h"
#include "Backend/Elements/Book.h"
#include "Backend/Elements/Movie.h"
#include "Backend/Elements/Song.h"
#include "Backend/Elements/Magazine.h"
#include "Backend/Elements/Podcast.h"
#include "Backend/Enums/Genres.h"
#include "Backend/Enums/Languages.h"

int main() {
    std::cout << "=== Test Compilazione Multimedia Library ===" << std::endl;
    
    try {
        // Test Book
        std::cout << "\n--- Test Book ---" << std::endl;
        Book book("Il Nome della Rosa", "Umberto Eco", 
                 Enums::BookGenre::HISTORICAL_FICTION, 
                 Date(1980, 1, 1),
                 1, 2048, true, "book_cover.jpg",
                 "Bompiani", 512, "978-88-452-1234-5", Enums::Language::ITALIAN);
        
        std::cout << "Book: " << book.getTitle() << " by " << book.getAuthor() << std::endl;
        std::cout << "Genre: " << book.getGenreString() << std::endl;
        std::cout << "Language: " << book.getLanguageString() << std::endl;
        std::cout << "Valid: " << (book.isValid() ? "Yes" : "No") << std::endl;
        
        // Test Movie
        std::cout << "\n--- Test Movie ---" << std::endl;
        Movie movie("The Matrix", "Wachowski Sisters", 
                   Enums::MovieGenre::SCIENCE_FICTION, 
                   Date(1999, 3, 31),
                   2, 4096, true, "matrix_cover.jpg",
                   "Lana Wachowski", 136, "Warner Bros.", "R", 
                   Enums::Language::ENGLISH, "USA");
        
        std::cout << "Movie: " << movie.getTitle() << " by " << movie.getDirector() << std::endl;
        std::cout << "Genre: " << movie.getGenreString() << std::endl;
        std::cout << "Language: " << movie.getLanguageString() << std::endl;
        std::cout << "Valid: " << (movie.isValid() ? "Yes" : "No") << std::endl;
        
        // Test Song
        std::cout << "\n--- Test Song ---" << std::endl;
        Song song("Bohemian Rhapsody", "Queen", 
                 Enums::MusicGenre::ROCK, 
                 Date(1975, 10, 31),
                 3, 1024, true, "queen_cover.jpg",
                 "Queen", "A Night at the Opera", 355, "MP3", "EMI", 1);
        
        std::cout << "Song: " << song.getTitle() << " by " << song.getArtist() << std::endl;
        std::cout << "Genre: " << song.getGenreString() << std::endl;
        std::cout << "Valid: " << (song.isValid() ? "Yes" : "No") << std::endl;
        
        // Test Magazine
        std::cout << "\n--- Test Magazine ---" << std::endl;
        Magazine magazine("National Geographic", "Various Authors", 
                        Enums::MagazineGenre::SCIENCE, 
                        Date(2024, 1, 1),
                        4, 512, true, "natgeo_cover.jpg",
                        "National Geographic Society", 1, "0027-9358", "Susan Goldberg", 
                        80, "Monthly");
        
        std::cout << "Magazine: " << magazine.getTitle() << std::endl;
        std::cout << "Genre: " << magazine.getGenreString() << std::endl;
        std::cout << "Valid: " << (magazine.isValid() ? "Yes" : "No") << std::endl;
        
        // Test Podcast
        std::cout << "\n--- Test Podcast ---" << std::endl;
        Podcast podcast("Serial", "Sarah Koenig", 
                      Enums::PodcastGenre::TRUE_CRIME, 
                      Date(2014, 10, 3),
                      5, 256, true, "serial_cover.jpg",
                      "Sarah Koenig", 1, "Spotify", 45, "Serial", 
                      "A true crime podcast about a real murder case.");
        
        std::cout << "Podcast: " << podcast.getTitle() << " by " << podcast.getHost() << std::endl;
        std::cout << "Genre: " << podcast.getGenreString() << std::endl;
        std::cout << "Valid: " << (podcast.isValid() ? "Yes" : "No") << std::endl;
        
        std::cout << "\n=== Compilazione completata con successo! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
