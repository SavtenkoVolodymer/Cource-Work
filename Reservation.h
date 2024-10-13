#ifndef HOTELMANEGEMENT_RESERVATION_H
#define HOTELMANEGEMENT_RESERVATION_H

#include <iostream>
#include <memory>
#include "Date.h"
using namespace std;

class Reservation {
private:
    string guest;
    Date check_in;
    Date check_out;
    unique_ptr<int> room;

public:
    Reservation();
    Reservation(string newGuest, Date  &newCheckIn, Date  &newCheckOut, int newRoom);
    Reservation(const Reservation& reservation);
    Reservation(Reservation&& reservation) noexcept;
    friend ostream& operator<<(ostream& os, const Reservation& reservation);
    friend istream& operator>>(istream& is, Reservation& reservation);
    ~Reservation();

    void writeToFile();
    double getPrice();
    [[nodiscard]] double getPriceFromFile() const;

    Reservation& operator=(const Reservation& reservation);
    Reservation& operator=(Reservation&& reservation) noexcept;

    bool operator==(const Reservation& other) const;
    bool operator!=(const Reservation& other) const;
    bool operator<(const Reservation& other) const;
    bool operator>(const Reservation& other) const;


    [[nodiscard]] string getGuest() const;
    [[nodiscard]] const Date getCheckIn() const;
    [[nodiscard]] const Date getCheckOut() const;
    [[nodiscard]] int getRoom() const;

    void setGuest(const string& newGuest);
    void setCheckIn(const Date& newCheckIn);
    void setCheckOut(const Date& newCheckOut);
    void setRoom(int newRoom);
};

#endif //HOTELMANEGEMENT_RESERVATION_H
