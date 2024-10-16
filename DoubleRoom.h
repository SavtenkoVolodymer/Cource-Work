#ifndef HOTELMANEGEMENT_DOUBLEROOM_H
#define HOTELMANEGEMENT_DOUBLEROOM_H

#include <iostream>
#include <list>
#include "Room.h"
#include "Guest.h"
using namespace std;

class DoubleRoom : public Room{
private:
    int maxOccupancy = 2;
    list<Guest> guests;

public:
    DoubleRoom();
    DoubleRoom(list<Guest> guests, int newIdRoom, bool newIsOccupied, double newPricePerNight, int currentOccupancy);
    DoubleRoom(int newIdRoom, bool newIsOccupied,double newPricePerNight, int newCurrentOccupancy);
    DoubleRoom(const DoubleRoom& other);
    DoubleRoom(DoubleRoom&& other) noexcept;
    friend ostream& operator<<(ostream& os, const DoubleRoom& room);
    friend istream& operator>>(istream& is, DoubleRoom& room);
    ~DoubleRoom();

    void printGuests();
    void writeToFile ();
    void addToFile ();
    void addGuest(const Guest& guest);


    DoubleRoom& operator=(const DoubleRoom& other);
    DoubleRoom& operator=(DoubleRoom&& other) noexcept;

    bool operator==(const DoubleRoom& other) const;
    bool operator!=(const DoubleRoom& other) const;
    bool operator<(const DoubleRoom& other) const;
    bool operator>(const DoubleRoom& other) const;

    [[nodiscard]] int getMaxOccupancy() const;
    [[nodiscard]] const list<Guest>& getGuests() const;

    void setMaxOccupancy(int newMaxOccupancy);
    void setGuests(const list<Guest>& newGuests);


};

#endif //HOTELMANEGEMENT_DOUBLEROOM_H
