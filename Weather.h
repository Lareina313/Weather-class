#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

#include "date.h"
#include "time.h"
#include "vector.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include "bst.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

/**
 * @struct WeatherData
 * @brief Structure to hold weather measurement data
 *
 * Holds information about a specific weather measurement, including the date, time,
 * wind speed, temperature, and solar radiation.
 */
struct WeatherData
{
    Date date;              ///< Date of the measurement
    Time time;              ///< Time of the measurement
    float windSpeed;        ///< Wind speed in m/s
    float temperature;      ///< Temperature in degrees Celsius
    float solarRadiation;   ///< Solar radiation in W/m²
};

/**
 * @class Weather
 * @brief Class for managing and processing weather data
 *
 * Provides functionality for loading, analyzing, and processing weather data, including
 * calculations for various weather statistics like wind speed, temperature, solar radiation,
 * and statistical measures like mean, standard deviation, and correlation coefficients.
 * Data is loaded from and written to a file, and various statistical methods are provided
 * for analyzing the weather data.
 *
 * @author Max Wong
 * @version 1.0
 * @date 11 Nov 2024
 */
class Weather
{
public:
    /**
     * @brief Default constructor
     *
     * Initializes the Weather object, setting up any required data structures (e.g., empty data vector).
     */
    Weather();

    /**
     * @brief Loads weather data from a file
     *
     * Reads weather data from the specified file and populates the internal data structure.
     *
     * @param filename The name of the file containing weather data.
     * @return `true` if data was successfully loaded, `false` otherwise.
     */
    bool loadDataFromFile(const string& filename);

    /**
     * @brief Calculates wind statistics for a specified month and year
     *
     * Analyzes the weather data for the given month and year and calculates statistics
     * related to wind speed (mean, standard deviation, etc.).
     *
     * @param month The month (1-12) for which to calculate statistics.
     * @param year The year for which to calculate statistics.
     */
    void calculateWindStats(int month, int year);

    /**
     * @brief Calculates temperature statistics for a specified year
     *
     * Analyzes the weather data for the given year and calculates statistics related to temperature,
     * such as mean, standard deviation, etc.
     *
     * @param year The year for which to calculate statistics.
     */
    void calculateTempStats(int year);

    /**
     * @brief Calculates solar radiation statistics for a specified year
     *
     * Analyzes the weather data for the given year and calculates statistics related to solar radiation,
     * such as mean and standard deviation.
     *
     * @param year The year for which to calculate statistics.
     */
    void calculateSolarRadiation(int year);

    /**
     * @brief Writes wind, temperature, and solar radiation data to a file
     *
     * Writes the calculated statistics for wind speed, temperature, and solar radiation
     * for the specified year to an output file.
     *
     * @param year The year for which to write the data.
     */
    void writeWindTempSolar(int year);

    /**
     * @brief Calculates the Spearman's rank correlation coefficient (SPCC) for a given month
     *
     * Calculates the correlation between wind speed, temperature, and solar radiation for a given month.
     *
     * @param month The month for which to calculate the SPCC.
     */
    void calculateSPCCForMonth(int month);

private:
    Vector<WeatherData> m_data;  ///< Vector holding all the weather data

    /**
     * @brief Converts a binary search tree (BST) to a vector
     *
     * Converts a binary search tree containing weather data (such as wind speed or temperature)
     * into a vector for easier processing.
     *
     * @param bst The binary search tree to convert.
     * @return A vector containing the elements of the BST.
     */
    Vector<float> bstToVector(Bst<float>& bst) const;

    /**
     * @brief Traverses a BST in-order and adds elements to a vector
     *
     * Recursively traverses a binary search tree in-order and adds the elements to a vector.
     *
     * @param node The current node of the BST.
     * @param vec The vector to store the elements.
     */
    void inOrderToVector(Node<float>* node, Vector<float>& vec) const;

    /**
     * @brief Calculates the mean of a binary search tree (BST)
     *
     * Calculates the mean (average) value of the elements in the BST.
     *
     * @param bst The binary search tree containing the data.
     * @return The mean of the elements in the BST.
     */
    double calculateMean(Bst<float>& bst);

    /**
     * @brief Calculates the standard deviation of a BST
     *
     * Calculates the standard deviation of the elements in the binary search tree.
     *
     * @param bst The binary search tree containing the data.
     * @param mean The mean value used to calculate the standard deviation.
     * @return The standard deviation of the elements in the BST.
     */
    double calculateStdev(Bst<float>& bst, double mean);

    /**
     * @brief Calculates Spearman's rank correlation coefficient (SPCC)
     *
     * Calculates the correlation coefficient between two sets of data (e.g., wind speed and temperature).
     *
     * @param x The first vector of data (e.g., wind speed).
     * @param y The second vector of data (e.g., temperature).
     * @return The Spearman's rank correlation coefficient.
     */
    double calculateSPCC(const Vector<float>& x, const Vector<float>& y);

    /**
     * @brief Calculates the mean absolute deviation (MAD) of a BST
     *
     * Calculates the mean absolute deviation of the elements in a binary search tree.
     *
     * @param bst The binary search tree containing the data.
     * @param mean The mean value used to calculate the MAD.
     * @return The mean absolute deviation.
     */
    double calculateMAD(Bst<float>& bst, double mean);

    /**
     * @brief Retrieves weather data for a specific month and year
     *
     * Filters the weather data for a specified month and year.
     *
     * @param month The month (1-12) for which to retrieve data.
     * @param year The year for which to retrieve data.
     * @return A vector containing the weather data for the specified month and year.
     */
    Vector<WeatherData> getDataForMonth(int month, int year);

    /**
     * @brief Retrieves weather data for a specific year
     *
     * Filters the weather data for a specified year.
     *
     * @param year The year for which to retrieve data.
     * @return A vector containing the weather data for the specified year.
     */
    Vector<WeatherData> getDataForYear(int year);
};

#endif // WEATHER_H_INCLUDED
