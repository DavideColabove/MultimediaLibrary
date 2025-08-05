#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date {
    protected:
        int day;
        int month;
        int year;

    public:
        Date(int d, int m, int y);
        Date(const Date& date);
        Date();
        virtual ~Date();

        void setDay(int d);
        int getDay() const;
        void setMonth(int m);
        int getMonth() const;
        void setYear(int y);
        int getYear() const;
        bool operator==(const Date& d) const;
        bool operator!=(const Date& d) const;
        bool operator<(const Date& d) const;
        bool operator>(const Date& d) const;
        bool operator<=(const Date& d) const;
        bool operator>=(const Date& d) const;

        void printDate() const;
};

#endif 