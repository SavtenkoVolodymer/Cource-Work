#include "GuestMenu.h"
#include <iostream>
#include <memory>
#include "Reservation.h"
#include "Admin.h"
#include "RoomList.h"
#include <fstream>

void GuestMenu::readInstructions() {
    std::ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Instruction.txt)");

    if (!fin.is_open()) {
        cerr << "Error: Could not open the instructions file." << endl;
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << std::endl;  // Виводимо кожен рядок інструкції на екран
    }

    fin.close();
}

void GuestMenu::removeRoomFromFile(int idRoom) {

    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    list<Room> rooms;
    Room room;
    while (fin >> room) {
        if (room.getIdRoom() != idRoom) {
            rooms.push_back(room);
        }
    }
    fin.close();
    cout << "Reservation successfully created and saved to file!" << endl;
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)", ios::trunc); // Очищаємо файл перед записом
    for (const auto& r : rooms) {
        fout << r.getIdRoom() << "\t" << r.getIsOccupied() << "\t" << r.getPricePerNight() << "\t" << r.getCurrentOccupancy() << "\n";
    }
    fout.close();


}

void GuestMenu::makeReservation(Guest& guest, list<Reservation>& reservations) {
    Date checkIn, checkOut;
    int idRoom;

    cout << " Enter check in date: \n";
    checkIn.setDate();
    cout << " Enter check out date: \n";
    checkOut.setDate();

    cout << "Enter room ID: ";
    cin >> idRoom;

    try {
        if (Admin::ifExist(idRoom)) {
            unique_ptr<Room> room = Guest::getRoomFromFile(idRoom);
            reservations.emplace_back(guest, checkIn, checkOut, std::move(room));

            Reservation reservation(guest, checkIn, checkOut, Guest::getRoomFromFile(idRoom));
            reservation.writeToFile();

            removeRoomFromFile(idRoom);

        } else {
            throw runtime_error("This ID of room does not exist!!");
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}
void GuestMenu::cancelReservations(Guest& guest, list<Reservation>& reservations) {
    bool hasCanceled = false;

    for (auto it = reservations.begin(); it != reservations.end();) {
        if (it->getGuest().getIdGuest() == guest.getIdGuest()) {
            it = reservations.erase(it);
            cout << "Reservation for guest with ID " << guest.getIdGuest() << " has been canceled." << endl;
            hasCanceled = true;
        } else {
            it->writeToFile();
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

        if (reservation.getGuest().getIdGuest() == guest.getIdGuest()) {
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

void GuestMenu::updateReservationDates(Guest& guest, list<Reservation>& reservations) {
    bool reservationFound = false;

    for (auto& reservation : reservations) {
        if (reservation.getGuest().getIdGuest() == guest.getIdGuest()) {
            reservationFound = true;
            cout << "Current reservation details for guest: " << guest.getName() << endl;
            cout << "Check-in: " << reservation.getCheckIn().getDate()
                 << ", Check-out: " << reservation.getCheckOut().getDate()
                 << ", Room: " << reservation.getRoom().getIdRoom() << endl;

            Date newCheckIn, newCheckOut;
            cout << "Enter new check-in date: ";
            newCheckIn.setDate();
            cout << "Enter new check-out date: ";
            newCheckOut.setDate();

            reservation.setCheckIn(newCheckIn);
            reservation.setCheckOut(newCheckOut);

            cout << "Reservation dates updated successfully!" << endl;

            ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)");
            if (!fout.is_open()) {
                cerr << "Error: Could not open file for writing." << endl;
                return;
            }

            for (const auto& res : reservations) {
                fout << res.getGuest().toString() << "\t"
                     << res.getCheckIn().getDate() << "\t"
                     << res.getCheckOut().getDate() << "\t"
                     << res.getRoom().getIdRoom() << endl;
            }

            fout.close();
            cout << "Changes saved to file!" << endl;
            break;
        }
    }

    if (!reservationFound) {
        cout << "No reservation found for guest: " << guest.getName() << endl;
    }
}

void GuestMenu::menuGuest(Guest& guest, list<Reservation>& reservations) {
    int choice = 0;

    while (choice != 6) {
        cout << "\nGuest Menu:" << endl;
        cout << "1. Make a Reservation" << endl;
        cout << "2. View Your Reservations" << endl;
        cout << "3. Cancel Your Reservations" << endl;
        cout << "4. View Room list" << endl;
        cout << "5. Update Reservation Dates" << endl;
        cout << "6. Exit Guest Menu" << endl;
        cout << "Enter your choice (1-6): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }

        if (choice < 1 || choice > 7) {
            cout << "Invalid choice. Please select a number between 1 and 6." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                GuestMenu guestMenu;
                RoomList roomList;
                Admin::shtrix();
                roomList.printRooms();
                guestMenu.makeReservation(guest, reservations);
                Admin::shtrix();
                break;
            }
            case 2: {
                viewReservations(guest, reservations);
                Admin::shtrix();
                break;
            }
            case 3: {
                GuestMenu::cancelReservations(guest, reservations);
                break;
            }
            case 4: {
                RoomList roomList;
                roomList.printRooms();
                break;
            }
            case 5: {
                updateReservationDates(guest, reservations);
                Admin::shtrix();
                break;
            }
            case 6: {
                cout << "Exiting Guest Menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please select 1, 2, 3, 4, 5, or 6." << endl;
        }
    }
}


//void Guest::addReservation(Guest& guest) {
//    cout << "Enter check in date: " << endl;
//    unique_ptr <int> year1 = make_unique <int> (getInput<int>("Enter check in year: " ));
//
//    unique_ptr <int> month1 = make_unique <int> (getInput<int>("Enter check in month: "));
//
//    unique_ptr <int> day1 = make_unique <int> (getInput<int>("Enter check in day: "));
//
//    Date date1(*year1, *month1, *day1);
//
//    cout << "Enter check out date: " << endl;
//    unique_ptr <int> year2 = make_unique <int> (getInput<int>("Enter check out year: " ));
//
//    unique_ptr <int> month2 = make_unique <int> (getInput<int>("Enter check out month: "));
//
//    unique_ptr <int> day2 = make_unique <int> (getInput<int>("Enter check out day: "));
//
//    unique_ptr <int> room = make_unique <int> (getInput<int>("Enter number of room: "));
//    Date date2(*year2, *month2, *day2);
//    shared_ptr<Guest> guest1 {new Guest (guest)};
//    try {
//        if (Admin::ifExistGuest(*room)) {
//            Reservation reservation(guest1, date1, date2, Guest::getRoomFromFile(2));
//            reservation.writeToFile();
//        } else {
//            throw runtime_error("This id of room does not exist!!");
//        }
//    }catch (exception &e){
//        cerr << e.what() << endl;
//    }
//}


