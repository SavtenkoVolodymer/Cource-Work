#include "GuestMenu.h"
#include <iostream>
#include <memory>
#include "Reservation.h"
#include "Admin.h"
#include "RoomList.h"
#include <fstream>


void GuestMenu::makeReservation(Guest& guest, list<Reservation>& reservations) {
    Date checkIn, checkOut;
    int roomId;

    cout << " Enter check in date: \n";
    checkIn.setDate();
    cout << " Enter check in date: \n";
    checkOut.setDate();

    cout << "Enter room ID: ";
    cin >> roomId;

    unique_ptr<Room> room = std::make_unique<Room>(roomId, true, 200.0, 1);

    reservations.emplace_back(make_shared<Guest>(guest), checkIn, checkOut, std::move(room));

//    try {
//        if (Admin::ifExist(roomId)) {
//            Reservation reservation(guest,checkIn, checkOut,room );
//            reservation.writeToFile();
//        } else {
//            throw runtime_error("This id of room does not exist!!");
//        }
//    }catch (exception &e){
//        cerr << e.what() << endl;
//    }

    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::app);
    if (fout.is_open()) {
        fout << guest.toString() << "\t"
             << checkIn.getDate() << "\t"
             << checkOut.getDate() << "\t"
             << roomId << "\n";
        fout.close();
        cout << "Reservation successfully created and saved to file!" << endl;
    } else {
        cerr << "Error opening file for writing reservations!" << endl;
    }
}

void GuestMenu::cancelReservations(Guest& guest, list<Reservation>& reservations) {
    bool hasCanceled = false;

    for (auto it = reservations.begin(); it != reservations.end();) {
        if (it->getGuest()->getIdGuest() == guest.getIdGuest()) {
            it = reservations.erase(it);
            cout << "Reservation for guest with ID " << guest.getIdGuest() << " has been canceled." << endl;
            hasCanceled = true;
        } else {
            ++it;
        }
    }

    if (!hasCanceled) {
        cout << "No reservations found for guest with ID " << guest.getIdGuest() << "." << endl;
    }
}



void GuestMenu::viewReservations(Guest& guest, const list<Reservation>& reservations) {
    bool hasReservations = false;

    for (const auto& reservation : reservations) {

        if (reservation.getGuest()->getIdGuest() == guest.getIdGuest()) {
                     cout << "Reservation found for guest: " << guest.getName() << endl;
                     cout << "Check-in: " << reservation.getCheckIn().getDate()
                      << ", Check-out: " << reservation.getCheckOut().getDate()
                      << ", Room: " << reservation.getRoom().getIdRoom() << endl;
            hasReservations = true;
        }
    }

    if (!hasReservations) {
        cout << "No reservations found for guest: " << guest.getName() <<endl;
    }
}

void GuestMenu::menuGuest(Guest& guest, list<Reservation>& reservations) {
    int choice = 0;
    while (choice != 4) {
             cout << "\nGuest Menu:" << endl;
             cout << "1. Make a Reservation" << endl;
             cout << "2. View Your Reservations" << endl;
             cout << "3. View Room list" << endl;
             cout << "4. Exit Guest Menu" << endl;
             cout << "Enter your choice: ";
             cin >> choice;

        switch (choice) {
            case 1:
                GuestMenu::makeReservation(guest,reservations);
//                GuestMenu::cancelReservations(guest,reservations);
                break;
            case 2:
                viewReservations(guest, reservations);
                break;
            case 3: {
                RoomList roomList;
                roomList.printRooms();
                break;
            }
            case 4: {
                cout << "Exiting Guest Menu..." << endl;
                break;
            }
            default:
                std::cout << "Invalid choice. Please select 1, 2, or 3." << std::endl;
        }
    }
}

void Guest::addReservation(Guest& guest) {
    cout << "Enter check in date: " << endl;
    unique_ptr <int> year1 = make_unique <int> (getInput<int>("Enter check in year: " ));

    unique_ptr <int> month1 = make_unique <int> (getInput<int>("Enter check in month: "));

    unique_ptr <int> day1 = make_unique <int> (getInput<int>("Enter check in day: "));

    Date date1(*year1, *month1, *day1);

    cout << "Enter check out date: " << endl;
    unique_ptr <int> year2 = make_unique <int> (getInput<int>("Enter check out year: " ));

    unique_ptr <int> month2 = make_unique <int> (getInput<int>("Enter check out month: "));

    unique_ptr <int> day2 = make_unique <int> (getInput<int>("Enter check out day: "));

    unique_ptr <int> room = make_unique <int> (getInput<int>("Enter number of room: "));
    Date date2(*year2, *month2, *day2);
    shared_ptr<Guest> guest1 {new Guest (guest)};
    try {
        if (Admin::ifExist(*room)) {
            Reservation reservation(guest1, date1, date2, Guest::getRoomFromFile(2));
            reservation.writeToFile();
        } else {
            throw runtime_error("This id of room does not exist!!");
        }
    }catch (exception &e){
        cerr << e.what() << endl;
    }
}
