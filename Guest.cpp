#include "Guest.h"
#include "fstream"

// Constructors
Guest::Guest() : name(""), idGuest(0), year(0), surname("") {}

Guest::Guest(string newName, int newIdGuest, int newYear, string newSurname)
        : name(std::move(newName)), idGuest(newIdGuest), year(newYear), surname(std::move(newSurname)) {}

Guest::Guest(const Guest& guest)
        : name(guest.name), idGuest(guest.idGuest), year(guest.year), surname(guest.surname) {}

Guest::Guest(Guest&& guest) noexcept
        : name(std::move(guest.name)), idGuest(guest.idGuest), year(guest.year), surname(std::move(guest.surname)) {
    guest.idGuest = 0;
    guest.year = 0;
}

istream& operator>>(istream& is, Guest& guest) {
    is >> guest.name >> guest.idGuest >> guest.year >> guest.surname;
    return is;
}

ostream& operator<<(ostream& os, const Guest& guest) {
    os << "Guest ID: " << guest.idGuest << ", Name: " << guest.name << ", Surname: " << guest.surname << ", Year: " << guest.year;
    return os;
}

// Operator =
Guest& Guest::operator=(const Guest& other) {
    if (this != &other) {
        name = other.name;
        idGuest = other.idGuest;
        year = other.year;
        surname = other.surname;
    }
    return *this;
}

Guest& Guest::operator=(Guest&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        idGuest = other.idGuest;
        year = other.year;
        surname = std::move(other.surname);
        other.idGuest = 0;
        other.year = 0;
    }
    return *this;
}

Guest::~Guest() {}

// Operators == , !- , >, <
bool Guest::operator==(const Guest& other) const {
    return idGuest == other.idGuest && name == other.name && year == other.year && surname == other.surname;
}

bool Guest::operator!=(const Guest& other) const {
    return !(*this == other);
}

bool Guest::operator<(const Guest& other) const {
    if (idGuest != other.idGuest) {
        return idGuest < other.idGuest;
    }
    if (year != other.year) {
        return year < other.year;
    }
    return name < other.name;
}

bool Guest::operator>(const Guest& other) const {
    return other < *this;
}

// Getters and Setters
string Guest::getName() const {
    return name;
}

int Guest::getIdGuest() const {
    return idGuest;
}

int Guest::getYear() const {
    return year;
}

string Guest::getSurname() const {
    return surname;
}

void Guest::setName(const string& _name) {
    name = _name;
}

void Guest::setIdGuest(int _idGuest) {
    idGuest = _idGuest;
}

void Guest::setYear(int _year) {
    year = _year;
}

void Guest::setSurname(const string& _surname) {
    surname = _surname;
}

// Sort
bool Guest::sortByName(const string& newName) const {
    return name == newName;
}

bool Guest::sortByHighYear(int newYear) const {
    return year >= newYear;
}

bool Guest::sortByLowYear(int newYear) const {
    return year<= newYear;
}

void Guest::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Guests.txt)", ios_base::app);
    fout << name << "\t" << surname << "\t" << idGuest << "\t"<< year << endl;
    fout.close();
}

