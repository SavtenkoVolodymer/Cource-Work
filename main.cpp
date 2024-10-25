#include  <iostream>
#include <fstream>
#include "Admin.h"
#include "Reservation.h"
#include "Guest.h"
#include "GuestMenu.h"
#include "RoomList.h"

int main() {

    int choice = 0;
    while (choice != 4) {
        cout << "\nWelcome to the Hotel Management System!!!" << endl;
        cout << "1. Register as Admin" << endl;
        cout << "2. Register as Guest" << endl;
        cout << "3. Read Instructions" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        try {
            cin >> choice;
            if (cin.fail()) {
                throw invalid_argument("Invalid input! Please enter a number (1, 2, 3 or 4.");
            }

            switch (choice) {
                case 1: {
                    try {
                        Admin admin;
                        Admin::registerAdmin();
                        list<Reservation> reservations = Reservation::reservationFromFile();
                        Admin::adminMenu(admin, reservations);
                    } catch (const invalid_argument &e) {
                        cout << "Registration failed: " << e.what() << endl;
                    }
                    break;
                }
                case 2: {
                    Guest guest = Guest::registerGuest();
                    list<Reservation> reservations = Reservation::reservationFromFile();
                    GuestMenu::menuGuest(guest, reservations);
                    break;
                }
                case 3:{
                    GuestMenu::readInstructions();
                    break;
                }
                case 4:
                    cout << "Exiting the system. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please select 1, 2, 3 or 4." << endl;
            }
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
    }

    return 0;
}



