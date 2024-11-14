#include "weather.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

bool loadDataFiles(Weather& analyzer);
void displayMenu();

int main()
{
    Weather analyzer;

    // Load all data files before showing menu
    cout << "Loading weather data files..." << endl;
    if (!loadDataFiles(analyzer))
    {
        cout << "Failed to load any weather data files. Exiting." << endl;
        return 1;
    }
    cout << "Data loading complete." << endl << endl;

    int choice;
    do {
        displayMenu();
        cin >> choice;

        // Clear any bad input state and ignore extra characters
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number." << endl << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                int month, year;
                cout << "Enter month (1-12): ";
                cin >> month;
                cout << "Enter year: ";
                cin >> year;

                if (cin.fail() || month < 1 || month > 12)
                {
                    cout << "Invalid input. Please enter valid month and year." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                } else
                    analyzer.calculateWindStats(month, year);
                cout << endl;
                break;
            }
            case 2:
            {
                int year;
                cout << "Enter year: ";
                cin >> year;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a valid year." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                } else
                    analyzer.calculateTempStats(year);
                cout << endl;
                break;
            }
            case 3:
            {
                int month;
                cout << "Enter month (1-12): ";
                cin >> month;

                if (month < 1 || month > 12)
                {
                    cout << "Invalid month. Please enter a month between 1 and 12." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break; // Prompt for valid input
                }
                analyzer.calculateSPCCForMonth(month);
                break;
            }
            case 4:
            {
                int year;
                cout << "Enter year: ";
                cin >> year;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a valid year." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                } else
                    analyzer.writeWindTempSolar(year);
                cout << endl;
                break;
            }
            case 5:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (true);
}

void displayMenu()
{
    cout << "Weather Data Analysis Menu:" << endl;
    cout << "1. Wind speed statistics for a specific month" << endl;
    cout << "2. Temperature statistics for a year" << endl;
    cout << "3. Calculate Sample Pearson Correlation Coefficient (sPCC) for a specific month" << endl;
    cout << "4. Generate comprehensive report (WindTempSolar.csv)" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice (1-5): ";
}

bool loadDataFiles(Weather& analyzer)
{
    string sourceFilePath = "data/data_source.txt";
    std::ifstream sourceFile(sourceFilePath);

    if (!sourceFile)
    {
        cout << "Error: Cannot open data_source.txt in data directory" << endl;
        return false;
    }

    string filename;
    bool atLeastOneFileLoaded = false;

    while (std::getline(sourceFile, filename))
    {
        if (filename.empty()) continue;

        string fullPath = "data/" + filename;
        cout << "Loading " << filename << "... ";

        if (analyzer.loadDataFromFile(fullPath))
        {
            cout << "Success" << endl;
            atLeastOneFileLoaded = true;
        } else
            cout << "Failed" << endl;
    }

    sourceFile.close();
    return atLeastOneFileLoaded;
}
