#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <string>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;
using std::to_string;

/**
 * @class Time
 * @brief Class for handling time values
 *
 * Provides functionality for storing and manipulating time values
 * in 24-hour format, including validation and formatting operations.
 *
 * @author Max Wong
 * @version 01
 * @date 11 Oct 2024
 */
class Time
{
public:
    /**
     * @brief Default constructor
     *
     * Creates a time set to 00:00
     */
    Time();

    /**
     * @brief Parameterized constructor
     *
     * @param hour Hour in 24-hour format (0-23)
     * @param minute Minute (0-59)
     * @pre Parameters must form a valid time
     */
    Time(int hour, int minute);

    /**
     * @brief String constructor
     *
     * Constructs time from string in format "HH:MM"
     *
     * @param timeString String containing time in "HH:MM" format
     * @pre timeString must be in correct format
     */
    Time(const string& timeString);

    /**
     * @brief Gets the hour
     *
     * @return Hour in 24-hour format (0-23)
     */
    int GetHour() const;

    /**
     * @brief Gets the minute
     *
     * @return Minute (0-59)
     */
    int GetMinute() const;

    /**
     * @brief Sets the hour
     *
     * @param hour Hour to set (0-23)
     */
    void SetHour(int hour);

    /**
     * @brief Sets the minute
     *
     * @param minute Minute to set (0-59)
     */
    void SetMinute(int minute);

    /**
     * @brief Checks if the time is valid
     *
     * Verifies hour and minute form a valid time
     *
     * @return true if time is valid, false otherwise
     */
    bool isValid() const;

    /**
     * @brief Converts time to string
     *
     * @return String in format "HH:MM"
     */
    string toString() const;

private:
    int m_hour;    ///< Hour in 24-hour format (0-23)
    int m_minute;  ///< Minute (0-59)
};

/**
 * @brief Output stream operator for Time
 *
 * @param os Output stream
 * @param t Time to output
 * @return Reference to output stream
 */
ostream& operator<<(ostream& os, const Time& t);

/**
 * @brief Input stream operator for Time
 *
 * @param input Input stream
 * @param t Time to input to
 * @return Reference to input stream
 */
istream& operator>>(istream& input, Time& t);

#endif // TIME_H_INCLUDED
