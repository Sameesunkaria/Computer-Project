//
//  main.cpp
//  Computer Project
//
//  Created by Samar Sunkaria on 12/28/14.
//  Copyright (c) 2015 Samar Sunkaria. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class hotel {
    string sName = "Anonymous";             // Name of the customer.
    int nRoom = 0;                          // Room number alloted.
    int nNights = 0;                        // Number of nights the room is reserved for.
public:
    void newReservation(string Name, int Nights, int Room) {        // Function to add a reservation.
        sName = Name; nNights = Nights; nRoom = Room;
    }
    void viewReservation() {                                        // Function to view customer details.
        cout << "Name:" << "\t\t" << sName << endl;
        cout << "Room:" << "\t\t" << nRoom << endl;
        cout << "Nights:" << "\t" << nNights << endl;
    }
    int getRoom() { return nRoom; }
    int getNights() { return nNights; }
    string getName() { return sName; }
    
}hotel;

int checkStatus(int nRoom);                 // To check if the room is vacant.
void newReservation();                      // To add a reservation.
void editReservation();                     // To edit a reservation.
void viewReservation();                     // To view a reservation.
void viewAllReservations();                 // To view all of the reservations.
int getNumberOfReservations();              // Returns the number of entries in the file.

int checkStatus(int nRoom) {
    int flag = 0;
    ifstream infile("database", ios::binary | ios::in);
    while (!infile.eof()) {
        infile.read((char*)&hotel, sizeof(hotel));
        if (nRoom == hotel.getRoom()) {     // Returns -1 if the room is booked/exists.
            flag = -1;
            break;
        }
    }
    infile.close();
    cout << endl << endl;
    return flag;
}

void newReservation() {
    ofstream outfile("database", ios::binary | ios::out | ios::app);    // Open/Create database.
    
    string sName;
    int nNights;
    int nRoom;
    cout << "Please enter the following details:" << endl << endl;
    cout << "Name:" << "\t\t";
    cin.ignore();
    getline(cin , sName);
    cout << "Nights:" << "\t\t";
    cin >> nNights;
    cout << "Room No.:" << "\t";
    cin >> nRoom;
    cout << endl;
    
    // Conditional Statements Begin.
    
nonZeroNights:                                                      // Checks to ensure non zero number of nights.
    if (nNights == 0){
        cout << "ERROR! You cannot book a room for 0 nights." << endl;
        cout << "Nights:" << "\t";
        cin >> nNights;
        goto nonZeroNights;
    }
    
checkRoom:
    if (checkStatus(nRoom) == -1) {                                 // Ensures that the room is not already booked.
        cout << "Sorry, the room is already booked." << endl;
        cout << "Room No." << "\t";
        cin >> nRoom;
        goto checkRoom;
    }
    
    // Conditional Statements End.
    
    hotel.newReservation(sName, nNights, nRoom);                    // Passes on the variables to the class "hotel"
    outfile.write((char*)&hotel, sizeof(hotel));
    outfile.close();
    cout << endl << endl;
}

void viewReservation() {
    ifstream infile("database", ios::binary | ios::in);
    int nRoom;
    int nNumberOfReservations = getNumberOfReservations();
    int flag = -1;
    cout << "Please enter your room number: ";
    cin >> nRoom;
    for (int i = 0; i < nNumberOfReservations; i++) {
        infile.read((char*)&hotel, sizeof(hotel));
        if (nRoom == hotel.getRoom()) {                             // Cycles through to find the required room number.
            cout << "Name:" << "\t\t" << hotel.getName() << endl;
            cout << "Nights:" << "\t\t" << hotel.getNights() << endl;
            cout << "Room No.:" << "\t" << hotel.getRoom() << endl;
            flag = 0;
        }
    }
    if (flag == -1) {
        cout << "Sorry, no record found.";
    }
    cout << endl << endl;
    infile.close();
}

void editReservation() {
    ifstream infile("database", ios::binary | ios::in);
    ofstream outfile("database", ios::binary | ios::out | ios::app);
    int nRoom;
    int nNumberOfReservations = getNumberOfReservations();
    int flag = -1;
    string reply;
    cout << "Please enter your room number: ";
    cin >> nRoom;
    for (int i = 0; i < nNumberOfReservations; i++) {
        infile.read((char*)&hotel, sizeof(hotel));
        if (nRoom == hotel.getRoom()) {                             // Cycles through to find the required room number.
            cout << "Name:" << "\t\t" << hotel.getName() << endl;
            cout << "Nights:" << "\t\t" << hotel.getNights() << endl;
            cout << "Room No.:" << "\t" << hotel.getRoom() << endl << endl;
            flag = 0;
            break;
        }
    }
    if (flag == -1) {
        cout << "Sorry, no record found.";
    }
    else {
        cout << "Are you sure you want to change this record? ";
        cin >> reply;
        if (reply == "y" || reply == "Y") {
            string sName;
            int nNights;
            cout << "Please enter the following details:" << endl << endl;
            cout << "Name:" << "\t\t";
            cin.ignore();
            getline(cin , sName);
            cout << "Nights:" << "\t\t";
            cin >> nNights;
            cout << "Room No.:" << "\t";
            cin >> nRoom;
            cout << endl;
            hotel.newReservation(sName, nNights, nRoom);
            outfile.write((char*)&hotel, sizeof(hotel));
        }
    }
    cout << endl << endl;
    outfile.close();
    infile.close();
}

void viewAllReservations() {
    ifstream infile("database", ios::binary | ios::in);
    int flag = -1;
    int nNumberOfReservations = getNumberOfReservations();
    cout << "Name" << "\t\t\t\t" << "Nights" << "\t\t" << "Room No." << endl << endl;
    for (int i = 0; i < nNumberOfReservations; i++) {
        infile.read((char*)&hotel, sizeof(hotel));
        cout << setw(20) << left << hotel.getName() << setw(12) << left << hotel.getNights() << hotel.getRoom() << endl;
        flag = 0;
    }
    if (flag == -1) {
        cout << "Sorry, no record found.";
    }
    cout << endl << endl;
    infile.close();
}

int home(){
    int flag;
    
    cout << "\t\t\t" << "------------" << endl;                     // Home Banner.
    cout << "\t\t\t\t" << "Home" << endl;
    cout << "\t\t\t" << "------------" << endl << endl;
    
    cout << "To proceed, please choose from one on the given options:" << endl << endl;
    
    cout << "\t" << "1." << "\t" << "Book a Room" << endl;
    cout << "\t" << "2." << "\t" << "View Reservation" << endl;
    cout << "\t" << "3." << "\t" << "Edit Reservation" << endl;
    cout << "\t" << "4." << "\t" << "Manager's Portal" << endl;
    cout << "\t" << "5." << "\t" << "Exit" << endl << endl;         // Function will return -1.
    cout << "Enter your Choice: ";
    cin >> flag;
    cout << endl << endl;
    
    switch (flag) {
        case 1: newReservation(); return 0;
        case 2: viewReservation(); return 0;
        case 3: editReservation(); return 0;
        case 4: viewAllReservations(); return 0;
        case 5: return -1;
        default: home(); return 0;
    }
}

int getNumberOfReservations() {
    ifstream infile("database", ios::binary | ios::in);
    int nNumberOfEntries = -1;                                      // Initialized to -1, to fix overcounting.
    while (!infile.eof()) {
        infile.read((char*)&hotel, sizeof(hotel));
        nNumberOfEntries++;
    }
    infile.close();
    return nNumberOfEntries;
}

int main() {
    int nLoop = 0;
    while (nLoop == 0)
        nLoop = home();
    return 0;
}