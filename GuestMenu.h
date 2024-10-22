#ifndef HOTELMANEGEMENT_GUESTMENU_H
#define HOTELMANEGEMENT_GUESTMENU_H

#include <list>
#include "Guest.h"
#include "Reservation.h"

class GuestMenu {
private:
    static void makeReservation(Guest& guest,list<Reservation>& reservations);
    static void viewReservations(Guest& guest, const list<Reservation>& reservations);

public:
    GuestMenu() = default;
    ~GuestMenu() = default;

    static void cancelReservations(Guest& guest, list<Reservation>& reservations);
    static void menuGuest(Guest& guest, std::list<Reservation>& reservations);
//    static void addReservation(Guest &guest);
    template <typename T>
    static T getInput(const string& prompt) {
        T value;
        while (true) {
            cout << prompt << endl;
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Invalid input. Please enter a value of the correct type." << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }


};
#endif //HOTELMANEGEMENT_GUESTMENU_H
