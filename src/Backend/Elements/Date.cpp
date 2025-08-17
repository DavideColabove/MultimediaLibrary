#include "Date.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {
    if (!isValid()) {
        throw std::invalid_argument("Invalid date");
    }
}

Date::Date(const Date& date) : year(date.year), month(date.month), day(date.day) {}

Date::Date() : year(1900), month(1), day(1) {}

int Date::getYear() const {
    return year;
}

Date& Date::setYear(int y) {
    year = y;
    if (!isValid()) {
        throw std::invalid_argument("Invalid year");
    }
    return *this;
}

int Date::getMonth() const {
    return month;
}

Date& Date::setMonth(int m) {
    month = m;
    if (!isValid()) {
        throw std::invalid_argument("Invalid month");
    }
    return *this;
}

int Date::getDay() const {
    return day;
}

Date& Date::setDay(int d) {
    day = d;
    if (!isValid()) {
        throw std::invalid_argument("Invalid day");
    }
    return *this;
}

// Validate date and handle leap years (year divisible by 4 but not 100, or by 400)
bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }
    
    return day >= 1 && day <= daysInMonth[month - 1];
}

std::string Date::toString() const {
    return toString("YYYY-MM-DD");
}

std::string Date::toString(const std::string& format) const {
    std::string result = format;
    
    std::string yearStr = std::to_string(year);
    std::string monthStr = std::to_string(month);
    std::string dayStr = std::to_string(day);
    
    if (monthStr.length() == 1) monthStr = "0" + monthStr;
    if (dayStr.length() == 1) dayStr = "0" + dayStr;
    
    size_t pos = result.find("YYYY");
    if (pos != std::string::npos) result.replace(pos, 4, yearStr);
    
    pos = result.find("MM");
    if (pos != std::string::npos) result.replace(pos, 2, monthStr);
    
    pos = result.find("DD");
    if (pos != std::string::npos) result.replace(pos, 2, dayStr);
    
    return result;
}

bool Date::parseIso(const std::string& iso8601, Date& out)
{
    if (iso8601.size() != 10 || iso8601[4] != '-' || iso8601[7] != '-') return false;
    auto isDigit = [](char c){ return c >= '0' && c <= '9'; };
    for (int i : {0,1,2,3,5,6,8,9}) if (!isDigit(iso8601[i])) return false;
    int y = std::stoi(iso8601.substr(0,4));
    int m = std::stoi(iso8601.substr(5,2));
    int d = std::stoi(iso8601.substr(8,2));
    Date candidate(y,m,d);
    if (!candidate.isValid()) return false;
    out = candidate;
    return true;
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}

bool Date::operator>=(const Date& other) const {
    return *this > other || *this == other;
} 