#include "Reservation.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "TripleRoom.h"
#include <utility>
#include "fstream"
#include "istream"

// Constructors
Reservation::Reservation() : guest(Guest()), check_in(Date()), check_out(Date()), room(make_unique<Room>(Room())) {}

Reservation::Reservation(Guest &newGuest, Date & newCheckIn, Date & newCheckOut,unique_ptr<Room> newRoom)
        : guest(newGuest), check_in(newCheckIn), check_out(newCheckOut),  room(std::move(newRoom)) {}

//Reservation::Reservation(const Reservation& reservation)
//        : guest(reservation.guest), check_in(reservation.check_in), check_out(reservation.check_out), room(reservation.room) {}

Reservation::Reservation(Reservation&& reservation) noexcept
        : guest(std::move(reservation.guest)),
          check_in(std::move(reservation.check_in)),
          check_out(std::move(reservation.check_out)),
          room(std::move(reservation.room)) {}

Reservation::~Reservation() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Guest: "<< guest << " Room: " << *room << endl;
    fout.close();
}

// Operator =
//Reservation& Reservation::operator=(const Reservation& reservation) {
//    if (this != &reservation) {
//        guest = reservation.guest;
//        check_in = reservation.check_in;
//        check_out = reservation.check_out;
//        room = make_unique<Room>(*reservation.room);
//    }
//    return *this;
//}

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
Guest Reservation::getGuest() const {
    return guest;
}

Date Reservation::getCheckIn() const {
    return check_in;
}

Date Reservation::getCheckOut() const {
    return check_out;
}

const Room& Reservation::getRoom() const {
    return *room;
}

void Reservation::setGuest(const Guest& newGuest) {
    guest = newGuest;
}

void Reservation::setCheckIn(const Date& newCheckIn) {
    check_in = newCheckIn;
}

void Reservation::setCheckOut(const Date& newCheckOut) {
    check_out = newCheckOut;
}

void Reservation::setRoom(unique_ptr<Room> newRoom) {
    room = std::move(newRoom);
}


istream &operator>>(istream& is, Reservation& reservation){

   is >> reservation.guest ;
   int year, month, day;
   is >> year >> month >> day;
   Date checkIn (year , month ,day);
   reservation.setCheckIn(checkIn);
   is >> year >> month >> day;
   Date checkOut (year , month ,day);
    reservation.setCheckOut(checkOut);
//       is >> *reservation.room;
   is >> day ;
//   reservation.setRoom(day);
   cout << reservation.getGuest();
   cout << reservation.getCheckIn().getDate();
   cout << reservation.getCheckOut().getDate();
   cout << reservation.getRoom();

   return is;
}
//istream& operator>>(istream& is, Reservation& reservation) {
//    is >> reservation.guest;
//    int year, month, day;
//    is >> year >> month >> day;
//    Date checkIn(year, month, day);
//    reservation.setCheckIn(checkIn);
//
//    is >> year >> month >> day;
//    Date checkOut(year, month, day);
//    reservation.setCheckOut(checkOut);
//
//    if (!reservation.room) {
//        reservation.room = make_unique<int>();
//    }
//
//    is >> *reservation.room;
//
//    return is;
//}


ostream &operator << (ostream& os, const Reservation& reservation) {
    os << reservation.guest << "\t" << reservation.getCheckIn().getDate()<< "\t"<<reservation.getCheckOut().getDate() << "\t"
       << *reservation.room;
    return os;
}


void Reservation::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::app);
    fout << guest << "\t" << check_in.getDate() << "\t" << check_out.getDate() << "\t" << *room<< endl;
    fout.close();
}

double Reservation::getPrice() {
    double buff = check_out.getDay()-check_in.getDay();
    return buff * this->getPriceFromFile();
}


double Reservation::getPriceFromFile() const {
    ifstream fin1(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedSingleR.txt)");
    SingleRoom room1;
    while (fin1 >> room1) {
        if (room1.getIdRoom() == this->getRoom().getIdRoom()) {
            return room1.getPricePerNight();
        }
    }
    fin1.close();

    ifstream fin2(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedDoubleR.txt)");
    DoubleRoom room2;
    while (fin2 >> room2) {
        if (room2.getIdRoom() == this->getRoom().getIdRoom()) {
            return room2.getPricePerNight();
        }
    }
    fin2.close();

    ifstream fin3(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedTripleR.txt)");
    TripleRoom room3;
    while (fin3 >> room3) {
        if (room3.getIdRoom() == this->getRoom().getIdRoom()) {
            return room3.getPricePerNight();
        }
    }
    fin3.close();
    return 0;
}