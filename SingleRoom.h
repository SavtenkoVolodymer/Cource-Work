#ifndef HOTELMANEGEMENT_SINGLEROOM_H
#define HOTELMANEGEMENT_SINGLEROOM_H

#include <iostream>
#include "Room.h"
#include "Guest.h"

using namespace std;

class SingleRoom : public Room {
private:
    int maxOccupancy = 1;
    Guest guest;

public:
    SingleRoom();
    SingleRoom(int newIdRoom, bool newIsOccupied, double newPricePerNight, Guest  guest);
    SingleRoom(const SingleRoom& other);
    SingleRoom(SingleRoom&& other) noexcept;
    friend ostream& operator<<(ostream& os, const SingleRoom& room);
    friend istream& operator>>(istream& is, SingleRoom& room);
    ~SingleRoom() override;

    void printGuests() override;
    void writeToFile () override;

    SingleRoom& operator=(const SingleRoom& other);
    SingleRoom& operator=(SingleRoom&& other) noexcept;

    bool operator==(const SingleRoom& other) const;
    bool operator!=(const SingleRoom& other) const;
    bool operator<(const SingleRoom& other) const;
    bool operator>(const SingleRoom& other) const;

    [[nodiscard]] int getMaxOccupancy() const;
    [[nodiscard]] const Guest& getGuest() const;
    void setGuest(const Guest& newGuest);
};

#endif //HOTELMANEGEMENT_SINGLEROOM_H
