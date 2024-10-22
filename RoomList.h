#ifndef HOTELMANEGEMENT_ROOMLIST_H
#define HOTELMANEGEMENT_ROOMLIST_H

#include <list>
#include <iostream>
#include "Room.h"
using namespace std;

class RoomList {
private:
    list<Room> rooms;

public:
    RoomList();
    RoomList(const RoomList& other);
    RoomList(RoomList&& other) noexcept;
    RoomList& operator=(const RoomList& other);
    RoomList& operator=(RoomList&& other) noexcept;
    ~RoomList();

    void printRooms();
    void roomsFromFile();
    void addRoom(Room &room){
        rooms.push_back(room);
    }

};

#endif //HOTELMANEGEMENT_ROOMLIST_H
