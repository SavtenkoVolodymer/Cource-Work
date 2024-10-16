#include "Guest.h"
#include "fstream"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "TripleRoom.h"

// Constructors
Guest::Guest() : name(""), idGuest(0), year(0), surname("") {}

Guest::Guest(string &newName, int newIdGuest, int newYear, string &newSurname)
        : name(newName), idGuest(newIdGuest), year(newYear), surname(newSurname) {}

Guest::Guest(const Guest& guest)
        : name(guest.name), idGuest(guest.idGuest), year(guest.year), surname(guest.surname) {}

Guest::Guest(Guest&& guest) noexcept
        : name(std::move(guest.name)), idGuest(guest.idGuest), year(guest.year), surname(std::move(guest.surname)) {
    guest.idGuest = 0;
    guest.year = 0;
}

istream& operator>>(istream& is, Guest& guest) {
    is >> guest.idGuest>> guest.name >> guest.surname >> guest.year;
    return is;
}

ostream& operator<<(ostream& os, const Guest& guest) {
    os << guest.idGuest << "\t" << guest.name << "\t" << guest.surname<< "\t"<< "\t"<<guest.year;
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

Guest::~Guest() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Name: "<< name << " Surname: " << surname << endl;
    fout.close();
}

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

bool Guest::sortBySurname(const std::string &newSurname) const {
    return name == newSurname;
}

//Functions

//unique_ptr<Room> Guest::getRoomFromFile(int idRoom) {
//    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedSingleR.txt)");
//    unique_ptr<Room> room = make_unique<Room>(Room ());
//    while(fin >> *room){
//        if(room->getIdRoom()== idRoom)
//            return room;
//    }
//    fin.close();
//}

//void Guest::addReservation() const {
//    cout << "Enter check in date: " << endl;
//    unique_ptr <int> year1 = make_unique <int> (getInput<int>("Enter check in year: " ));
//
//    unique_ptr <int> month1 = make_unique <int> (getInput<int>("Enter check in month: "));
//
//    unique_ptr <int> day1 = make_unique <int> (getInput<int>("Enter check in day: "));
//
//    Date date1(*year1, *month1, *day1);
//
//    cout << "Enter check out date: " << endl;
//    unique_ptr <int> year2 = make_unique <int> (getInput<int>("Enter check out year: " ));
//
//    unique_ptr <int> month2 = make_unique <int> (getInput<int>("Enter check out month: "));
//
//    unique_ptr <int> day2 = make_unique <int> (getInput<int>("Enter check out day: "));
//
//    unique_ptr <int> room = make_unique <int> (getInput<int>("Enter number of room: "));
//    Date date2(*year2, *month2, *day2);
//    try {
//        if (ifExist(*room)) {
//            Reservation reservation(this, date1, date2, Guest::getRoomFromFile(2));
//            reservation.writeToFile();
//        } else {
//            throw runtime_error("This id of room does not exist!!");
//        }
//    }catch (exception &e){
//        cerr << e.what() << endl;
//    }
//}

void Guest::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Guests.txt)", ios_base::app);
    fout << idGuest << "\t" << name << "\t" << surname << "\t"<< year << endl;
    fout.close();
}


bool Guest::ifExist(int idRoom) {
    ifstream fin1(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedSingleR.txt)");
    SingleRoom room1;
    while (fin1 >> room1) {
        if (room1.getIdRoom() == idRoom) {
            return true;
        }
    }
    fin1.close();

    ifstream fin2(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedDoubleR.txt)");
    DoubleRoom room2;
    while (fin2 >> room2) {
        if (room2.getIdRoom() == idRoom) {
            return true;
        }
    }
    fin2.close();

    ifstream fin3(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\FreedTripleR.txt)");
    TripleRoom room3;
    while (fin3 >> room3) {
        if (room3.getIdRoom() == idRoom) {
            return true;
        }
    }
    fin3.close();
    return false;
}

void Guest::viewReservations(const list<Reservation>& reservations) const {
    cout << "Reservations for guest: " << name << " (ID: " << idGuest << ")" << endl;
    bool found = false;

    for (const auto& res : reservations) {
        if (res.getGuest().getIdGuest() == idGuest) {
            cout << "Reservation from " << res.getCheckIn().getDate()
                 << " to " << res.getCheckOut().getDate()
                 << " in Room " << res.getRoom().getIdRoom() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No reservations found for this guest." << endl;
    }
}
