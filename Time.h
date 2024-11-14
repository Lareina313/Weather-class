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
 * @brief Class for handling time values in 24-hour format
 *
 * The Time class provides functionality for storing, manipulating, and validating time values
 * in a 24-hour format (HH:MM), including formatting operations and comparison with other time
 * instances.
 *
 * @author Max Wong
 * @version 1.0
 * @date 11 Nov 2024
 */
class Time
{
public:
    /**
     * @brief Default constructor
     *
     * Initializes the time to 00:00 (midnight).
     */
    Time();

    /**
     * @brief Parameterized constructor
     *
     * Constructs a Time object from the provided hour and minute values.
     *
     * @param hour Hour in 24-hour format (0-23).
     * @param minute Minute (0-59).
     * @pre The provided hour and minute must form a valid time.
     */
    Time(int hour, int minute);

    /**
     * @brief String constructor
     *
     * Constructs a Time object from a string representation in the "HH:MM" format.
     *
     * @param timeString String containing time in the format "HH:MM".
     * @pre The timeString must be in the correct "HH:MM" format.
     */
    Time(const string& timeString);

    /**
     * @brief Gets the hour
     *
     * Returns the hour stored in the Time object.
     *
     * @return The hour in 24-hour format (0-23).
     */
    int GetHour() const;

    /**
     * @brief Gets the minute
     *
     * Returns the minute stored in the Time object.
     *
     * @return The minute (0-59).
     */
    int GetMinute() const;

    /**
     * @brief Sets the hour
     *
     * Sets the hour for the Time object.
     *
     * @param hour The hour to set (0-23).
     * @pre The hour must be between 0 and 23 (inclusive).
     */
    void SetHour(int hour);

    /**
     * @brief Sets the minute
     *
     * Sets the minute for the Time object.
     *
     * @param minute The minute to set (0-59).
     * @pre The minute must be between 0 and 59 (inclusive).
     */
    void SetMinute(int minute);

    /**
     * @brief Checks if the time is valid
     *
     * Verifies that the hour and minute form a valid time. This function ensures that the
     * hour is in the range [0, 23] and the minute is in the range [0, 59].
     *
     * @return true if the time is valid, false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Converts the time to a string
     *
     * Converts the Time object to a string representation in the "HH:MM" format.
     *
     * @return A string representing the time in the "HH:MM" format.
     */
    string toString() const;

    /**
     * @brief Comparison operator for less than
     *
     * Compares the current Time object with another Time object to determine if the current
     * time is earlier than the other time.
     *
     * @param other The Time object to compare with.
     * @return true if the current time is earlier than the other time, false otherwise.
     */
    bool operator<(const Time& other) const;

private:
    int m_hour;    ///< Hour in 24-hour format (0-23)
    int m_minute;  ///< Minute (0-59)
};

/**
 * @brief Output stream operator for Time
 *
 * Overloads the << operator to output a Time object to an output stream in the "HH:MM" format.
 *
 * @param os The output stream to write to.
 * @param t The Time object to output.
 * @return A reference to the output stream (os).
 */
ostream& operator<<(ostream& os, const Time& t);

/**
 * @brief Input stream operator for Time
 *
 * Overloads the >> operator to read a Time object from an input stream. The input should
 * be in the "HH:MM" format.
 *
 * @param input The input stream to read from.
 * @param t The Time object to input to.
 * @return A reference to the input stream (input).
 */
istream& operator>>(istream& input, Time& t);

#endif // TIME_H_INCLUDED
