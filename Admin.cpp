#include "Admin.h"
#include "fstream"

// Constructors
Admin::Admin() : login(""), password("") {}

Admin::Admin(string  newLogin, string  newPassword)
        : login(std::move(newLogin)), password(std::move(newPassword)) {}

Admin::Admin(const Admin& admin)
        : login(admin.login), password(admin.password) {}

Admin::Admin(Admin&& admin) noexcept
        : login(std::move(admin.login)), password(std::move(admin.password)) {}

Admin::~Admin() {}

istream& operator>>(istream& is, Admin& admin) {
    is >> admin.login;
    is >> admin.password;
    return is;
}

ostream& operator<<(ostream& os, const Admin& admin) {
    os << "Admin Login: " << admin.login << ", Password: " << admin.password;
    return os;
}

// Operator =
Admin& Admin::operator=(const Admin& admin) {
    if (this != &admin) {
        login = admin.login;
        password = admin.password;
    }
    return *this;
}

Admin& Admin::operator=(Admin&& admin) noexcept {
    if (this != &admin) {
        login = std::move(admin.login);
        password = std::move(admin.password);
    }
    return *this;
}
// Getters and Setters
string Admin::getLogin() const {
    return login;
}

string Admin::getPassword() const {
    return password;
}

void Admin::setLogin(const string& _login) {
    login = _login;
}

void Admin::setPassword(const string& _password) {
    password = _password;
}
// Operators == , != , >, <
bool Admin::operator==(const Admin& other) const {
    return login == other.login && password == other.password;
}

bool Admin::operator!=(const Admin& other) const {
    return !(*this == other);
}

bool Admin::operator<(const Admin& other) const {
    if (login != other.login) {
        return login < other.login;
    }
    return password < other.password;
}

bool Admin::operator>(const Admin& other) const {
    return other < *this;
}

void Admin::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Admins.txt)", ios_base::app);
    fout << login << "\t" << password << endl;
    fout.close();
}

