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

struct WeatherData
{
    Date date;              ///< Date of the measurement
    Time time;              ///< Time of the measurement
    float windSpeed;        ///< Wind speed in m/s
    float temperature;      ///< Temperature in degrees Celsius
    float solarRadiation;   ///< Solar radiation in W/m2

    bool operator<(const WeatherData& other) const
    {
        return this->temperature < other.temperature;
    }

};

class Weather
{
public:
    Weather();
    bool loadDataFromFile(const string& filename);
    void insertIntoBST(const WeatherData& data); /////////////////////
    void insertIntoMap(int year, int month, const WeatherData& data);////////////////////////
    void calculateWindStats(int month, int year);
    void calculateTempStats(int year);
    void calculateSolarRadiation(int year);
    void writeWindTempSolar(int year);
    void calculateSPCCForMonth(int month);

private:
    Vector<WeatherData> m_data; // Storing of all weather data
    Bst<WeatherData> m_bst;

    double calculateMean(const Vector<float>& values);
    double calculateStdev(const Vector<float>& values, double mean);
    double calculateSPCC(const Vector<float>& x, const Vector<float>& y);

    Vector<WeatherData> getDataForMonth(int month);
    Vector<WeatherData> getDataForMonth(int month, int year);
    Vector<WeatherData> getDataForYear(int year);
};

#endif // WEATHER_H_INCLUDED
