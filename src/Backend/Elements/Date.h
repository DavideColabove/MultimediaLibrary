#ifndef DATE_H
#define DATE_H

#include <string>

/**
 * @brief Date class for managing calendar dates
 * 
 * This class provides a robust implementation for handling dates with validation,
 * formatting, and comparison capabilities. It supports various date formats
 * and ensures data integrity through comprehensive validation.
 */
class Date {
private:
    int year;   // Year (e.g., 2024)
    int month;  // Month (1-12)
    int day;    // Day of month (1-31)
    
public:
    /**
     * @brief Constructs a Date with specified year, month, and day
     * @param y Year
     * @param m Month (1-12)
     * @param d Day (1-31)
     */
    Date(int y, int m, int d);
    
    /**
     * @brief Copy constructor
     * @param date Date object to copy from
     */
    Date(const Date& date);
    
    /**
     * @brief Default constructor (creates invalid date)
     */
    Date();
    
    // Attribute accessors
    int getYear() const;
    Date& setYear(int y);
    int getMonth() const;
    Date& setMonth(int m);
    int getDay() const;
    Date& setDay(int d);
    
    /**
     * @brief Validates the date for calendar correctness
     * 
     * Checks if the date represents a valid calendar date, including:
     * - Valid year range (1900-2100)
     * - Valid month (1-12)
     * - Valid day for the given month and year
     * - Leap year handling for February
     * 
     * @return true if the date is valid, false otherwise
     */
    bool isValid() const;
    
    /**
     * @brief Converts the date to string representation
     * @return Date in "YYYY-MM-DD" format
     */
    std::string toString() const;
    
    /**
     * @brief Converts the date to string with custom format
     * @param format Format string (e.g., "YYYY-MM-DD", "DD/MM/YYYY")
     * @return Formatted date string
     */
    std::string toString(const std::string& format) const;
    
    /**
     * @brief Parses an ISO 8601 date string
     * @param iso8601 Date string in "YYYY-MM-DD" format
     * @param out Output date object
     * @return true if parsing successful, false otherwise
     */
    static bool parseIso(const std::string& iso8601, Date& out);
    
    // Comparison operators
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    
    /**
     * @brief Assignment operator
     * @return Reference to this Date object
     */
    Date& operator=(const Date&) = default;
};

#endif // DATE_H 