// ticketmanager.cpp
// Noah Tucker, Richard Stadnick, Derek Morgan and 
// This program is where the ticketmanager class is defined
//This file needs more comments

#include "ticketmanager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

TicketManager::TicketManager(){ //load files create 2-D array of seat structs
    ifstream seat_availability;
    seat_availability.open("./SeatAvailability.dat");
    char ch;
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            seat_availability >> ch;
            if(ch == '#'){
                seats[row][col].available = true;
            }else if(ch == '*'){
                seats[row][col].available = false;
            }
            if(row < 4){
                seats[row][col].price = 12.50;
            }else if(row >= 4 && row < 8){
                seats[row][col].price = 10.00;
            }else if(row >= 8 && row < 12){
                seats[row][col].price = 8.00;
            }else{
                seats[row][col].price = 5.00;
            }
            
        }
    }
}

void TicketManager::displayChart(){  //represent seats by a chart of * and # chars
    cout << setw(39) << "012345678901234567890123456789\n";
    for(int row = 0; row < ROWS; row++){
        cout << setw(4) << "row " << setw(3) << row << " ";
        for(int col = 0; col < COLS; col++){
            if(seats[row][col].available)
                cout << '#';
            else{
                cout << '*';
            }
        }
        cout << '\n';
    }
}

bool TicketManager::ticketRequest(int num_seats, int row_num, int start_seat){ //determine if requested seats are available and give the seating price
    bool available = true;
    int seat = start_seat;
    if(start_seat > COLS || start_seat < 0 || (start_seat + num_seats) > COLS || row_num > ROWS || row_num < 0){
        return false;
    }
    while(seat < (start_seat + num_seats) && available){
        if(!seats[row_num][seat].available){
            available = false;
        }
        seat++;
    }
    return available;
}
void TicketManager::purchase(){ //purchase seats update date accordingly
	for (int row = 0; row < 15; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			cout << theater[row][col].cost<< " "; //did you mean seats[row][col].cost
		}

		cout << endl;
	}
}


void TicketManager::report()					//display sales report
{
	int seatsAvailable = 0,					// accumulators
		seatsUnavailable = 0;
	double totalSales = 0;

	for (int row = 0; row < ROWS; row++)			// calculating number of seats available, unavailable, and total sales
	{
		for (int col = 0; col < COLS; col++)
		{
			if (seats[row][col].available == true)
			{
				seatsAvailable++;
			}
			else if (seats[row][col].available == false)
			{
				seatsUnavailable++;
				totalSales += seats[row][col].price;
			}
		}
	}

	// displaying sales report on number of seats available/unavailable and total sales
	cout << setw(20) << left << "Seats Available" << setw(22) << left << "Seats Unavailable";
	cout << setw(10) << "Total Money Collected" << endl;
	cout << "===============================================================" << endl;
	cout << setw(20) << left << seatsAvailable << setw(22) << left << seatsUnavailable;
	cout << setprecision(2) << fixed << showpoint;
	cout << setw(10) << totalSales << endl;
}

TicketManager::~TicketManager(){ //write to and close files

}

