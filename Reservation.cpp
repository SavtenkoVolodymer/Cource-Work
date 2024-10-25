#include "Reservation.h"
#include <utility>
#include "fstream"
#include "istream"
#include "algorithm"

// Constructors
Reservation::Reservation() : guest(), check_in(), check_out(), room(nullptr) {}


Reservation::Reservation(Guest& newGuest, Date& newCheckIn, Date& newCheckOut, unique_ptr<Room> newRoom)
        : guest(newGuest), check_in(newCheckIn), check_out(newCheckOut), room(std::move(newRoom)) {}

Reservation::Reservation(const Reservation& reservation)
        : check_in(reservation.check_in), check_out(reservation.check_out),
          room(reservation.room ? make_unique<Room>(*reservation.room) : nullptr),
          guest(reservation.guest) {}

Reservation::Reservation(Reservation&& reservation) noexcept
        : check_in(std::move(reservation.check_in)), check_out(std::move(reservation.check_out)),
          room(std::move(reservation.room)), guest(std::move(reservation.guest)) {}

Reservation::~Reservation() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Guest: "<< this->getGuest().getName() << " Room: " << *room << endl;
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
    if (guest != other.guest) {
        return false;
    }
    return (check_in == other.check_in) &&
           (check_out == other.check_out) &&
           (*room == *other.room);
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

void Reservation::setRoom(Room &newRoom) {
    room = make_unique<Room>(newRoom);
}


istream &operator>>(istream& is, Reservation& reservation){
    int idGuest;
    int yearGuest;
    string name;
    string surname;
    is >> idGuest >> name >> surname >> yearGuest;
    Guest guest (name,idGuest,yearGuest,surname);
    reservation.setGuest(guest);
   int year, month, day;
   is >> year >> month >> day;
   Date checkIn (year , month ,day);
   reservation.setCheckIn(checkIn);
   is >> year >> month >> day;
   Date checkOut (year , month ,day);
    reservation.setCheckOut(checkOut);
    int idRoom;
    bool isOccupied;
    double pricePerNight;
    int currentOccupancy;
    is >> idRoom >> isOccupied>> pricePerNight >> currentOccupancy;
    Room room (idRoom, isOccupied, pricePerNight,currentOccupancy);
    reservation.setRoom(room);
   cout << reservation.getGuest();
   cout << reservation.getCheckIn().getDate();
   cout << reservation.getCheckOut().getDate();
   cout << reservation.getRoom();

   return is;
}

ostream &operator << (ostream& os, const Reservation& reservation) {
    os << reservation.getGuest() << "\t" << reservation.getCheckIn().getDate()<< "\t"<<reservation.getCheckOut().getDate() << "\t"
       << *reservation.room << endl;
    return os;
}




void Reservation::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::app);
    fout << this->getGuest().toString() << " " << check_in.getDate() << " " << check_out.getDate() << " " << *room<<endl;
    fout.close();
}

double Reservation::getPrice() {
    return (this->check_out-this->check_in ) * this->getPriceFromFile();
}

//list<Reservation> Reservation::reservationFromFile() {
//    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)");
//
//    if (!fin.is_open()) {
//        cerr << "Error: Could not open the file " << endl;
//    }
//    list<Reservation> reservations;
//    int idGuest;
//    int yearGuest;
//    string name;
//    string surname;
//
//    int year1, month2, day3;
//    int year, month, day;
//
//    int idRoom;
//    bool isOccupied;
//    double pricePerNight;
//    int currentOccupancy;
//    while (fin >> idGuest >> name >> surname >> yearGuest >>
//    year >> month >> day >> year1 >>month2>>day3>>
//    idRoom>>isOccupied>>pricePerNight>>currentOccupancy) {
//        Reservation reservation;
//        reservation.setGuest(Guest (name,idGuest,year,surname));
//        reservation.setCheckIn(Date(year,month,day));
//        reservation.setCheckOut(Date(year1,month2,day3));
//        unique_ptr<Room> room1 = make_unique<Room>(Room(idRoom,isOccupied,pricePerNight,currentOccupancy));
//        reservation.setRoom(*room1);

//        string guestName, guestSurname;
//        int guestId, guestYear;
//
//        fin >> guestId >> guestName >> guestSurname >> guestYear;
//        Guest guest (guestName, guestId, guestYear, guestSurname);
//        int year, month, day;
//
//        fin >> year >> month >> day;
//        Date checkIn(year, month, day);
//
//        fin >> year >> month >> day;
//
//        Date checkOut(year, month, day);
//
//        int idRoom;
//        bool isOccupied;
//        double pricePerNight;
//        int currentOccupancy;
//        fin >> idRoom >> isOccupied >> pricePerNight >> currentOccupancy;
//
//        unique_ptr<Room> room = make_unique<Room>(idRoom, isOccupied, pricePerNight, currentOccupancy);
//
//        Reservation reservation(guest, checkIn, checkOut, std::move(room));


//        reservations.push_back(reservation);
//    }
//    fin.close();
//    return reservations;
//}


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


list<Reservation> Reservation::reservationFromFile() {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)");

    if (!fin.is_open()) {
        cerr << "Error: Could not open the file " << endl;
        return {};
    }

    list<Reservation> reservations;
    int idGuest, yearGuest, idRoom, currentOccupancy;
    string name, surname;
    int yearCheckIn, monthCheckIn, dayCheckIn;
    int yearCheckOut, monthCheckOut, dayCheckOut;
    bool isOccupied;
    double pricePerNight;

    while (fin >> idGuest >> name >> surname >> yearGuest >>
               yearCheckIn >> monthCheckIn >> dayCheckIn >>
               yearCheckOut >> monthCheckOut >> dayCheckOut >>
               idRoom >> isOccupied >> pricePerNight >> currentOccupancy) {

        Reservation reservation;
        reservation.setGuest(Guest(name, idGuest, yearGuest, surname));
        reservation.setCheckIn(Date(yearCheckIn, monthCheckIn, dayCheckIn));
        reservation.setCheckOut(Date(yearCheckOut, monthCheckOut, dayCheckOut));

        unique_ptr<Room> room1 = make_unique<Room>(idRoom, isOccupied, pricePerNight, currentOccupancy);
        reservation.setRoom(*room1);

        if (find(reservations.begin(), reservations.end(), reservation) == reservations.end()) {
            reservations.push_back(reservation);
        }
    }

    fin.close();
    return reservations;
}
