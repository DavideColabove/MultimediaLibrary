#include "Date.h"
#include <iostream>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}
Date::Date(const Date& date) : day(date.day), month(date.month), year(date.year) {}
Date::Date() : day(0), month(0), year(0) {}
Date::~Date() {}

void Date::setDay(int d) {
    day = d;
}

int Date::getDay() const {
    return day;
}

void Date::setMonth(int m) {
    month = m;
}

int Date::getMonth() const {
    return month;
}

void Date::setYear(int y) {
    year = y;
}

int Date::getYear() const {
    return year;
}

bool Date::operator==(const Date& d) const {
    return (day == d.day && month == d.month && year == d.year);
}

bool Date::operator!=(const Date& d) const {
    return !(*this == d);
}

bool Date::operator<(const Date& d) const {
    if (year != d.year) return year < d.year;
    if (month != d.month) return month < d.month;
    return day < d.day;
}

bool Date::operator>(const Date& d) const {
    return d < *this;
}

bool Date::operator<=(const Date& d) const {
    return !(*this > d);
}

bool Date::operator>=(const Date& d) const {
    return !(*this < d);
}

void Date::printDate() const {
    std::cout << day << "/" << month << "/" << year << std::endl;
}