#ifndef HOTELMANEGEMENT_GUEST_H
#define HOTELMANEGEMENT_GUEST_H

#include <iostream>
#include "Reservation.h"
#include "Person.h"
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

    void addReservation() const override;
    void viewReservations(const list<Reservation>& reservations) const;
    void writeToFile() override;
    static bool ifExist(int idRoom);
    static unique_ptr<Room> getRoomFromFile(int idRoom);

    template <typename T>
    static T getInput(const string& prompt) {
        T value;
        while (true) {
            cout << prompt << endl;
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Invalid input. Please enter a value of the correct type." << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

    bool operator==(const Guest& other) const;
    bool operator!=(const Guest& other) const;
    bool operator<(const Guest& other) const;
    bool operator>(const Guest& other) const;

    [[nodiscard]] bool sortByName(const string& newName) const;
    [[nodiscard]] bool sortByHighYear(int newYear) const;
    [[nodiscard]] bool sortByLowYear(int newYear) const;
    bool sortBySurname(const string& newSurname) const;

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
