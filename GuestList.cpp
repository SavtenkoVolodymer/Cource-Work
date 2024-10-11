#include "GuestList.h"

// Constructors
GuestList::GuestList(const GuestList& other) {
    guests = other.guests;
}

GuestList::GuestList(GuestList&& other) noexcept {
    guests = std::move(other.guests);
}

// Operator =
GuestList& GuestList::operator=(const GuestList& other) {
    if (this != &other) {
        guests = other.guests;
    }
    return *this;
}

GuestList& GuestList::operator=(GuestList&& other) noexcept {
    if (this != &other) {
        guests = std::move(other.guests);
    }
    return *this;
}

// Operators == , != , < , >
bool GuestList::operator==(const GuestList& other) const {
    return this->guests == other.guests;
}

bool GuestList::operator!=(const GuestList& other) const {
    return !(*this == other);
}

bool GuestList::operator<(const GuestList& other) const {
    return this->guests.size() < other.guests.size();
}

bool GuestList::operator>(const GuestList& other) const {
    return this->guests.size() > other.guests.size();
}

// Getters and Setters
const list<Guest>& GuestList::getGuests() const {
    return guests;
}

void GuestList::setGuests(const list<Guest>& newGuests) {
    guests = newGuests;
}

// Functions
void GuestList::addGuest(const Guest& guest) {
    guests.push_back(guest);
}

void GuestList::removeGuest(const Guest& guest) {
    guests.remove(guest);
}

size_t GuestList::getGuestCount() const {
    return guests.size();
}

ostream& operator<<(ostream& os, const GuestList& guestList) {
    os << "Guest List: \n";
    for (const auto &guest: guestList.guests) {
        os << guest << "\n";
    }
    return os;
}