#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

using std::istream;
using std::ostream;
using std::getline;
using std::string;

/**
 * @class Date
 * @brief Class for handling calendar dates
 *
 * Provides functionality for storing and manipulating calendar dates,
 * including validation and formatting operations.
 *
 * @author Max Wong
 * @version 01
 * @date 11 Oct 2024
 */
class Date {
public:
    /**
     * @brief Default constructor
     *
     * Creates a date set to January 1, 2000
     */
    Date();

    /**
     * @brief Parameterized constructor
     *
     * @param day Day of the month (1-31)
     * @param month Month of the year (1-12)
     * @param year Year
     * @pre Parameters must form a valid date
     */
    Date(int day, int month, int year);

    /**
     * @brief Gets the day of the month
     *
     * @return Day of the month (1-31)
     */
    int GetDay() const;

    /**
     * @brief Gets the month
     *
     * @return Month (1-12)
     */
    int GetMonth() const;

    /**
     * @brief Gets the year
     *
     * @return Year
     */
    int GetYear() const;

    /**
     * @brief Sets the day of the month
     *
     * @param day Day to set (1-31)
     */
    void SetDay(int day);

    /**
     * @brief Sets the month
     *
     * @param month Month to set (1-12)
     */
    void SetMonth(int month);

    /**
     * @brief Sets the year
     *
     * @param year Year to set
     */
    void SetYear(int year);

    /**
     * @brief Converts month number to name
     *
     * @param month Month number (1-12)
     * @return String containing month name
     */
    string SetMonthName(int month);

    /**
     * @brief Checks if the date is valid
     *
     * Verifies day, month, and year form a valid calendar date
     *
     * @return true if date is valid, false otherwise
     */
    bool isValid() const;

private:
    int m_day;   ///< Day of the month
    int m_month; ///< Month of the year
    int m_year;  ///< Year
};

/**
 * @brief Output stream operator for Date
 *
 * @param os Output stream
 * @param date Date to output
 * @return Reference to output stream
 */
ostream& operator<<(ostream& os, const Date& date);

/**
 * @brief Input stream operator for Date
 *
 * @param input Input stream
 * @param date Date to input to
 * @return Reference to input stream
 */
istream& operator>>(istream& input, Date& date);

#endif // DATE_H_INCLUDED
