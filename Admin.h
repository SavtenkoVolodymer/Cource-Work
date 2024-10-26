#ifndef HOTELMANEGEMENT_ADMIN_H
#define HOTELMANEGEMENT_ADMIN_H

#include <iostream>
#include <string>
#include <vector>

#include "Person.h"
#include "Reservation.h"
using namespace std;

class Admin : public Person {
private:
    string login;
    string password;

public:
    Admin();
    [[maybe_unused]] Admin(string  newLogin, string  newPassword);
    Admin(const Admin& admin);
    Admin(Admin&& admin) noexcept;
    friend ostream& operator<<(ostream& os, const Admin& admin);
    friend istream& operator>>(istream& is, Admin& admin);
    ~Admin() override;

    static void updateRoomPrice(int idRoom , double newPrice);
    static bool ifPasswordExist(const string& password);
    static bool ifExistAdmin(const string& login);
    static void registerAdmin();
    static void adminMenu(Admin& admin, list<Reservation>& reservations);
    static void addRoom();
    void writeToFile() override;
    static bool ifExist(int idRoom);
    static void removeReservationById(int idGuest);
    static void checkAvailableRooms();
    static void viewGuestsWithoutReservations();
    static void shtrix();

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

    Admin& operator=(const Admin& admin);
    Admin& operator=(Admin&& admin) noexcept;

    bool operator==(const Admin& other) const;
    bool operator!=(const Admin& other) const;
    bool operator<(const Admin& other) const;
    bool operator>(const Admin& other) const;

    [[nodiscard]] string getLogin() const;
    [[nodiscard]] string getPassword() const;
    void setLogin(const string& _login);
    void setPassword(const string& _password);


};

#endif //HOTELMANEGEMENT_ADMIN_H
