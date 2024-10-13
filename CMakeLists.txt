cmake_minimum_required(VERSION 3.27)
project(HotelManegement)

set(CMAKE_CXX_STANDARD 17)

add_executable(HotelManegement main.cpp
        Admin.cpp
        Admin.h
        Guest.cpp
        Guest.h
        Room.cpp
        Room.h
        Reservation.cpp
        Reservation.h
        Date.cpp
        Date.h
        GuestList.cpp
        GuestList.h
        SingleRoom.cpp
        SingleRoom.h
        DoubleRoom.cpp
        DoubleRoom.h
        TripleRoom.cpp
        TripleRoom.h
        RoomList.cpp
        RoomList.h
)
