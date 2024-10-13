#include "SingleRoom.h"
#include "fstream"

// Constructors
SingleRoom::SingleRoom() : Room(), guest() {}

SingleRoom::SingleRoom(int newIdRoom, bool newIsOccupied, double newPricePerNight, Guest  &newGuest)
        : Room(newIdRoom, newIsOccupied, newPricePerNight, 1), guest(newGuest) {}

SingleRoom::SingleRoom(int newIdRoom, bool newIsOccupied, double newPricePerNight , int newCurrentOccupancy)
        : Room(newIdRoom, newIsOccupied, newPricePerNight, newCurrentOccupancy) {}

SingleRoom::SingleRoom(const SingleRoom& other)
        : Room(other), maxOccupancy(other.maxOccupancy), guest(other.guest) {}

SingleRoom::SingleRoom(SingleRoom&& other) noexcept
        : Room(std::move(other)), maxOccupancy(other.maxOccupancy), guest(std::move(other.guest)) {
    other.maxOccupancy = 0;
}

SingleRoom::~SingleRoom() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << " Destructor from Single Room "<<endl;
}

istream &operator>>(istream& is, SingleRoom& obj){
    is>>static_cast<Room&>(obj);
    return is;
}

ostream& operator<<(ostream& os, const SingleRoom& room) {
    os << room.getIdRoom()
       << (room.getIsOccupied() ? "Yes" : "No")
       << room.getPricePerNight()
       << room.getMaxOccupancy()
       << room.getGuest().getName() << " " << room.getGuest().getSurname();

    return os;
}

// Operator =
SingleRoom& SingleRoom::operator=(const SingleRoom& other) {
    if (this != &other) {
        Room::operator=(other);
        maxOccupancy = other.maxOccupancy;
        guest = other.guest;
    }
    return *this;
}

SingleRoom& SingleRoom::operator=(SingleRoom&& other) noexcept {
    if (this != &other) {
        Room::operator=(std::move(other));
        maxOccupancy = other.maxOccupancy;
        guest = std::move(other.guest);
        other.maxOccupancy = 0;
    }
    return *this;
}

// Operator == , != , > , <
bool SingleRoom::operator==(const SingleRoom& other) const {
    return Room::operator==(other) &&
           maxOccupancy == other.maxOccupancy &&
           guest == other.guest;
}

bool SingleRoom::operator!=(const SingleRoom& other) const {
    return !(*this == other);
}

bool SingleRoom::operator<(const SingleRoom& other) const {
    return maxOccupancy < other.maxOccupancy;
}

bool SingleRoom::operator>(const SingleRoom& other) const {
    return maxOccupancy > other.maxOccupancy;
}
// Getters and Setters
int SingleRoom::getMaxOccupancy() const {
    return maxOccupancy;
}

const Guest& SingleRoom::getGuest() const {
    return guest;
}

void SingleRoom::setGuest(const Guest& newGuest) {
    guest = newGuest;
}

void SingleRoom::printGuests() {
    cout<<guest<<endl;
}

void SingleRoom::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\SingleRooms.txt)", ios_base::app);
    fout << getIdRoom() << "\t" << getIsOccupied() << "\t" << getPricePerNight() << "\t" << getMaxOccupancy()<<"\t"<<guest<< endl;
    fout.close();
}
void SingleRoom::addToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedSingleR.txt)", ios_base::app);
    fout << getIdRoom() << "\t" << getIsOccupied() << "\t" << getPricePerNight() << "\t" << getCurrentOccupancy()<<endl;
    fout.close();
    cout<< "Single room was added to file"<<endl;
}

