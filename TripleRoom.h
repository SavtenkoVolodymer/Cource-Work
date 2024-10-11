#ifndef HOTELMANEGEMENT_TRIPLEROOM_H
#define HOTELMANEGEMENT_TRIPLEROOM_H

#include <iostream>
#include <list>
#include "Room.h"
#include "Guest.h"

using namespace std;

class TripleRoom : public Room {
private:
    int maxOccupancy = 3;
    list<Guest> guests;

public:
    TripleRoom();
    TripleRoom(int newIdRoom, bool newIsOccupied, double newPricePerNight, const list<Guest>& newGuests);
    TripleRoom(const TripleRoom& other);
    TripleRoom(TripleRoom&& other) noexcept;
    friend ostream& operator<<(ostream& os, const TripleRoom& room);
    friend istream& operator>>(istream& is, TripleRoom& room);
    ~TripleRoom() override;

    void printGuests() override;
    void writeToFile () override;

    TripleRoom& operator=(const TripleRoom& other);
    TripleRoom& operator=(TripleRoom&& other) noexcept;

    bool operator==(const TripleRoom& other) const;
    bool operator!=(const TripleRoom& other) const;
    bool operator<(const TripleRoom& other) const;
    bool operator>(const TripleRoom& other) const;

    [[nodiscard]] int getMaxOccupancy() const;
    [[nodiscard]] const list<Guest>& getGuests() const;

    void setMaxOccupancy(int newMaxOccupancy);
    void setGuests(const list<Guest>& newGuests);

    void addGuest(const Guest& guest);
};

#endif //HOTELMANEGEMENT_TRIPLEROOM_H
