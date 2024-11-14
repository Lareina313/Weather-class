#include "weather.h"


Weather::Weather()
{
    Vector<WeatherData> m_data;
    Date date;
    Time time;
    float windSpeed = 0.0;
    float temperature = 0.0;
    float solarRadiation = 0.0;
}

bool Weather::loadDataFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    string header;
    getline(file, header); // Read the header line

    // Initialize column indices
    int wastIndex = -1, windIndex = -1, tempIndex = -1, solarIndex = -1;
    int columnIndex = 0;
    string column; // Hold current column name

    // Parse header to determine column indices
    for (size_t i = 0; i <= header.length(); ++i)
    {
        if (i == header.length() || header[i] == ',') // End of line or comma
        {
            if (column == "WAST") wastIndex = columnIndex;
            else if (column == "S") windIndex = columnIndex;
            else if (column == "T") tempIndex = columnIndex;
            else if (column == "SR") solarIndex = columnIndex;

            // Move to the next column
            column.clear(); // Reset for the next column
            columnIndex++;
        } else
            column += header[i]; // Build column name character by character
    }

    // Check if all expected columns were found
    if (wastIndex == -1 || windIndex == -1 || tempIndex == -1 || solarIndex == -1)
    {
        cout << "Error: Missing expected columns in the header." << endl;
        return false;
    }

    // Read data lines
    string line;
    while (getline(file, line))
    {
        Vector<string> cells; // Vector to hold the split cell values
        string cell; // To hold the current cell value
        columnIndex = 0; // Reset column index for data line

        // Parse the line into cells
        for (size_t i = 0; i <= line.length(); ++i)
        {
            if (i == line.length() || line[i] == ',')
            {
                cells.Add(cell); // Add the cell value to the vector
                cell.clear(); // Reset for the next cell
                columnIndex++;
            } else
                cell += line[i]; // Build the cell value character by character
        }

        // Ensure enough data was read
        if (cells.size() > wastIndex && cells.size() > windIndex &&
            cells.size() > tempIndex && cells.size() > solarIndex)
        {
            WeatherData data;

            // Parse date and time
            string wastStr = cells[wastIndex];
            size_t spacePos = wastStr.find(' ');
            string dateStr = wastStr.substr(0, spacePos);
            string timeStr = wastStr.substr(spacePos + 1);

            // Parse date
            int day = (dateStr[0] - '0') * 10 + (dateStr[1] - '0');
            int month = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
            int year = (dateStr[6] - '0') * 1000 + (dateStr[7] - '0') * 100 + (dateStr[8] - '0') * 10 + (dateStr[9] - '0');
            data.date = Date(day, month, year);

            // Parse time
            int hour = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
            int minute = (timeStr[3] - '0') * 10 + (timeStr[4] - '0');
            data.time = Time(hour, minute);

            // Parse measurements
            if (!cells[windIndex].empty() && cells[windIndex] != "N/A")
            {
                data.windSpeed = stof(cells[windIndex]);
            }
            if (!cells[tempIndex].empty() && cells[tempIndex] != "N/A")
            {
                data.temperature = stof(cells[tempIndex]);
            }
            if (!cells[solarIndex].empty() && cells[solarIndex] != "N/A")
            {
                float solar = stof(cells[solarIndex]);
                if (solar >= 100)   // Only include values more than 100 W/m2
                    data.solarRadiation = solar;
            }
            m_data.Add(data);
        }
    }
    return true;
}

Vector<float> Weather::bstToVector(Bst<float>& bst) const
{
    Vector<float> result;
    inOrderToVector(bst.getRoot(), result);
    return result;
}

// Recursive helper function for in-order traversal
void Weather::inOrderToVector(Node<float>* node, Vector<float>& vec) const
{
    if (node != nullptr)
    {
        inOrderToVector(node->left, vec);
        vec.Add(node->data);
        inOrderToVector(node->right, vec);
    }
}


void Weather::calculateWindStats(int month, int year)
{
    Vector<WeatherData> monthData = getDataForMonth(month, year);
    if (monthData.isEmpty())
    {
        cout << Date().SetMonthName(month) << " " << year << ": No Data" << endl;
        return;
    }

    Bst<float> monthWindBST;
    for (int i = 0; i < monthData.size(); i++)
    {
        monthWindBST.insert(monthData[i].windSpeed * 3.6); // Convert to km/h
    }
    double mean = calculateMean(monthWindBST);
    double stdev = calculateStdev(monthWindBST, mean);

    cout << Date().SetMonthName(month) << " " << year << ":" << endl;
    cout << "Average speed: " << mean << " km/h" << endl;
    cout << "Sample stdev: " << stdev << endl;
}

double Weather::calculateMean(Bst<float>& bst)
{
    int count = bst.count();
    if (count == 0) return 0; // No data in BST
    double sum = bst.sum();
    return sum / count;
}

double Weather::calculateStdev(Bst<float>& bst, double mean)
{
    Vector<float> values = bstToVector(bst); // Convert bst to vector for easier variance calculation to each values
    if (values.size() < 2)
        return 0;
    double sumSquares = 0;
    for (int i = 0; i < values.size(); i++)
    {
        double diff = values[i] - mean;
        sumSquares += diff * diff;
    }
    return sqrt(sumSquares / (values.size() - 1));
}

double Weather::calculateSPCC(const Vector<float>& x, const Vector<float>& y)
{
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_x2 = 0.0;
    double sum_y2 = 0.0;

    for (int i = 0; i < x.size(); i++)
    {
        sum_x += x[i];        // Sum of x
        sum_y += y[i];        // Sum of y
        sum_xy += x[i] * y[i]; // Sum of x * y
        sum_x2 += x[i] * x[i]; // Sum of x^2
        sum_y2 += y[i] * y[i]; // Sum of y^2
    }

    double numerator = x.size() * sum_xy - sum_x * sum_y;
    double denominator = sqrt((x.size() * sum_x2 - sum_x * sum_x) * (x.size() * sum_y2 - sum_y * sum_y));

    if (denominator == 0)
        return 0;

    return numerator / denominator;
}

void Weather::calculateSPCCForMonth(int month)
{
    Vector<float> wind_speed;
    Vector<float> temp;
    Vector<float> solar_radiation;

    for (int i = 0; i < m_data.size(); i++)
    {
        WeatherData data = m_data[i];
        if (data.date.GetMonth() == month)
        {
            wind_speed.Add(data.windSpeed);
            temp.Add(data.temperature);
            solar_radiation.Add(data.solarRadiation);
        }
    }

    double s_t = calculateSPCC(wind_speed, temp);
    double s_r = calculateSPCC(wind_speed, solar_radiation);
    double t_r = calculateSPCC(temp, solar_radiation);

    // Output the results
    cout << "Sample Pearson Correlation Coefficient for " << Date().SetMonthName(month) << endl;
    cout << "S_T: " << s_t << endl;
    cout << "S_R: " << s_r << endl;
    cout << "T_R: " << t_r << endl;

}

Vector<WeatherData> Weather::getDataForMonth(int month, int year)
{
    Vector<WeatherData> monthData;
    for (int i = 0; i < m_data.size(); i++)
    {
        if (m_data[i].date.GetMonth() == month && m_data[i].date.GetYear() == year)
            monthData.Add(m_data[i]);
    }
    return monthData;
}

Vector<WeatherData> Weather::getDataForYear(int year)
{
    Vector<WeatherData> yearData;
    for (int i = 0; i < m_data.size(); i++)
    {
        if (m_data[i].date.GetYear() == year)
            yearData.Add(m_data[i]);
    }
    return yearData;
}

void Weather::calculateTempStats(int year)
{
    Vector<WeatherData> yearData = getDataForYear(year);
    if (yearData.isEmpty())
    {
        cout << year << ": No Data" << endl;
        return;
    }

    cout << year << endl;
    // Process each month
    for (int month = 1; month <= 12; month++)
    {
        Bst<float> yearTempBST;
        Vector<WeatherData> monthData = getDataForMonth(month, year);

        // Collect valid temperature readings for the month
        for (int i = 0; i < monthData.size(); i++)
        {
            yearTempBST.insert(monthData[i].temperature);
        }

        if (yearTempBST.count() > 0)
        {
            double mean = calculateMean(yearTempBST);
            double stdev = calculateStdev(yearTempBST, mean);
            cout << Date().SetMonthName(month) << ": average: " << mean << " degrees C, stdev: " << stdev << endl;
        } else
            cout << Date().SetMonthName(month) << ": No Data" << endl;
    }
}

void Weather::calculateSolarRadiation(int year)
{
    Vector<WeatherData> yearData = getDataForYear(year);
    if (yearData.isEmpty())
    {
        cout << year << ": No Data" << endl;
        return;
    }

    cout << year << endl;

    // Process each month
    for (int month = 1; month <= 12; month++)
    {
        Vector<WeatherData> monthData = getDataForMonth(month, year);
        float totalRadiation = 0.0f;
        bool hasData = false;

        // Sum up radiation values for the month
        for (int i = 0; i < monthData.size(); i++)
        {
            if (monthData[i].solarRadiation >= 100)  // Only include values ≥ 100 W/m2
            {
                // Convert W/m2 to kWh/m2
                totalRadiation += (monthData[i].solarRadiation / 1000.0f); // f to treat as float
                hasData = true;
            }
        }

        if (hasData)
            cout << Date().SetMonthName(month) << ": " << totalRadiation << " kWh/m2" << endl;
        else
            cout << Date().SetMonthName(month) << ": No Data" << endl;
    }
}

double Weather::calculateMAD(Bst<float>& bst, double mean)
{
    Vector<float> values = bstToVector(bst);
    if (values.isEmpty())
        return 0;
    double sumAbsDiff = 0;
    for (int i = 0; i < values.size(); i++)
    {
        sumAbsDiff += abs(values[i] - mean);
    }
    return sumAbsDiff / values.size();
}

void Weather::writeWindTempSolar(int year)
{
    ofstream outFile("WindTempSolar.csv");
    if (!outFile)
    {
        cout << "Error: Could not create output file WindTempSolar.csv" << endl;
        return;
    }

    Vector<WeatherData> yearData = getDataForYear(year);
    if (yearData.isEmpty())
    {
        outFile << year << endl << "No Data" << endl;
        outFile.close();
        return;
    }

    // Write the year header
    outFile << year << endl;
    outFile << "Month,\"Average Wind Speed(stdev, mad)\",\"Average Ambient Temperature(stdev, mad)\",Solar Radiation" << endl;

    // Process each month
    for (int month = 1; month <= 12; month++)
    {
        Vector<WeatherData> monthData = getDataForMonth(month, year);
        if (monthData.isEmpty()) continue; // Skip months with no data

        Bst<float> windSpeedBst;
        Bst<float> temperatureBst;
        float totalRadiation = 0.0f;
        bool hasWind = false, hasTemp = false, hasSolar = false;

        // Collect data for the month
        for (int i = 0; i < monthData.size(); i++)
        {
            // Wind speed
            if (monthData[i].windSpeed >= 0)
            {
                windSpeedBst.insert(monthData[i].windSpeed * 3.6); // Convert to km/h
                hasWind = true;
            }

            // Temperature
            temperatureBst.insert(monthData[i].temperature);
            hasTemp = true;

            // Solar radiation
            if (monthData[i].solarRadiation >= 100)
            {
                totalRadiation += (monthData[i].solarRadiation / 1000.0f); // Convert to kWh/m2
                hasSolar = true;
            }
        }

        // Calculate statistics and write to file
        outFile << Date().SetMonthName(month) << ",";

        // Wind speed stats
        if (hasWind)
        {
            double windMean = calculateMean(windSpeedBst);
            double windStdev = calculateStdev(windSpeedBst, windMean);
            double windMAD = calculateMAD(windSpeedBst, windMean);
            outFile << "\"" << windMean << "(" << windStdev << ", " << windMAD << ")\"";
        }
        outFile << ",";

        // Temperature stats
        if (hasTemp)
        {
            double tempMean = calculateMean(temperatureBst);
            double tempStdev = calculateStdev(temperatureBst, tempMean);
            double tempMAD = calculateMAD(temperatureBst, tempMean);
            outFile << "\"" << tempMean << "(" << tempStdev << ", " << tempMAD << ")\"";
        }
        outFile << ",";

        // Solar radiation
        if (hasSolar)
            outFile << totalRadiation;

        outFile << endl;
    }

    outFile.close();
    cout << "Data has been written to WindTempSolar.csv" << endl;
}
