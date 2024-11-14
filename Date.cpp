#include "Date.h"

Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 2000;
}

Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int Date::GetDay() const
{
    return m_day;
}
int Date::GetMonth() const
{
    return m_month;
}
int Date::GetYear() const
{
    return m_year;
}

void Date::SetDay(int day)
{
    m_day = day;
}
void Date::SetMonth(int month)
{
    m_month = month;
}
void Date::SetYear(int year)
{
    m_year = year;
}

string Date::SetMonthName(int month)
{
    Map<int, string> monthMap;
    monthMap.insert(1, "January");
    monthMap.insert(2, "February");
    monthMap.insert(3, "March");
    monthMap.insert(4, "April");
    monthMap.insert(5, "May");
    monthMap.insert(6, "June");
    monthMap.insert(7, "July");
    monthMap.insert(8, "August");
    monthMap.insert(9, "September");
    monthMap.insert(10, "October");
    monthMap.insert(11, "November");
    monthMap.insert(12, "December");
     if (monthMap.exists(month))
        return monthMap.get(month);
     else
        return "Invalid Month";
}

bool Date::isValid() const
{
    if (m_month < 1 || m_month > 12) return false;
    if (m_day < 1 || m_day > 31) return false;      // Simplified; leap year not considered
    if (m_month == 2 && m_day > 29) return false;   // Handle February
    return true;
}

bool Date::operator<(const Date& other) const
{
        if (this->m_year < other.m_year)
            return true;
        if (this->m_year == other.m_year)
        {
            if (this->m_month < other.m_month)
                return true;
            if (this->m_month == other.m_month)
                return this->m_day < other.m_day;
        }
        return false;
}

bool Date::operator==(const Date& other) const
{
    return this->m_year == other.m_year &&
           this->m_month == other.m_month &&
           this->m_day == other.m_day;
}

ostream& operator<<(ostream& os, const Date& date)
{
    os << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear();

    return os;
}

istream& operator>>(istream& input, Date& date)
{
    int day;
    int month;
    int year;

    input >> day;
    input >> month;
    input >> year;

    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);

    return input;
}
