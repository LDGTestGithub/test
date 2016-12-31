#include <string>
#include <iostream>

using namespace std;

class Date
{
public:
    unsigned getDay()
    {
        return day;
    }

    unsigned getMonth()
    {
        return month;
    }

    unsigned getYear()
    {
        return year;
    }

    void setDay(unsigned _day)
    {
        day = _day;
    }

    void setMonth(unsigned _month)
    {
        month = _month;
    }

    void setYear(unsigned _year)
    {
        year = _year;
    }

    void printDate()
    {
        cout << day << "/" << month << "/" << year;
    }

private:
    unsigned day, month, year;
};
