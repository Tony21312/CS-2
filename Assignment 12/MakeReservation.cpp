// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition

extern bool leapYear( int year );
extern Date computeCurrentDate();

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
                                  AvailRoomDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomDatabase( theAvailableRoomsDatabase )
{
}

void MakeReservation::execute()
{
   Date currentDate = computeCurrentDate();

   Date availableMonths[ 7 ];

   computeAvailableMonths( currentDate, availableMonths );

   int checkInYMCode;
   int firstDay;
   int lastDay;

   Date checkInDate;
   Date checkOutDate;

   inputCheckInDates( checkInDate, currentDate, availableMonths, checkInYMCode, firstDay, lastDay );
   inputCheckOutDates( checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay );

   cout << "\nCheck in date: " << checkInDate.getYear() << '-'
        << setw( 2 ) << setfill( '0' ) << checkInDate.getMonth() << '-'
        << setw( 2 ) << checkInDate.getDay() << endl;

   cout << "Check out date: " << checkOutDate.getYear() << '-'
        << setw( 2 ) << checkOutDate.getMonth() << '-'
        << setw( 2 ) << checkOutDate.getDay() << endl;

   bool min = 0;

   for (int n = 1; n < 6; n++)
   {
       if (availableRoomDatabase.compMinNumRooms(n, checkInDate, checkOutDate) != 0)
           min = 1;
   }

   if (min == 0)
   {
       cout << "\nThere are no rooms available!\n";
       return;
   }

   availableRoomDatabase.displayAvailableRooms( checkInDate, checkOutDate );

   const char roomTypeName[ 6 ][ 20 ] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
                                              "Superior Suite", "Deluxe Suite" };
    int roomType = 0, numRooms = 0;
    while ((roomType > 6 || roomType < 1) || availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate) == 0)
    {
        cout <<"\nSelect Room Type¡G" << endl;
        for (int n = 1; n < 6; n++)
        {
            if (availableRoomDatabase.compMinNumRooms(n, checkInDate, checkOutDate) != 0)
                cout << n << '.' << roomTypeName[n] << endl;
        }
        cout << "6.Give up\n?";
        cin >> roomType;
//        cout << availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate) << endl;
    }
    cin.ignore();
    if (roomType == 6)
        return;

    while (numRooms < 1 || numRooms > availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate))
    {
        cout << "\nNumber of rooms ( " << availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate) << " rooms available ):";
        cin >> numRooms;
    }

   availableRoomDatabase.decreaseAvailRooms( roomType, numRooms, checkInDate, checkOutDate );

   cout << "\nID Number: ";
   string idNumber;
   cin >> idNumber;

   cout << "\nName: ";
   string name;
   cin >> name;

   cout << "\nMobile Phone: ";
   string mobile;
   cin >> mobile;
   cin.ignore();

   newReservation.setReservation( roomType, numRooms, checkInDate, checkOutDate, idNumber, name, mobile );

   cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
   newReservation.displayReservation();

   reservationDatabase.pushBack( newReservation );

   cout << "\nReservation successfully!" << endl;
}

void MakeReservation::computeAvailableMonths( Date currentDate, Date availableMonths[] )
{
    int year = currentDate.getYear();
    int month = currentDate.getMonth() - 1;

    for (int n = 1; n <= 6; n++)
    {
        if (++month > 12)
        {
            month -= 12;
            year++;
            currentDate.setYear(year);
        }
        currentDate.setMonth(month);

        availableMonths[n] = currentDate;
    }

}

void MakeReservation::inputCheckInDates( Date &checkInDate, Date currentDate,
     Date availableMonths[], int &checkInYMCode, int &firstDay, int &lastDay )
{
    checkInYMCode = 0;
    while (checkInYMCode > 6 || checkInYMCode < 1)
    {
        cout << "\nPlease Input Check In Date\n\nMonth:\n";
        for (int n = 1; n <= 6; n++)
            cout << n << '.' << availableMonths[n].getYear() << '-' << availableMonths[n].getMonth() << endl;
        cout << '?';
        cin >> checkInYMCode;
    }
    cin.ignore();

    checkInDate.setYear(availableMonths[checkInYMCode].getYear());
    checkInDate.setMonth(availableMonths[checkInYMCode].getMonth());

    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (checkInYMCode == 1)
        firstDay = currentDate.getDay();
    else
        firstDay = 1;

    if(checkInYMCode == 6)
        lastDay = days[availableMonths[checkInYMCode].getMonth()] - 1;
    else
        lastDay = days[availableMonths[checkInYMCode].getMonth()];

    int day = 0;

    while (day > lastDay || day < firstDay)
    {
        cout << "\nDay ( " << firstDay << " ~ " << lastDay << " ):";
        cin >> day;
    }
    checkInDate.setDay(day);
    if (checkInYMCode == 6 && day == days[availableMonths[checkInYMCode].getMonth()] - 1)
        firstDay = lastDay;

}

void MakeReservation::inputCheckOutDates( Date &checkOutDate, Date checkInDate,
     Date availableMonths[], int checkInYMCode, int firstDay, int lastDay )
{
    int checkOutYMCode = 0;    
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    while (checkOutYMCode > 6 || checkOutYMCode < 1 || checkOutYMCode < checkInYMCode)
    {
        cout << "\nPlease Input Check Out Date\n\nMonth:\n";
        for (int n = checkInYMCode; n <= 6; n++)
        {
            if(checkInYMCode == 6 && checkInDate.getDay() == days[availableMonths[n].getMonth()] - 1)
                cout << n << '.' << availableMonths[n].getYear() << '-' << availableMonths[n].getMonth() << endl;
            if (n == checkInYMCode && checkInDate.getDay() == lastDay);

            else
                cout << n << '.' << availableMonths[n].getYear() << '-' << availableMonths[n].getMonth() << endl;         
        }
        cout << '?';
        cin >> checkOutYMCode;
    }
    cin.ignore();

    checkOutDate.setYear(availableMonths[checkOutYMCode].getYear());
    checkOutDate.setMonth(availableMonths[checkOutYMCode].getMonth());

    int day = 0;        

    if (checkOutYMCode == checkInYMCode)
        while (day > days[availableMonths[checkOutYMCode].getMonth()] || day < firstDay + 1)
        {
            cout << "\nDay ( " << firstDay + 1 << " ~ " << days[availableMonths[checkOutYMCode].getMonth()] << " ):";
            cin >> day;
        }
    else
        while (day > days[availableMonths[checkOutYMCode].getMonth()] || day < 1)
        {
            cout << "\nDay ( " << 1 << " ~ " << days[availableMonths[checkOutYMCode].getMonth()] << " ):";
            cin >> day;
        }
    cin.ignore();
    checkOutDate.setDay(day);
}