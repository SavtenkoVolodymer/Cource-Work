#ifndef HOTELMANEGEMENT_ADMIN_H
#define HOTELMANEGEMENT_ADMIN_H

#include <iostream>
#include <string>

using namespace std;

class Admin {
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
    ~Admin();

    void writeToFile();

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
