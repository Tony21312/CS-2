// AvailRoomDatabase.cpp
// Member-function definitions for class AvailRoomDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

extern bool leapYear( int year );
extern Date computeCurrentDate();
//char availFileName[] = "Available Rooms 2021-11-24.dat";
//char availFileName[] = "Available Rooms 2022-2-22.dat";
char availFileName[] = "Available Rooms 2022-5-23.dat";
//char availFileName[] = "Available Rooms 2022-5-28.dat";
//char availFileName[] = "Available Rooms blank.dat";

AvailRoomDatabase::AvailRoomDatabase()
{
   loadAvailableRooms();

   if( availRooms.size() == 0 )
      initAvailRooms(); // create available rooms information for 6 months
   else
      appendAvailRooms(); // append new available rooms information
}

AvailRoomDatabase::~AvailRoomDatabase()
{
   saveAvailableRooms();
}

void AvailRoomDatabase::loadAvailableRooms()
{
    ifstream inFile("Available Rooms.dat", ios::binary);
    if (!inFile)
    {
        cout << "Available Room could not be open." << endl;
        system("Exit");
    }
    AvailRoom temp;
    Date currentDate(computeCurrentDate());
    while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(temp)))
    {
        if (currentDate <= temp.getDate())
        {
            availRooms.push_back(temp);
//            cout << temp.getDate().getYear() << temp.getDate().getMonth() << temp.getDate().getDay() << endl;
        }

    }
    inFile.close();
}

void AvailRoomDatabase::initAvailRooms()
{
    int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if(leapYear(computeCurrentDate().getYear()))
        days[2] = 29;

    AvailRoom availRoom;
    availRoom.setDate(computeCurrentDate().getYear(), computeCurrentDate().getMonth(), computeCurrentDate().getDay());

    int year = computeCurrentDate().getYear();
    int month = computeCurrentDate().getMonth();
    int day = computeCurrentDate().getDay();
 
    for (; day <= days[month]; day++)
    {
        availRoom.setDate(year, month, day);
        availRooms.push_back(availRoom);
//        cout << availRoom.getDate().getYear() << availRoom.getDate().getMonth() << availRoom.getDate().getDay() << endl;
    }

    for (int n = month + 1, temp = month; n < temp + 6; n++)
    {
        if (++month > 12)
        {            
            month -= 12;
            year++;

            if (leapYear(year))
                days[2] = 29;
            else
                days[2] = 28;
        }

        for (day = 1; day <= days[month]; day++)
        {
            availRoom.setDate(year, month, day);
            availRooms.push_back(availRoom);
 //           cout << availRoom.getDate().getYear() << availRoom.getDate().getMonth() << availRoom.getDate().getDay() << endl;
        }
    }
}

void AvailRoomDatabase::appendAvailRooms()
{
    int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    AvailRoom availRoom;

    if (leapYear(computeCurrentDate().getYear()))
        days[2] = 29;

    int startMonth = availRooms.begin()->getDate().getMonth();
    int endMonth = (availRooms.end() - 1)->getDate().getMonth();

    int year = (availRooms.end() - 1)->getDate().getYear();
    int month = (availRooms.end() - 1)->getDate().getMonth();
    int day = 1;
    for (int n = endMonth + 1; n < startMonth + 6; n++)
    {
        if (++month > 12)
        {
            month -= 12;
            year++;
            if (leapYear(year))
                days[2] = 29;
            else
                days[2] = 28;
        }
        for (day = 1; day <= days[month]; day++)
        {
            availRoom.setDate(year, month, day);
            availRooms.push_back(availRoom);
//            cout << availRoom.getDate().getYear() << availRoom.getDate().getMonth() << availRoom.getDate().getDay() << endl;
        }
    }
    
}

void AvailRoomDatabase::displayAvailableRooms( Date checkInDate, Date checkOutDate )
{
   cout << "\nThe number of available rooms of each room type:\n\n";
   cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

   vector< AvailRoom >::iterator checkInIterator;
   vector< AvailRoom >::iterator checkOutIterator;

   findIterators( checkInDate, checkOutDate, checkInIterator, checkOutIterator );

   for( vector< AvailRoom >::iterator it = checkInIterator; it < checkOutIterator; ++it )
      cout << it->getDate().getYear() << "-"
           << setw( 2 ) << setfill( '0' ) << it->getDate().getMonth() << "-"
           << setw( 2 ) << it->getDate().getDay()
           << setw( 16 ) << setfill( ' ' ) << it->getAvailRoom( 1 )
           << setw( 14 ) << it->getAvailRoom( 2 )
           << setw( 19 ) << it->getAvailRoom( 3 )
           << setw( 17 ) << it->getAvailRoom( 4 )
           << setw( 15 ) << it->getAvailRoom( 5 ) << "\n";
}

int AvailRoomDatabase::compMinNumRooms( int roomType,
                       const Date &checkInDate, const Date &checkOutDate )
{
    int min = 10;
    for (int n = 0; n < availRooms.size(); n++)
    {        
        if (availRooms[n].getDate() == checkOutDate)
            break;
        if (availRooms[n].getDate() >= checkInDate)
        {
//            cout << min << ' ' << availRooms[n].getAvailRoom(roomType) << endl;
            if (availRooms[n].getAvailRoom(roomType) < min)
                min = availRooms[n].getAvailRoom(roomType);
        }
    }
    return min;
}

void AvailRoomDatabase::decreaseAvailRooms( int roomType, int numRooms,
                        const Date &checkInDate, const Date &checkOutDate )
{
    for (int n = 0; n < availRooms.size(); n++)
    {
        if (availRooms[n].getDate() >= checkInDate)
            availRooms[n].decreaseAvailRooms(roomType, numRooms);
        
        if (availRooms[n].getDate() == checkOutDate)
            break;
    }
}

void AvailRoomDatabase::saveAvailableRooms()
{
    ofstream outFile("Available Rooms.dat", ios::binary);
    if (!outFile)
    {
        cout << "Available Rooms could not be open." << endl;
        system("Exit");
    }
    for (int n = 0; n < availRooms.size(); n++)
        outFile.write(reinterpret_cast<const char*>(&availRooms[n]), sizeof(availRooms[n]));
    outFile.close();
}

void AvailRoomDatabase::findIterators( const Date &checkInDate, const Date &checkOutDate,
                                       vector< AvailRoom >::iterator &checkInIterator,
                                       vector< AvailRoom >::iterator &checkOutIterator )
{
    for (int n = 0; n < availRooms.size(); n++)
    {
        if (availRooms[n].getDate() == checkInDate)
            checkInIterator = availRooms.begin() + n;

        if (availRooms[n].getDate() == checkOutDate)
        {
            checkOutIterator = availRooms.begin() + n;
            break;
        }    
    }
    //cout << checkInIterator->getDate().getYear() << checkInIterator->getDate().getMonth() << checkInIterator->getDate().getDay() << endl;
    //cout << checkOutIterator->getDate().getYear() << checkOutIterator->getDate().getMonth() << checkOutIterator->getDate().getDay() << endl;
}