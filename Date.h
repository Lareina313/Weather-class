#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include "map.h"

using std::istream;
using std::ostream;
using std::getline;
using std::string;

/**
 * @class Date
 * @brief Class for handling calendar dates
 *
 * The Date class provides functionality for storing and manipulating calendar dates,
 * including validation, setting, and formatting operations. The class also supports
 * comparison operators and can be used to interact with dates in a variety of formats.
 *
 * @author Max Wong
 * @version 1.0
 * @date 11 Nov 2024
 */
class Date {
public:
    /**
     * @brief Default constructor
     *
     * Initializes the Date object to a default value of January 1, 2000.
     */
    Date();

    /**
     * @brief Parameterized constructor
     *
     * Creates a Date object with the specified day, month, and year.
     *
     * @param day The day of the month (1-31)
     * @param month The month of the year (1-12)
     * @param year The year (e.g., 2024)
     * @pre The provided day, month, and year must form a valid calendar date.
     */
    Date(int day, int month, int year);

    /**
     * @brief Gets the day of the month
     *
     * Returns the day stored in the Date object (1-31).
     *
     * @return The day of the month.
     */
    int GetDay() const;

    /**
     * @brief Gets the month of the year
     *
     * Returns the month stored in the Date object (1-12).
     *
     * @return The month of the year.
     */
    int GetMonth() const;

    /**
     * @brief Gets the year
     *
     * Returns the year stored in the Date object.
     *
     * @return The year.
     */
    int GetYear() const;

    /**
     * @brief Sets the day of the month
     *
     * Sets the day for the Date object.
     *
     * @param day The day to set (1-31).
     * @pre The day must be valid for the current month and year.
     */
    void SetDay(int day);

    /**
     * @brief Sets the month of the year
     *
     * Sets the month for the Date object.
     *
     * @param month The month to set (1-12).
     * @pre The month must be a valid calendar month.
     */
    void SetMonth(int month);

    /**
     * @brief Sets the year
     *
     * Sets the year for the Date object.
     *
     * @param year The year to set.
     */
    void SetYear(int year);

    /**
     * @brief Converts a month number to its corresponding name
     *
     * Converts the month number (1-12) to a string representing the full month name.
     *
     * @param month The month number (1-12).
     * @return The full name of the month (e.g., "January", "February").
     * @pre The month number must be between 1 and 12.
     */
    string SetMonthName(int month);

    /**
     * @brief Checks if the date is valid
     *
     * Validates if the day, month, and year form a valid calendar date, taking into account
     * leap years, month length, etc.
     *
     * @return true if the date is valid, false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Comparison operator for less than
     *
     * Compares the current Date object with another Date object to determine if the current
     * Date is earlier than the other.
     *
     * @param other The Date object to compare with.
     * @return true if the current Date is earlier than the other Date.
     */
    bool operator<(const Date& other) const;

    /**
     * @brief Comparison operator for equality
     *
     * Compares the current Date object with another Date object to determine if they represent
     * the same calendar date.
     *
     * @param other The Date object to compare with.
     * @return true if the current Date is equal to the other Date.
     */
    bool operator==(const Date& other) const;

private:
    int m_day;   ///< Day of the month (1-31)
    int m_month; ///< Month of the year (1-12)
    int m_year;  ///< Year (e.g., 2024)
};

/**
 * @brief Output stream operator for Date
 *
 * Overloads the << operator to output a Date object to an output stream in a human-readable format.
 *
 * @param os The output stream to write to.
 * @param date The Date object to output.
 * @return A reference to the output stream (os).
 */
ostream& operator<<(ostream& os, const Date& date);

/**
 * @brief Input stream operator for Date
 *
 * Overloads the >> operator to read a Date object from an input stream. The format of the input
 * should match the expected format for the Date constructor (e.g., day, month, year).
 *
 * @param input The input stream to read from.
 * @param date The Date object to input to.
 * @return A reference to the input stream (input).
 */
istream& operator>>(istream& input, Date& date);


#endif // DATE_H_INCLUDED
