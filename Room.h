#ifndef HOTELMANEGEMENT_ROOM_H
#define HOTELMANEGEMENT_ROOM_H
#include <iostream>

using namespace std;

class Room {
private:
    int idRoom;
    bool isOccupied;
    double pricePerNight;
    int currentOccupancy;

public:
    Room();
    Room(int newIdRoom, bool newIsOccupied, double newPricePerNight, int currentOccupancy);
    Room(const Room& room);
    Room(Room&& room) noexcept;
    friend ostream& operator<<(ostream& out, const Room& n);
    friend istream& operator>>(istream& in, Room& room);
    virtual ~Room();
    Room& operator=(const Room& other);
    Room& operator=(Room&& other) noexcept;

    void getRooms();
    void writeToFile() const;

    bool operator==(const Room& other) const;
    bool operator!=(const Room& other) const;
    bool operator<(const Room& other) const;
    bool operator>(const Room& other) const;

    [[nodiscard]] int getIdRoom() const;
    [[nodiscard]] bool getIsOccupied() const;
    [[nodiscard]] double getPricePerNight() const;
    [[nodiscard]] int getCurrentOccupancy() const;

    void setIdRoom(int _idRoom);
    void setIsOccupied(bool _isOccupied);
    void setPricePerNight(double _price);
    void setCurrentOccupancy(int _currentOccupancy);
};

#endif //HOTELMANEGEMENT_ROOM_H
