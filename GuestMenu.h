#ifndef HOTELMANEGEMENT_GUESTMENU_H
#define HOTELMANEGEMENT_GUESTMENU_H

#include <list>
#include "Guest.h"
#include "Reservation.h"

class GuestMenu {
private:
    void makeReservation(Guest& guest,list<Reservation>& reservations);
    static void viewReservations(Guest& guest, const list<Reservation>& reservations);

public:
    GuestMenu() = default;
    ~GuestMenu() = default;

    static void cancelReservations(int idGuest);
    static void menuGuest(Guest& guest, list<Reservation>& reservations);
    static void updateReservationDates(Guest& guest, list<Reservation>& reservations);
    void removeRoomFromFile(int idRoom);
    static void readInstructions();
};
#endif //HOTELMANEGEMENT_GUESTMENU_H
