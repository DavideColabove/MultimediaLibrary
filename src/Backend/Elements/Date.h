#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int year;   
    int month;  
    int day;    
public:
    Date(int y, int m, int d);
    Date(const Date& date);
    Date();
    int getYear() const;
    Date& setYear(int y);
    int getMonth() const;
    Date& setMonth(int m);
    int getDay() const;
    Date& setDay(int d);
    bool isValid() const;
    std::string toString() const;
    std::string toString(const std::string& format) const;
    static bool parseIso(const std::string& iso8601, Date& out);
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    Date& operator=(const Date&) = default;
};

#endif 