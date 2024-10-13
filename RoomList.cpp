#include "RoomList.h"

RoomList::RoomList() : singleRooms(), doubleRooms(), tripleRooms() {}


RoomList::RoomList(const RoomList& other)
        : singleRooms(other.singleRooms), doubleRooms(other.doubleRooms), tripleRooms(other.tripleRooms) {}

RoomList::RoomList(RoomList&& other) noexcept
        : singleRooms(std::move(other.singleRooms)),
          doubleRooms(std::move(other.doubleRooms)),
          tripleRooms(std::move(other.tripleRooms)) {}


RoomList& RoomList::operator=(const RoomList& other) {
    if (this != &other) {
        singleRooms = other.singleRooms;
        doubleRooms = other.doubleRooms;
        tripleRooms = other.tripleRooms;
    }
    return *this;
}

RoomList& RoomList::operator=(RoomList&& other) noexcept {
    if (this != &other) {
        singleRooms = std::move(other.singleRooms);
        doubleRooms = std::move(other.doubleRooms);
        tripleRooms = std::move(other.tripleRooms);
    }
    return *this;
}

RoomList::~RoomList() {}
