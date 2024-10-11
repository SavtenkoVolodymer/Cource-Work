#include "Room.h"
#include <fstream>
#include <iostream>

//Constructors
Room::Room() : idRoom(0), isOccupied(false), pricePerNight(0.0), currentOccupancy(0) {}

Room::Room(int newIdRoom, bool newIsOccupied, double newPricePerNight, int currentOccupancy)
        : idRoom(newIdRoom), isOccupied(newIsOccupied), pricePerNight(newPricePerNight), currentOccupancy(currentOccupancy) {}

Room::Room(const Room& room)
        : idRoom(room.idRoom), isOccupied(room.isOccupied), pricePerNight(room.pricePerNight), currentOccupancy(room.currentOccupancy) {}

Room::Room(Room&& room) noexcept
        : idRoom(room.idRoom), isOccupied(room.isOccupied), pricePerNight(room.pricePerNight), currentOccupancy(room.currentOccupancy) {
    room.idRoom = 0;
    room.isOccupied = false;
    room.pricePerNight = 0.0;
    room.currentOccupancy = 0;
}

Room::~Room() {}

istream& operator>>(istream& is, Room& room) {
    is >> room.idRoom >> room.isOccupied >> room.pricePerNight >> room.currentOccupancy;
    return is;
}
ostream& operator<<(ostream& out, const Room& n) {
    out << "Room ID: " << n.idRoom << ", Occupied: " << (n.isOccupied ? "Yes" : "No")
        << ", Price per Night: " << n.pricePerNight << ", Current Occupancy: " << n.currentOccupancy;
    return out;
}

// Getters and Setters
int Room::getIdRoom() const {
    return idRoom;
}

bool Room::getIsOccupied() const {
    return isOccupied;
}

double Room::getPricePerNight() const {
    return pricePerNight;
}

void Room::setIdRoom(int _idRoom) {
    idRoom = _idRoom;
}

void Room::setIsOccupied(bool _isOccupied) {
    isOccupied = _isOccupied;
}

void Room::setPricePerNight(double _price) {
    pricePerNight = _price;
}
// Operator =
Room& Room::operator=(const Room& other) {
    if (this != &other) {
        idRoom = other.idRoom;
        isOccupied = other.isOccupied;
        pricePerNight = other.pricePerNight;
        currentOccupancy = other.currentOccupancy;
    }
    return *this;
}

Room& Room::operator=(Room&& other) noexcept {
    if (this != &other) {
        idRoom = other.idRoom;
        isOccupied = other.isOccupied;
        pricePerNight = other.pricePerNight;
        currentOccupancy = other.currentOccupancy;

        other.idRoom = 0;
        other.isOccupied = false;
        other.pricePerNight = 0.0;
        other.currentOccupancy = 0;
    }
    return *this;
}
// Operators == , != , >, <
bool Room::operator==(const Room& other) const {
    return idRoom == other.idRoom &&
           isOccupied == other.isOccupied &&
           pricePerNight == other.pricePerNight &&
           currentOccupancy == other.currentOccupancy;
}

bool Room::operator!=(const Room& other) const {
    return !(*this == other);
}

bool Room::operator<(const Room& other) const {
    if (idRoom != other.idRoom) {
        return idRoom < other.idRoom;
    }
    if (pricePerNight != other.pricePerNight) {
        return pricePerNight < other.pricePerNight;
    }
    return currentOccupancy < other.currentOccupancy;
}

bool Room::operator>(const Room& other) const {
    return other < *this;
}

