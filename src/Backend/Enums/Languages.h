#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <string>
#include <vector>


namespace Enums {
    enum class Language {
        ITALIAN,        
        ENGLISH,        
        SPANISH,        
        FRENCH,         
        GERMAN,         
        PORTUGUESE,     
        RUSSIAN,        
        CHINESE,        
        JAPANESE,       
        KOREAN,         
        ARABIC,         
        HINDI,          
        DUTCH,          
        SWEDISH,        
        NORWEGIAN,      
        DANISH,         
        FINNISH,        
        POLISH,         
        CZECH,          
        HUNGARIAN,      
        ROMANIAN,       
        BULGARIAN,      
        GREEK,          
        TURKISH,        
        HEBREW,         
        PERSIAN,        
        THAI,           
        VIETNAMESE,     
        INDONESIAN,     
        MALAY,          
        FILIPINO,       
        LATIN,          
        ANCIENT_GREEK,  
        SANSKRIT,       
        OLD_ENGLISH,    
        MIDDLE_ENGLISH, 
        OLD_FRENCH,     
        OLD_GERMAN,     
        OLD_ITALIAN,    
        OLD_SPANISH,    
        OLD_PORTUGUESE, 
        OLD_RUSSIAN,    
        OLD_CHINESE,    
        OLD_JAPANESE,   
        OLD_KOREAN,     
        OLD_ARABIC,     
        OLD_HINDI,      
        OLD_DUTCH,      
        OLD_SWEDISH,    
        OLD_NORWEGIAN,  
        OLD_DANISH,     
        OLD_FINNISH,    
        OLD_POLISH,     
        OLD_CZECH,      
        OLD_HUNGARIAN,  
        OLD_ROMANIAN,   
        OLD_BULGARIAN,  
        OLD_GREEK,      
        OLD_TURKISH,    
        OLD_HEBREW,     
        OLD_PERSIAN,    
        OLD_THAI,       
        OLD_VIETNAMESE, 
        OLD_INDONESIAN, 
        OLD_MALAY,      
        OLD_FILIPINO,   
        OLD_LATIN,      
        OLD_ANCIENT_GREEK, 
        OLD_SANSKRIT,   
        OTHER           
    };
    std::string languageToString(Language language);
    Language stringToLanguage(const std::string& language);
    std::vector<std::string> getAllLanguages();
}

#endif 