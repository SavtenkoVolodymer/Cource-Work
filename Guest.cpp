#include "Guest.h"
#include "fstream"


// Constructors
Guest::Guest() : Person(), name(" "), idGuest(0), year(0), surname(" ") {}

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
    os << guest.idGuest << "\t" << guest.name << "\t" << guest.surname<< "\t"<<guest.year<<"\t";
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

//Functions

void Guest::getGuest() {
    cout <<"Id Guest: " << idGuest <<endl
    << "Guest name: " << name << endl
    << "Guest surname: "<< surname<< endl
    << "Guest date of birth"<<year << endl;
}
unique_ptr<Room> Guest::getRoomFromFile(int idRoom) {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    unique_ptr<Room> room = make_unique<Room>(Room ());
    while(fin >> *room){
        if(room->getIdRoom()== idRoom)
            return room;
    }
    fin.close();
    return {};
}



void Guest::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Guests.txt)", ios_base::app);
    fout << idGuest << "\t" << name << "\t" << surname << "\t"<< year << endl;
    fout.close();
}
bool Guest::ifExistGuest(int idGuest) {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Guests.txt)");
    if (!fin.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return false;
    }

    string name, surname;
    int existingId, year;

    while (fin >> existingId >> name >> surname >> year) {
        if (existingId == idGuest) {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

Guest Guest::registerGuest() {
    string name, surname;
    int idGuest, year;

    cout << "\nRegistering Guest:" << endl;
    while (true) {
        cout << " Enter name: ";
        cin >> name;
        if (!isalpha(name[0]) || !isupper(name[0])) {
            cout << "Invalid name. The name should start with a capital letter and contain only letters." << endl;
            continue;
        }
        bool valid = true;
        for (char c : name) {
            if (!isalpha(c)) {
                cout << "Invalid name. Name should only contain letters." << endl;
                valid = false;
                break;
            }
        }
        if (valid) break;
    }
    while (true) {
        cout << "Enter surname: ";
        cin >> surname;
        if (!isalpha(surname[0]) || !isupper(surname[0])) {
            cout << "Invalid surname. The surname should start with a capital letter and contain only letters." << endl;
            continue;
        }

        bool valid = true;
        for (char c : surname) {
            if (!isalpha(c)) {
                cout << "Invalid surname. Surname should only contain letters." << endl;
                valid = false;
                break;
            }
        }
        if (valid) break;
    }
    while (true) {
        cout << "Enter guest ID: ";
        cin >> idGuest;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number for the ID." << endl;
            continue;
        }
        if (ifExistGuest(idGuest)) {
            cout << "Guest ID already exists. Please enter a different ID." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Enter birth year: ";
        cin >> year;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number for the year." << endl;
            continue;
        }
        if (year < 1900 || year > 2024) {
            cout << "Invalid year. Please enter a year between 1900 and 2024." << endl;
        } else {
            break;
        }
    }

    Guest guest(name, idGuest, year, surname);

    cout << "Guest successfully registered!" << endl;
    cout << "Guest details: " << guest << endl;

    guest.writeToFile();
    return guest;
}




string Guest::toString() const {
    string g_id = std::to_string(idGuest);
    string g_year = std::to_string(year);
    return g_id + "\t" +name + "\t" + surname + "\t" + g_year;
}