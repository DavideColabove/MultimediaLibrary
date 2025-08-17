#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <string>
#include <vector>

/**
 * @brief Namespace containing language enumeration and utility functions
 * 
 * This namespace provides a comprehensive enumeration of languages supported
 * by the multimedia library system, including modern languages, historical
 * languages, and ancient languages. It includes conversion functions between
 * enum values and string representations, as well as helper functions for
 * frontend integration.
 */
namespace Enums {
    /**
     * @brief Enumeration of supported languages
     * 
     * Defines all languages supported by the library system, including:
     * - Modern languages (Italian, English, Spanish, etc.)
     * - Historical languages (Old English, Middle English, etc.)
     * - Ancient languages (Latin, Ancient Greek, Sanskrit, etc.)
     * - Other languages for extensibility
     */
    enum class Language {
        // Modern languages
        ITALIAN,        // Italian
        ENGLISH,        // English
        SPANISH,        // Spanish
        FRENCH,         // French
        GERMAN,         // German
        PORTUGUESE,     // Portuguese
        RUSSIAN,        // Russian
        CHINESE,        // Chinese
        JAPANESE,       // Japanese
        KOREAN,         // Korean
        ARABIC,         // Arabic
        HINDI,          // Hindi
        DUTCH,          // Dutch
        SWEDISH,        // Swedish
        NORWEGIAN,      // Norwegian
        DANISH,         // Danish
        FINNISH,        // Finnish
        POLISH,         // Polish
        CZECH,          // Czech
        HUNGARIAN,      // Hungarian
        ROMANIAN,       // Romanian
        BULGARIAN,      // Bulgarian
        GREEK,          // Greek
        TURKISH,        // Turkish
        HEBREW,         // Hebrew
        PERSIAN,        // Persian
        THAI,           // Thai
        VIETNAMESE,     // Vietnamese
        INDONESIAN,     // Indonesian
        MALAY,          // Malay
        FILIPINO,       // Filipino
        
        // Historical and ancient languages
        LATIN,          // Latin
        ANCIENT_GREEK,  // Ancient Greek
        SANSKRIT,       // Sanskrit
        OLD_ENGLISH,    // Old English
        MIDDLE_ENGLISH, // Middle English
        OLD_FRENCH,     // Old French
        OLD_GERMAN,     // Old German
        OLD_ITALIAN,    // Old Italian
        OLD_SPANISH,    // Old Spanish
        OLD_PORTUGUESE, // Old Portuguese
        OLD_RUSSIAN,    // Old Russian
        OLD_CHINESE,    // Old Chinese
        OLD_JAPANESE,   // Old Japanese
        OLD_KOREAN,     // Old Korean
        OLD_ARABIC,     // Old Arabic
        OLD_HINDI,      // Old Hindi
        OLD_DUTCH,      // Old Dutch
        OLD_SWEDISH,    // Old Swedish
        OLD_NORWEGIAN,  // Old Norwegian
        OLD_DANISH,     // Old Danish
        OLD_FINNISH,    // Old Finnish
        OLD_POLISH,     // Old Polish
        OLD_CZECH,      // Old Czech
        OLD_HUNGARIAN,  // Old Hungarian
        OLD_ROMANIAN,   // Old Romanian
        OLD_BULGARIAN,  // Old Bulgarian
        OLD_GREEK,      // Old Greek
        OLD_TURKISH,    // Old Turkish
        OLD_HEBREW,     // Old Hebrew
        OLD_PERSIAN,    // Old Persian
        OLD_THAI,       // Old Thai
        OLD_VIETNAMESE, // Old Vietnamese
        OLD_INDONESIAN, // Old Indonesian
        OLD_MALAY,      // Old Malay
        OLD_FILIPINO,   // Old Filipino
        OLD_LATIN,      // Old Latin
        OLD_ANCIENT_GREEK, // Old Ancient Greek
        OLD_SANSKRIT,   // Old Sanskrit
        
        OTHER           // Other languages
    };

    /**
     * @brief Converts a Language enum to its string representation
     * @param language The language enum value
     * @return String representation of the language
     */
    std::string languageToString(Language language);

    /**
     * @brief Converts a string to its corresponding Language enum
     * @param language The language string
     * @return Language enum value
     */
    Language stringToLanguage(const std::string& language);

    /**
     * @brief Gets all languages as a vector of strings for frontend integration
     * @return Vector containing all language names
     */
    std::vector<std::string> getAllLanguages();
}

#endif // LANGUAGES_H 