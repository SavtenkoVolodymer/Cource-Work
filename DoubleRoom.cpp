#include "DoubleRoom.h"
#include "fstream"
// Constructors
DoubleRoom::DoubleRoom() : Room(), maxOccupancy(2), guests() {}

DoubleRoom::DoubleRoom(int maxOccupancy, list<Guest> guests, int newIdRoom, bool newIsOccupied, double newPricePerNight, int currentOccupancy)
        : Room(newIdRoom, newIsOccupied, newPricePerNight, currentOccupancy), maxOccupancy(maxOccupancy), guests(std::move(guests)) {}

DoubleRoom::DoubleRoom(const DoubleRoom& other)
        : Room(other), maxOccupancy(other.maxOccupancy), guests(other.guests) {}

DoubleRoom::DoubleRoom(DoubleRoom&& other) noexcept
        : Room(std::move(other)), maxOccupancy(other.maxOccupancy), guests(std::move(other.guests)) {
    other.maxOccupancy = 0;
}

DoubleRoom::~DoubleRoom() {}

istream &operator>>(istream& is, DoubleRoom& obj){
    is>>static_cast<Room&>(obj);
    return is;
}

ostream& operator<<(ostream& os, const DoubleRoom& room) {
    os<<static_cast<const Room&>(room);
    for(const Guest& guest : room.guests){
        os<<" "<<guest;
    }

    return os;
}

// Operator =
DoubleRoom& DoubleRoom::operator=(const DoubleRoom& other) {
    if (this != &other) {
        Room::operator=(other);
        maxOccupancy = other.maxOccupancy;
        guests = other.guests;
    }
    return *this;
}

DoubleRoom& DoubleRoom::operator=(DoubleRoom&& other) noexcept {
    if (this != &other) {
        Room::operator=(std::move(other));
        maxOccupancy = other.maxOccupancy;
        guests = std::move(other.guests);
        other.maxOccupancy = 0;
    }
    return *this;
}

// Operators == , != , > , <
bool DoubleRoom::operator==(const DoubleRoom& other) const {
    return maxOccupancy == other.maxOccupancy && Room::operator==(other) && guests == other.guests;
}

bool DoubleRoom::operator!=(const DoubleRoom& other) const {
    return !(*this == other);
}

bool DoubleRoom::operator<(const DoubleRoom& other) const {
    if (maxOccupancy != other.maxOccupancy) {
        return maxOccupancy < other.maxOccupancy;
    }
    if (guests.size() != other.guests.size()) {
        return guests.size() < other.guests.size();
    }
    return Room::operator<(other);
}

bool DoubleRoom::operator>(const DoubleRoom& other) const {
    return other < *this;
}
// Getters and Setters
int DoubleRoom::getMaxOccupancy() const {
    return maxOccupancy;
}

const list<Guest>& DoubleRoom::getGuests() const {
    return guests;
}

void DoubleRoom::setMaxOccupancy(int newMaxOccupancy) {
    maxOccupancy = newMaxOccupancy;
}

void DoubleRoom::setGuests(const list<Guest>& newGuests) {
    guests = newGuests;
}
// Functions
void DoubleRoom::addGuest(const Guest& guest) {
    if (guests.size() < maxOccupancy) {
        guests.push_back(guest);
    } else {
        cout << "Room is full!" << endl;
    }
}


void DoubleRoom::printGuests() {
    for(const Guest& guest: guests){
        cout<<guest<<endl;
    }
}

void DoubleRoom::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\DoubleRooms.txt)", ios_base::app);
    fout << getIdRoom() << "\t" << getIsOccupied() << "\t" << getPricePerNight() << "\t" << getMaxOccupancy()<< endl;
    fout.close();
}






