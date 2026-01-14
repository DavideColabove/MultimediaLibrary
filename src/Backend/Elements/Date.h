#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int year;
    int month;
    int day;
    
public:
    // Constructors
    Date(int y, int m, int d);
    Date(const Date& date);
    Date();
    
    // Getters and setters
    int getYear() const;
    Date& setYear(int y);
    int getMonth() const;
    Date& setMonth(int m);
    int getDay() const;
    Date& setDay(int d);
    
    // Utility methods
    bool isValid() const;
    std::string toString() const;
    std::string toString(const std::string& format) const; // format: "YYYY-MM-DD", "DD/MM/YYYY", etc.
    
    // Operators
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
};

#endif // DATE_H 