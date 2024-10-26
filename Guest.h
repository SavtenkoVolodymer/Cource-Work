#ifndef HOTELMANEGEMENT_GUEST_H
#define HOTELMANEGEMENT_GUEST_H

#include <iostream>
#include <limits>
#include <memory>
#include "Person.h"
#include "Room.h"
#include "list"
using namespace std;

class Guest : public Person{
private:
    string name;
    int idGuest;
    int year;
    string surname;

public:
    Guest();
    Guest(string &newName, int newIdGuest, int newYear, string &newSurname);
    Guest(const Guest& guest);
    Guest(Guest&& guest) noexcept;
    friend ostream& operator<<(ostream& os, const Guest& guest);
    friend istream& operator>>(istream& is, Guest& guest);
    ~Guest() override;
    Guest& operator=(const Guest& other);
    Guest& operator=(Guest&& other) noexcept;

    static bool ifExistGuest(int idGuest);
    [[nodiscard]] string toString() const;
    void getGuest();
    void writeToFile() override;
    static Guest registerGuest();
    static unique_ptr<Room> getRoomFromFile(int idRoom);


    bool operator==(const Guest& other) const;
    bool operator!=(const Guest& other) const;
    bool operator<(const Guest& other) const;
    bool operator>(const Guest& other) const;


    [[nodiscard]] string getName() const;
    [[nodiscard]] int getIdGuest() const;
    [[nodiscard]] int getYear() const;
    [[nodiscard]] string getSurname() const;

    void setName(const string& _name);
    void setIdGuest(int _idGuest);
    void setYear(int _year);
    void setSurname(const string& _surname);


};

#endif //HOTELMANEGEMENT_GUEST_H
