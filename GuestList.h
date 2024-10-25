#ifndef HOTELMANEGEMENT_GUESTLIST_H
#define HOTELMANEGEMENT_GUESTLIST_H

#include <iostream>
#include <list>
#include "Guest.h"
using namespace std;

class GuestList {
private:
    list<Guest> guests;

public:
    GuestList() = default;
    GuestList(const GuestList& other);
    GuestList(GuestList&& other) noexcept;
    friend ostream& operator<<(ostream& os, const GuestList& guestList);
    ~GuestList() = default;

    GuestList& operator=(const GuestList& other);
    GuestList& operator=(GuestList&& other) noexcept;

    bool operator==(const GuestList& other) const;
    bool operator!=(const GuestList& other) const;
    bool operator<(const GuestList& other) const;
    bool operator>(const GuestList& other) const;

    void printGuests();
    void addGuest(const Guest& guest);
    void guestsFromFile();

    void sortGuestsByName(const string& name);

    [[nodiscard]] const list<Guest>& getGuests() const;
    void setGuests(const list<Guest>& newGuests);
};

#endif //HOTELMANEGEMENT_GUESTLIST_H
