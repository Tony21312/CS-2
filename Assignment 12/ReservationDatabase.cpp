// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

ReservationDatabase::ReservationDatabase()
{
	loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
	saveToReservationFile();
}

void ReservationDatabase::loadReservations()
{
	ifstream inFile("Reservations.dat", ios::binary);
	if (!inFile)
	{
		cout << "Reservations could not be open !" << endl;
		system("Exit");
	}

	Reservation temp;
	while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(temp)))
	{		
		pushBack(temp);
//		temp.displayReservation();
	}
	inFile.close();
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

int ReservationDatabase::numReservations( string idNumber )
{
	for (int n = 0; n < reservations.size(); n++)
	{
		if (reservations[n].equalID(idNumber, reservations[n].getIDNumber()))
			return reservations[n].getNumRooms();
	}
	return 0;

}

void ReservationDatabase::displayReservations( string idNumber )
{
	cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";

   for( vector< Reservation >::iterator it = reservations.begin(); it < reservations.end(); it++ )
      if( it->equalID( idNumber, it->getIDNumber() ) )
         it->displayReservation();
}

void ReservationDatabase::saveToReservationFile()
{
	ofstream outFile("Reservations.dat", ios::binary);
	if (!outFile)
	{
		cout << "file could not be open." << endl;
		system("Exit");
	}
	for (int n = 0; n < reservations.size(); n++)
	{
		outFile.write(reinterpret_cast<const char*>(&reservations[n]), sizeof(reservations[n]));
	}
	outFile.close();
}