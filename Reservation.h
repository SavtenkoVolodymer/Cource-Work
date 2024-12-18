#ifndef HOTELMANEGEMENT_RESERVATION_H
#define HOTELMANEGEMENT_RESERVATION_H

#include <iostream>
#include <memory>
#include "Date.h"
#include "Room.h"
#include "Guest.h"
using namespace std;

class Reservation {
private:
    Guest guest;
    Date check_in;
    Date check_out;
    unique_ptr<Room> room;
public:
    Reservation();
    Reservation(Guest& newGuest, Date& newCheckIn, Date& newCheckOut, unique_ptr<Room> newRoom);
    Reservation(const Reservation& reservation);
    Reservation(Reservation&& reservation) noexcept;
    friend ostream& operator<<(ostream& os, const Reservation& reservation);
    friend istream& operator>>(istream& is, Reservation& reservation);
    ~Reservation();

    static list <Reservation> reservationFromFile();
    void writeToFile();
    double getPrice();
    double getPriceFromFile() const;

    Reservation& operator=(const Reservation& reservation);
    Reservation& operator=(Reservation&& reservation) noexcept;

    bool operator==(const Reservation& other) const;
    bool operator!=(const Reservation& other) const;
    bool operator<(const Reservation& other) const;
    bool operator>(const Reservation& other) const;


    [[nodiscard]] Guest getGuest() const;
    [[nodiscard]] Date getCheckIn() const;
    [[nodiscard]] Date getCheckOut() const;
    [[nodiscard]] const Room& getRoom() const;

    void setCheckIn(const Date& newCheckIn);
    void setCheckOut(const Date& newCheckOut);
    void setRoom(Room & newRoom);
    void setGuest(const Guest &newGuest);
};

#endif //HOTELMANEGEMENT_RESERVATION_H
