#include "RoomList.h"
#include <utility>
#include <fstream>

RoomList::RoomList() : rooms() {}

RoomList::RoomList(const RoomList& other) : rooms(other.rooms) {}

RoomList::RoomList(RoomList&& other) noexcept : rooms(std::move(other.rooms)) {
    other.rooms.clear();
}

RoomList& RoomList::operator=(const RoomList& other) {
    if (this != &other) {
        rooms = other.rooms;
    }
    return *this;
}

RoomList& RoomList::operator=(RoomList&& other) noexcept {
    if (this != &other) {
        rooms = std::move(other.rooms);
        other.rooms.clear();
    }
    return *this;
}

RoomList::~RoomList() {
    rooms.clear();
}

void RoomList::roomsFromFile() {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    if (!fin.is_open()) {
        cerr << "Error: Could not open the file " << endl;
        return;
    }

    int idRoom;
    bool isOccupied;
    double pricePerNight;
    int currentOccupancy;

    while (fin >> idRoom >> isOccupied >> pricePerNight >> currentOccupancy) {
        Room room(idRoom, isOccupied, pricePerNight, currentOccupancy);
        rooms.push_back(room);
    }

    fin.close();
}

void RoomList::printRooms() {
    this->roomsFromFile();
    for(Room &room : rooms){
        room.getRooms();
        cout << "--------------------------------------------"<<endl;
    }
}

