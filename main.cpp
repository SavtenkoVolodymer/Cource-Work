#include  <iostream>
#include <fstream>
#include "Admin.h"
#include "Date.h"
#include "Reservation.h"
#include "Guest.h"
#include "GuestMenu.h"
#include "GuestList.h"
#include "RoomList.h"

int main() {
//    Admin admin ("Katya","777");
//    Admin::addRoom();
//    Admin::ifExist(2);


//    Guest guest(name,2,2000,surname);
//    string name = "Vova";
//    string surname = "Savtenko";
//    Guest guest1(name,2,2000,surname);
//    guest1.sortBySurname("Savtenko");
//    string name2 = "Vova";
//    string surname2 = "Savtenko";
//    Guest guest2(name,2,2000,surname);
//    string name3 = "Vova";
//    string surname3 = "Savtenko";
//    Guest guest3(name,2,2000,surname);
//    string name4 = "Vova";
//    string surname4 = "Savtenko";
//    Guest guest4(name,2,2000,surname);
//
////    cout << Guest::ifExist(15);
//
//    guest.writeToFile();
//    guest1.writeToFile();
//    guest2.writeToFile();
//    guest3.writeToFile();
//    guest4.writeToFile();
//GuestList guestList ;
//    guestList.printGuests();
//    string name = "Vova";
//    string surname = "Savtenko";
//    shared_ptr <Guest> guest {new Guest(name , 1, 200,surname)};
//    Date date (2021, 01,12);
//    unique_ptr<Room> room = make_unique<Room>(1, false, 1000, 1);
//    Reservation reservation (guest,  date , date ,std::move(room));
//    reservation.getPriceFromFile();
//    guest->writeToFile();
//    room->writeToFile();

//        RoomList roomList;
//        RoomList::roomsFromFile("Rooms.txt");
//
//        reservation.writeToFile();
//    GuestList guestList;
//    guestList.printGuests();


//
//
//    cout<< reservation1.getGuest()<<endl;
//    cout << reservation1.getCheckIn().getDate()<< endl;
//    cout << reservation1.getCheckOut().getDate()<< endl;
//    cout << reservation1.getRoom();

//    Reservation reservation (name,date , date , 1);
//    cout<< reservation << endl;
//    cout << reservation.getPriceFromFile();
//    cout << *guest->getRoomFromFile(1);

//    Guest guest(name, 1, 1990, surname);
//    Guest::getRoomFromFile(1);
//    Room room(104, false, 300, 2);
//    RoomList roomList;
//    roomList.addRoom(room);
//      roomList.roomsFromFile("Rooms.txt");

//
//




    int choice = 0;

    while (choice != 3) {
        cout << "\nWelcome to the Hotel Management System" << endl;
        cout << "1. Register as Admin" << endl;
        cout << "2. Register as Guest" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                try {
                    Admin admin;
                    Admin::registerAdmin();
                    list<Reservation> reservations = Reservation::reservationFromFile();
                    Admin::adminMenu(admin, reservations);
                } catch (const invalid_argument& e) {
                    cout << "Registration failed: " << e.what() << endl;
                }
                break;
            case 2: {
                Guest guest = Guest::registerGuest();
                list<Reservation> reservations = Reservation::reservationFromFile();
                GuestMenu::menuGuest(guest, reservations);
                break;
            }
            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select 1, 2 or 3." << endl;
        }
    }

    return 0;
}



