// Date.cpp
// Member-function definitions for class Date.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "Date.h"

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
}

void Date::setMonth( int m )
{
   month = ( m <= 12 && m >= 1 ) ? m : 1; // sets month
}

void Date::setDay( int d )
{
   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( month == 2 && leapYear( year ) )
      day = ( d <= 29 && d >= 1 ) ? d : 1;
   else
      day = ( d <= days[ month ] && d >= 1 ) ? d : 1;
}

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{
   if( year < date2.year )
      return true;
   if( year > date2.year )
      return false;

   if( month < date2.month )
      return true;
   if( month > date2.month )
      return false;

   if( day < date2.day )
      return true;

   return false;
}

bool Date::operator<=( const Date &date2 )
{
   return ( *this < date2 ) || ( *this == date2 );
}

bool Date::operator>=( const Date &date2 )
{
   return !( *this < date2 );
}

// return *this - date2 provided that *this > date2
int Date::operator-( const Date &date2 )
{
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (date2.year == year)
    {
        if (date2.month == month)
        {
            return day - date2.day;
        }
        else if (date2.month > month)
            return 0;
        else
        {
            int temp = 0;
            for (int n = date2.month; n < month; n++)
            {
                if (n == date2.month)
                    temp += (days[n] - date2.day);
                else
                    temp += days[n];
            }
            temp += day;
            return temp;
        }
    }
    else if (year < date2.year)
        return 0;
    else
    {
        int temp = 0;

        // calculate how many days between (date2.year + 1) and year
        for (int n = date2.year + 1; n < year; n++)
        {
            if (leapYear(n))
                temp += 366;
            else
                temp += 365;
        }

        // calculate how many days from (year/ 1/ 1) to (year/ month/ day).
        if (leapYear(year))
            days[2] = 29;
        for (int n = 1; n <= month; n++)
        {
            if (n < month)
                temp += days[n];
            else
                temp += day;
        }

        // calculate how many days
        //from(date2.year/date2.month/date2.day) to (date2.year/ 12/ 31).
        if (!leapYear(date2.year))
            days[2] = 28;
        for (int n = date2.month; n <= 12; n++)
        {
            if (n == date2.month)
                temp += days[n] - date2.day;
            else
                temp += days[n];
        }
        return temp;
    }
}