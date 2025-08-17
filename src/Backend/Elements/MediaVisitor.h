#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

// Forward declarations of concrete media types
class Book;
class Movie;
class Song;
class Magazine;
class Podcast;

/**
 * @brief Visitor interface for the Media hierarchy
 * 
 * This interface implements the Visitor design pattern to enable type-safe
 * operations on different media types without using type checking or casting.
 * Each concrete media class implements an accept() method that calls the
 * appropriate visit() method on the visitor object.
 * 
 * The Visitor pattern allows for:
 * - Type-safe operations on polymorphic objects
 * - Extensibility without modifying existing classes
 * - Separation of algorithms from object structure
 */
class MediaVisitor {
public:
    /**
     * @brief Virtual destructor for polymorphic deletion
     */
    virtual ~MediaVisitor() = default;

    /**
     * @brief Visits a Book object
     * @param book The book to visit
     */
    virtual void visit(const Book& book) = 0;
    
    /**
     * @brief Visits a Movie object
     * @param movie The movie to visit
     */
    virtual void visit(const Movie& movie) = 0;
    
    /**
     * @brief Visits a Song object
     * @param song The song to visit
     */
    virtual void visit(const Song& song) = 0;
    
    /**
     * @brief Visits a Magazine object
     * @param magazine The magazine to visit
     */
    virtual void visit(const Magazine& magazine) = 0;
    
    /**
     * @brief Visits a Podcast object
     * @param podcast The podcast to visit
     */
    virtual void visit(const Podcast& podcast) = 0;
};

#endif // MEDIAVISITOR_H


