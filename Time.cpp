#include "Time.h"

Time::Time()
{
    m_hour = 0;
    m_minute = 0;
}

Time::Time(int hour, int minute)
{
    m_hour = hour;
    m_minute = minute;
}

Time::Time(const string& timeString)
{
    // Convert time string to int and allocate into variables
    int colon = timeString.find(':');
    m_hour = stoi(timeString.substr(0,colon));
    m_minute = stoi(timeString.substr(colon + 1));
}

int Time::GetHour() const
{
    return m_hour;
}

int Time::GetMinute() const
{
    return m_minute;
}

void Time::SetHour(int hour)
{
    m_hour = hour;
}

void Time::SetMinute(int minute)
{
    m_minute = minute;
}

bool Time::isValid() const
{
    return (m_hour >= 0 && m_hour < 24) && (m_minute >= 0 && m_minute < 60);
}

string Time::toString() const
{
    return to_string(m_hour) + ":" + to_string(m_minute);
}
ostream& operator<<(ostream& os, const Time& t)
{
    os << t.toString();
    return os;
}

istream& operator>>(istream& input, Time& t)
{
    string timeString;
    input >> timeString;
    t = Time(timeString);
    return input;
}
