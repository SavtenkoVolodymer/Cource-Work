#include "Reservation.h"

#include <utility>
#include "fstream"
#include "istream"

// Constructors
Reservation::Reservation() : guest(""), check_in(Date()), check_out(Date()), room(nullptr) {}

Reservation::Reservation(string newGuest, Date  newCheckIn, Date  newCheckOut, int newRoom)
        : guest(std::move(newGuest)), check_in(std::move(newCheckIn)), check_out(std::move(newCheckOut)), room(make_unique<int>(newRoom)) {}

Reservation::Reservation(const Reservation& reservation)
        : guest(reservation.guest),
          check_in(reservation.check_in),
          check_out(reservation.check_out),
          room(make_unique<int>(*reservation.room)) {}

Reservation::Reservation(Reservation&& reservation) noexcept
        : guest(std::move(reservation.guest)),
          check_in(std::move(reservation.check_in)),
          check_out(std::move(reservation.check_out)),
          room(std::move(reservation.room)) {}

Reservation::~Reservation() {}

// Operator =
Reservation& Reservation::operator=(const Reservation& reservation) {
    if (this != &reservation) {
        guest = reservation.guest;
        check_in = reservation.check_in;
        check_out = reservation.check_out;
        room = make_unique<int>(*reservation.room);
    }
    return *this;
}

Reservation& Reservation::operator=(Reservation&& reservation) noexcept {
    if (this != &reservation) {
        guest = std::move(reservation.guest);
        check_in = std::move(reservation.check_in);
        check_out = std::move(reservation.check_out);
        room = std::move(reservation.room);
    }
    return *this;
}

// Operators == , != , < , >
bool Reservation::operator==(const Reservation& other) const {
    return guest == other.guest &&
           check_in == other.check_in &&
           check_out == other.check_out &&
           *room == *other.room;
}

bool Reservation::operator!=(const Reservation& other) const {
    return !(*this == other);
}

bool Reservation::operator<(const Reservation& other) const {
    if (guest != other.guest) {
        return guest < other.guest;
    }
    if (check_in != other.check_in) {
        return check_in < other.check_in;
    }
    if (check_out != other.check_out) {
        return check_out < other.check_out;
    }
    return *room < *other.room;
}

bool Reservation::operator>(const Reservation& other) const {
    return other < *this;
}

// Getters and Setters
string Reservation::getGuest() const {
    return guest;
}

const Date& Reservation::getCheckIn() const {
    return check_in;
}

const Date& Reservation::getCheckOut() const {
    return check_out;
}

int Reservation::getRoom() const {
    return *room;
}

void Reservation::setGuest(const string& newGuest) {
    guest = newGuest;
}

void Reservation::setCheckIn(const Date& newCheckIn) {
    check_in = newCheckIn;
}

void Reservation::setCheckOut(const Date& newCheckOut) {
    check_out = newCheckOut;
}

void Reservation::setRoom(int newRoom) {
    room = make_unique<int>(newRoom);
}

istream &operator>>(istream& is, Reservation& reservation){

   is >> reservation.guest ;

   int year, month, day;
   is >> year >> month >> day;
   is >> year >> month >> day;
   is >> *reservation.room;

   return is;
}


ostream &operator << (ostream& os, const Reservation& reservation) {
    os << reservation.guest << "\t" << &reservation.check_in << "\t"<< &reservation.check_out << "\t"
       << &reservation.room;
    return os;
}

void Reservation::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::app);
    fout << guest << "\t" << &check_in << "\t" << &check_out << "\t" << *room<< endl;
    fout.close();
}

