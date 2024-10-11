#ifndef HOTELMANEGEMENT_DOUBLEROOM_H
#define HOTELMANEGEMENT_DOUBLEROOM_H

#include <iostream>
#include <list>
#include "Room.h"
#include "Guest.h"

using namespace std;

class DoubleRoom : public Room {
private:
    int maxOccupancy = 2;
    list<Guest> guests;

public:
    DoubleRoom();
    DoubleRoom(int maxOccupancy, list<Guest> guests, int newIdRoom, bool newIsOccupied, double newPricePerNight, int currentOccupancy);
    DoubleRoom(const DoubleRoom& other);
    DoubleRoom(DoubleRoom&& other) noexcept;
    friend ostream& operator<<(ostream& os, const DoubleRoom& room);
    friend istream& operator>>(istream& is, DoubleRoom& room);
    ~DoubleRoom() override;

    void printGuests() override;
    void writeToFile () override;

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

    void addGuest(const Guest& guest);
};

#endif //HOTELMANEGEMENT_DOUBLEROOM_H
