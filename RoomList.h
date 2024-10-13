#ifndef HOTELMANEGEMENT_ROOMLIST_H
#define HOTELMANEGEMENT_ROOMLIST_H

#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "TripleRoom.h"
#include <list>
#include <iostream>
using namespace std;

class RoomList {
private:
    list<SingleRoom> singleRooms;
    list<DoubleRoom> doubleRooms;
    list<TripleRoom> tripleRooms;

public:
    RoomList();
    RoomList(const RoomList& other);
    RoomList(RoomList&& other) noexcept;
    RoomList& operator=(const RoomList& other);
    RoomList& operator=(RoomList&& other) noexcept;
    ~RoomList();

    void addSingleRoom(SingleRoom &singleRoom){
        singleRooms.push_back(singleRoom);
    }
    void addDoubleRoom(DoubleRoom &doubleRoom){
        doubleRooms.push_back(doubleRoom);
    }
    void addTripleRoom(TripleRoom &tripleRoom){
        tripleRooms.push_back(tripleRoom);
    }

};

#endif //HOTELMANEGEMENT_ROOMLIST_H
