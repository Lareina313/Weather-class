#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

#include "date.h"
#include "time.h"
#include "vector.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

/**
 * @struct WeatherData
 * @brief Structure to hold weather measurements for a specific date and time
 *
 * Contains measurements for wind speed, temperature, and solar radiation
 * along with the associated date and time of the measurements.
 */
struct WeatherData {
    Date date;              ///< Date of the measurement
    Time time;              ///< Time of the measurement
    float windSpeed;        ///< Wind speed in m/s
    float temperature;      ///< Temperature in degrees Celsius
    float solarRadiation;   ///< Solar radiation in W/m2
};

/**
 * @class Weather
 * @brief Main class for weather data analysis
 *
 * Provides functionality to load weather data from files and perform
 * various statistical analyses on the data, including wind speed,
 * temperature, and solar radiation calculations.
 *
 * @author Max Wong
 * @version 01
 * @date 11 Oct 2024
 *
 * @bug No known bugs
 */
class Weather {
public:
    /**
     * @brief Default constructor
     */
    Weather();

    /**
     * @brief Loads weather data from a CSV file
     * @param filename Path to the CSV file containing weather data
     * @return bool True if file was successfully loaded, false otherwise
     * @pre File must exist and be properly formatted
     * @post Weather data will be loaded into memory if successful
     */
    bool loadDataFromFile(const string& filename);

    /**
     * @brief Calculates wind statistics for a specific month and year
     * @param month Month number (1-12)
     * @param year Year
     * @pre Month must be between 1 and 12
     */
    void calculateWindStats(int month, int year);

    /**
     * @brief Calculates temperature statistics for an entire year
     * @param year Year to analyze
     */
    void calculateTempStats(int year);

    /**
     * @brief Calculates total solar radiation for each month in a year
     * @param year Year to analyze
     */
    void calculateSolarRadiation(int year);

    /**
     * @brief Generates a comprehensive CSV report with wind, temperature, and solar data
     * @param year Year to analyze
     * @post Creates a file named "WindTempSolar.csv" in the current directory
     */
    void writeWindTempSolar(int year);

private:
    Vector<WeatherData> m_data; // Storing of all weather data

    /**
     * @brief Calculates the mean of a set of values
     * @param values Vector of float values
     * @return double The calculated mean
     */
    double calculateMean(const Vector<float>& values);

    /**
     * @brief Calculates the standard deviation of a set of values
     * @param values Vector of float values
     * @param mean Pre-calculated mean of the values
     * @return double The calculated standard deviation
     */
    double calculateStdev(const Vector<float>& values, double mean);

    /**
     * @brief Retrieves all weather data for a specific month and year
     * @param month Month number (1-12)
     * @param year Year
     * @return Vector<WeatherData> Weather data for the specified month
     */
    Vector<WeatherData> getDataForMonth(int month, int year);

    /**
     * @brief Retrieves all weather data for a specific year
     * @param year Year
     * @return Vector<WeatherData> Weather data for the specified year
     */
    Vector<WeatherData> getDataForYear(int year);
};

#endif // WEATHER_H_INCLUDED
