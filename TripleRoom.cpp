#include "TripleRoom.h"
#include "fstream"

//Constructors
TripleRoom::TripleRoom() : Room(), maxOccupancy(3) {}

TripleRoom::TripleRoom(int newIdRoom, bool newIsOccupied, double newPricePerNight, const list<Guest>& newGuests)
        : Room(newIdRoom, newIsOccupied, newPricePerNight , 3), guests(newGuests) {}

TripleRoom::TripleRoom(const TripleRoom& other)
        : Room(other), maxOccupancy(other.maxOccupancy), guests(other.guests) {}

TripleRoom::TripleRoom(TripleRoom&& other) noexcept
        : Room(std::move(other)), maxOccupancy(other.maxOccupancy), guests(std::move(other.guests)) {}

TripleRoom::~TripleRoom() {}

istream &operator>>(istream& is, TripleRoom& obj){
    is>>static_cast<Room&>(obj);
    return is;
}

ostream& operator<<(ostream& os, const TripleRoom& room) {
    os<<static_cast <const Room&>(room);
    for(const Guest& guest: room.getGuests()){
        os<<guest;
    }
    return os;
}

// Operator =
TripleRoom& TripleRoom::operator=(const TripleRoom& other) {
    if (this != &other) {
        Room::operator=(other);
        maxOccupancy = other.maxOccupancy;
        guests = other.guests;
    }
    return *this;
}

TripleRoom& TripleRoom::operator=(TripleRoom&& other) noexcept {
    if (this != &other) {
        Room::operator=(std::move(other));
        maxOccupancy = other.maxOccupancy;
        guests = std::move(other.guests);
    }
    return *this;
}
// Operators == , != , >,<
bool TripleRoom::operator==(const TripleRoom& other) const {
    return Room::operator==(other) &&
           maxOccupancy == other.maxOccupancy &&
           guests == other.guests;
}

bool TripleRoom::operator!=(const TripleRoom& other) const {
    return !(*this == other);
}

bool TripleRoom::operator<(const TripleRoom& other) const {
    return maxOccupancy < other.maxOccupancy;
}

bool TripleRoom::operator>(const TripleRoom& other) const {
    return maxOccupancy > other.maxOccupancy;
}
// Getters and Setters
int TripleRoom::getMaxOccupancy() const {
    return maxOccupancy;
}

const list<Guest>& TripleRoom::getGuests() const {
    return guests;
}

void TripleRoom::setMaxOccupancy(int newMaxOccupancy) {
    maxOccupancy = newMaxOccupancy;
}

void TripleRoom::setGuests(const list<Guest>& newGuests) {
    guests = newGuests;
}
// Functions
void TripleRoom::addGuest(const Guest& guest) {
    if (guests.size() < maxOccupancy) {
        guests.push_back(guest);
    } else {
        cout << "Cannot add guest: Maximum occupancy reached." << endl;
    }
}

void TripleRoom::printGuests() {
    for(const Guest& guest: guests){
        cout<<guest<<endl;
    }
}

void TripleRoom::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\TripleRooms.txt)", ios_base::app);
    fout << getIdRoom() << "\t" << getIsOccupied() << "\t" << getPricePerNight() << "\t" << getMaxOccupancy()<< endl;
    fout.close();
}


