#include "Reservation.h"
#include <utility>
#include "fstream"
#include "istream"

// Constructors
Reservation::Reservation() : guest(), check_in(), check_out(), room(nullptr) {}


Reservation::Reservation(const shared_ptr<Guest>& newGuest, Date& newCheckIn, Date& newCheckOut, unique_ptr<Room> newRoom)
        : check_in(newCheckIn), check_out(newCheckOut), room(std::move(newRoom)), guest(newGuest) {}

Reservation::Reservation(const Reservation& reservation)
        : check_in(reservation.check_in), check_out(reservation.check_out),
          room(reservation.room ? make_unique<Room>(*reservation.room) : nullptr),
          guest(reservation.guest) {}

Reservation::Reservation(Reservation&& reservation) noexcept
        : check_in(std::move(reservation.check_in)), check_out(std::move(reservation.check_out)),
          room(std::move(reservation.room)), guest(std::move(reservation.guest)) {}

Reservation::~Reservation() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Guest: "<< this->getGuest()->getName() << " Room: " << *room << endl;
    fout.close();
}

// Operator =
Reservation& Reservation::operator=(const Reservation& reservation) {
    if (this != &reservation) {
        guest = reservation.guest;
        check_in = reservation.check_in;
        check_out = reservation.check_out;
        room = make_unique<Room>(*reservation.room);
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
    shared_ptr<Guest> thisGuest = guest.lock();
    shared_ptr<Guest> otherGuest = other.guest.lock();

    return (thisGuest == otherGuest) &&
           check_in == other.check_in &&
           check_out == other.check_out &&
           *room == *other.room;
}

bool Reservation::operator!=(const Reservation& other) const {
    return !(*this == other);
}

bool Reservation::operator<(const Reservation& other) const {
    shared_ptr<Guest> thisGuest = guest.lock();
    shared_ptr<Guest> otherGuest = other.guest.lock();

    if (thisGuest && otherGuest) {
        if (*thisGuest != *otherGuest) {
            return *thisGuest < *otherGuest;
        }
    } else if (thisGuest) {
        return false;
    } else if (otherGuest) {
        return true;
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
shared_ptr<Guest> Reservation::getGuest() const {
    return guest.lock();
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

void Reservation::setGuest(const shared_ptr<Guest>& newGuest) {
    guest = weak_ptr<Guest>(newGuest);
}

void Reservation::setCheckIn(const Date& newCheckIn) {
    check_in = newCheckIn;
}

void Reservation::setCheckOut(const Date& newCheckOut) {
    check_out = newCheckOut;
}

void Reservation::setRoom(Room &newRoom) {
    room = make_unique<Room>(newRoom);
}


istream &operator>>(istream& is, Reservation& reservation){

   is >> *reservation.getGuest() ;
   int year, month, day;
   is >> year >> month >> day;
   Date checkIn (year , month ,day);
   reservation.setCheckIn(checkIn);
   is >> year >> month >> day;
   Date checkOut (year , month ,day);
    reservation.setCheckOut(checkOut);
   is >> day ;
   cout << reservation.getGuest();
   cout << reservation.getCheckIn().getDate();
   cout << reservation.getCheckOut().getDate();
   cout << reservation.getRoom();

   return is;
}


ostream &operator << (ostream& os, const Reservation& reservation) {
    os << reservation.getGuest() << "\t" << reservation.getCheckIn().getDate()<< "\t"<<reservation.getCheckOut().getDate() << "\t"
       << *reservation.room;
    return os;
}

string Reservation::getGuestName() const {
    return this->getGuest()->getName();
}


void Reservation::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::app);
    fout << this->getGuest()->toString() << " " << check_in.getDate() << " " << check_out.getDate() << " " << *room<<endl<< endl;
    fout.close();
}

double Reservation::getPrice() {
    return (this->check_out-this->check_in ) * this->getPriceFromFile();
}

list<Reservation> Reservation::reservationFromFile() {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)");

    if (!fin.is_open()) {
        cerr << "Error: Could not open the file " << endl;
    }
    list<Reservation> reservations;

    while (fin) {
        string guestName, guestSurname;
        int guestId, guestYear;


        fin >> guestId >> guestName >> guestSurname >> guestYear;
        shared_ptr<Guest> guest = make_shared<Guest>(guestName, guestId, guestYear, guestSurname);

        int year, month, day;

        fin >> year >> month >> day;
        Date checkIn(year, month, day);

        fin >> year >> month >> day;

        Date checkOut(year, month, day);

        int idRoom;
        bool isOccupied;
        double pricePerNight;
        int currentOccupancy;
        fin >> idRoom >> isOccupied >> pricePerNight >> currentOccupancy;

        unique_ptr<Room> room = make_unique<Room>(idRoom, isOccupied, pricePerNight, currentOccupancy);

        Reservation reservation(guest, checkIn, checkOut, std::move(room));

        reservations.emplace_back(reservation);
    }

    fin.close();
    return reservations;
}


double Reservation::getPriceFromFile() const {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    Room rooms;
    while (fin >> rooms) {
        if (rooms.getIdRoom() == this->getRoom().getIdRoom()) {
            return rooms.getPricePerNight();
        }
    }
    fin.close();
    return 0;
}
