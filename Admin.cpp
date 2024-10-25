#include "Admin.h"
#include <ctime>
#include "fstream"
#include "GuestList.h"
#include "RoomList.h"
#include "Reservation.h"
#include "Date.h"

// Constructors
Admin::Admin() : login(""), password("") {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)");
    fout << " Logged in as admin" << endl;
    fout.close();
}

Admin::Admin(string newLogin, string newPassword)
        : login(std::move(newLogin)), password(std::move(newPassword)) {}

Admin::Admin(const Admin &admin)
        : login(admin.login), password(admin.password) {}

Admin::Admin(Admin &&admin) noexcept
        : login(std::move(admin.login)), password(std::move(admin.password)) {}

Admin::~Admin() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout <<"Destructor from Admin"<< endl;
    fout.close();
}

istream &operator>>(istream &is, Admin &admin) {
    is >> admin.login;
    is >> admin.password;
    return is;
}

ostream &operator<<(ostream &os, const Admin &admin) {
    os << "Admin Login: " << admin.login << ", Password: " << admin.password;
    return os;
}

// Operator =
Admin &Admin::operator=(const Admin &admin) {
    if (this != &admin) {
        login = admin.login;
        password = admin.password;
    }
    return *this;
}

Admin &Admin::operator=(Admin &&admin) noexcept {
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

void Admin::setLogin(const string &_login) {
    login = _login;
}

void Admin::setPassword(const string &_password) {
    password = _password;
}

// Operators == , != , >, <
bool Admin::operator==(const Admin &other) const {
    return login == other.login && password == other.password;
}

bool Admin::operator!=(const Admin &other) const {
    return !(*this == other);
}

bool Admin::operator<(const Admin &other) const {
    if (login != other.login) {
        return login < other.login;
    }
    return password < other.password;
}

bool Admin::operator>(const Admin &other) const {
    return other < *this;
}

void Admin::shtrix() {
    cout << "-----------------------------------------------------------------------"<<endl;
}



void Admin::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Admins.txt)", ios_base::app);
    fout << login << "\t" << password << endl;
    fout.close();
}

void Admin::viewGuestsWithoutReservations() {
    ifstream guestFile(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Guests.txt)");
    ifstream reservationFile(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)");

    if (!guestFile.is_open()) {
        cerr << "Error: Could not open the Guests file." << endl;
        return;
    }
    if (!reservationFile.is_open()) {
        cerr << "Error: Could not open the Reservations file." << endl;
        return;
    }

    list<Guest> allGuests;
    string guestName, guestSurname;
    int guestId, guestYear;

    while (guestFile >> guestId >> guestName >> guestSurname >> guestYear) {
        Guest guest(guestName, guestId, guestYear, guestSurname);
        allGuests.push_back(guest);
    }
    guestFile.close();

    list<int> reservedGuestIds;
    int resGuestId;
    string temp;
    while (reservationFile >> resGuestId >> temp >> temp >> temp >> temp) {
        reservedGuestIds.push_back(resGuestId);
    }
    reservationFile.close();

    cout << "\nGuests without reservations:\n";
    bool hasGuestsWithoutReservation = false;

    for (const auto& guest : allGuests) {
        bool foundReservation = false;

        for (const auto& reservedGuestId : reservedGuestIds) {
            if (guest.getIdGuest() == reservedGuestId) {
                foundReservation = true;
                break;
            }
        }
        if (!foundReservation) {
            cout << "Guest: " << guest.getName() << " " << guest.getSurname()
                 << ", ID: " << guest.getIdGuest() << ", Year: " << guest.getYear() << endl;
            hasGuestsWithoutReservation = true;
        }
    }
    if (!hasGuestsWithoutReservation) {
        cout << "All guests have reservations.\n";
    }
}


void Admin::updateRoomPrice(int roomId, double newPrice) {

    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    if (!fin.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    list<Room> rooms;
    int idRoom;
    bool isOccupied;
    double pricePerNight;
    int currentOccupancy;
    bool roomFound = false;

    while (fin >> idRoom >> isOccupied >> pricePerNight >> currentOccupancy) {
        Room room(idRoom, isOccupied, pricePerNight, currentOccupancy);
        if (room.getIdRoom() == roomId) {
            roomFound = true;
        }
        rooms.push_back(room);
    }
    fin.close();

    if (!roomFound) {
        cout << "Room with ID " << roomId << " not found." << endl;
        return;
    }

    for (auto& room : rooms) {
        if (room.getIdRoom() == roomId) {
            room.setPricePerNight(newPrice);
        }
    }
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    if (!fout.is_open()) {
        cerr << "Error: Could not open the file for writing." << endl;
        return;
    }
    for (const auto& room : rooms) {
        fout << room.getIdRoom() << " "
             << room.getIsOccupied() << " "
             << room.getPricePerNight() << " "
             << room.getCurrentOccupancy() << endl;
    }
    fout.close();
    cout << "Room price updated successfully!" << endl;
}


void Admin::saveReservationsToFile(const list<Reservation>& reservations) {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::trunc);

    if (!fout.is_open()) {
        cerr << "Error opening file for writing reservations!" << endl;
        return;
    }

    for (const auto& reservation : reservations) {
        fout << reservation.getGuest().toString() << "\t"
             << reservation.getCheckIn().getDate() << "\t"
             << reservation.getCheckOut().getDate() << "\t"
             << reservation.getRoom().getIdRoom() << "\n";
    }

    fout.close();
    cout << "Reservations saved to file successfully." << endl;
}

bool Admin::ifPasswordExist(const string& password) {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Admins.txt)");
    if (!fin.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return false;
    }

    string existingLogin, existingPassword;

    while (fin >> existingLogin >> existingPassword) {
        if (existingPassword == password) {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}
bool Admin::ifExistAdmin(const string& login) {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Admins.txt)");
    if (!fin.is_open()) {
        cerr << "Error: Could not open the file for reading." << endl;
        return false;
    }

    string existingLogin, existingPassword;
    while (fin >> existingLogin >> existingPassword) {
        if (existingLogin == login) {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}
void Admin::registerAdmin() {
    string login, password;

    cout << "\nRegistering/Administering Admin:" << endl;

    // Валідація логіна (англійські літери та цифри)
    while (true) {
        cout << " Enter login: ";
        cin >> login;

        bool isValidLogin = true;
        for (char c : login) {
            if (!isalnum(c) || !isascii(c)) {  // Логін може містити лише англійські літери та цифри
                isValidLogin = false;
                break;
            }
        }

        if (!isValidLogin) {
            cout << "Login must contain only English letters and numbers. Please try again." << endl;
        } else if (ifExistAdmin(login)) {
            cout << "Authorization successful! Admin already exists." << endl;
            return;
        } else {
            break;
        }
    }

    // Валідація пароля (англійські літери та цифри)
    while (true) {
        cout << "Enter password: ";
        cin >> password;

        bool isValidPassword = true;
        for (char c : password) {
            if (!isalnum(c) || !isascii(c)) {  // Пароль також може містити лише англійські літери та цифри
                isValidPassword = false;
                break;
            }
        }

        if (!isValidPassword) {
            cout << "Password must contain only English letters and numbers. Please try again." << endl;
        } else if (ifPasswordExist(password)) {
            cout << "Password already exists. Please enter a different password." << endl;
        } else {
            break;
        }
    }

    Admin admin(login, password);
    cout << "Admin successfully registered!" << endl;
    cout << "Admin details: " << admin << endl;

    Admin::shtrix();
    admin.writeToFile();
}





void Admin::adminMenu(Admin &admin, list<Reservation> &reservations) {
    int choice = 0;

    while (choice != 9) {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Add Room" << endl;
        cout << "2. View Guest list" << endl;
        cout << "3. View All Reservations" << endl;
        cout << "4. Remove Reservation by ID" << endl;
        cout << "5. Check Available Rooms" << endl;
        cout << "6. Sort Guests By Name" << endl;
        cout << "7. Update Room Price" << endl;
        cout << "8. View Guests Without Reservations" << endl;
        cout << "9. Exit Admin Menu" << endl;
        cout << "Enter your choice (1-9): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            continue;
        }

        if (choice < 1 || choice > 9) {
            cout << "Invalid choice. Please select a number between 1 and 9." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                Admin::addRoom();
                shtrix();
                break;
            }
            case 2:{
                GuestList guestList;
                guestList.printGuests();
                shtrix();
                break;
            }
            case 3:{
                Admin::viewAllReservations(reservations);
                for(Reservation& reservation: reservations){
                    cout << "Guest: " << reservation.getGuest().toString()
                         << ", Check-in: " << reservation.getCheckIn().getDate()
                         << ", Check-out: " << reservation.getCheckOut().getDate()
                         << ", Room: " << reservation.getRoom().getIdRoom() << endl;
                }
                shtrix();
                break;
            }
            case 4: {
//                int idGuest;
//                cout << "Enter the guest ID to remove reservation: ";
//                cin >> idGuest;
//                Admin::saveReservationsToFile(reservations);
//                for(auto it = reservations.begin(); it != reservations.end(); ){
////              it->writeToFile();
//               cout << *it<<endl;
//                }
                Admin::removeReservationById(980, reservations);
                break;
            }
            case 5: {

                Admin::checkAvailableRooms();
                shtrix();
                break;
            }
            case 6: {
                GuestList guestList;
                string name;
                cout << "Enter the name of the Guest: ";
                cin >> name;
                guestList.sortGuestsByName(name);
                shtrix();
                break;
            }
            case 7: {
                int idRoom = getInput<int>("Enter room ID: ");
                auto newPrice = getInput<double>("Enter new price: ");
                updateRoomPrice(idRoom, newPrice);
                shtrix();
                break;
            }
            case 8: {
                Admin::viewGuestsWithoutReservations();
                shtrix();
                break;
            }
            case 9: {
                cout << "Exiting Admin Menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please select a number between 1 and 9." << endl;
        }
    }
}

void Admin::addRoom() {
    cout << "Add room: " << endl;

    unique_ptr<int> id1;
    unique_ptr<double> price;
    unique_ptr<int> occ;

    while (true) {
        try {
            id1 = make_unique<int>(getInput<int>("Enter room ID: "));
            break;
        } catch (const exception &e) {
            cerr << "Invalid room ID! Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (true) {
        try {
            price = make_unique<double>(getInput<double>("Enter price: "));
            break;
        } catch (const exception &e) {
            cerr << "Invalid price! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (true) {
        try {
            occ = make_unique<int>(getInput<int>("Enter current occupancy (max 4): "));

            if (*occ < 0 || *occ > 4) {
                throw invalid_argument("Occupancy must be between 0 and 4.");
            }
            break;
        } catch (const invalid_argument &e) {

        } catch (const exception &e) {
            cerr << "Invalid occupancy! Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    try {
        Room room(*id1, false, *price, *occ);
        room.writeToFile();
        cout << "Room added successfully!" << endl;
    } catch (const exception &e) {
        cerr << "Error while adding room: " << e.what() << endl;
    }
}

bool Admin::ifExist(int idRoom) {
    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    Room room;
    while (fin >> room) {
        if (room.getIdRoom() == idRoom) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void Admin::removeReservationById(int idGuest, list<Reservation>& reservations) {
//    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::trunc);
//    fout.close();
    for (auto it = reservations.begin(); it != reservations.end();) {
        const Guest& guest = it->getGuest();
//        cout << *it;
        if (guest.getIdGuest() == idGuest) {
            it = reservations.erase(it);
            cout << "Reservation for guest with ID " << idGuest << " has been removed." << endl;
        } else {
            ++it;
        }
    }
//    for(auto it = reservations.begin(); it != reservations.end(); ){
//        it->writeToFile();
////        cout << *it;
//    }
}


void Admin::checkAvailableRooms() {
    int occupancy = 0;

    while (true) {
        cout << "Enter the occupancy (number of people, 1 to 4): ";
        cin >> occupancy;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 4." << endl;
            continue;
        }

        if (occupancy < 1 || occupancy > 4) {
            cout << "Invalid occupancy! Please enter a number between 1 and 4." << endl;
        } else {
            break;
        }
    }
    cout << "Checking available rooms for an occupancy of " << occupancy << " people." << endl;

    ifstream fin(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Rooms.txt)");
    if (!fin.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    bool available = false;
    int idRoom;
    bool isOccupied;
    double pricePerNight;
    int currentOccupancy;

    while (fin >> idRoom >> isOccupied >> pricePerNight >> currentOccupancy) {
        if (currentOccupancy == occupancy) {
            cout << "Room " << idRoom << " is available for " << occupancy << " people." << endl;
            available = true;
        }
    }

    fin.close();

    if (!available) {
        cout << "No rooms are available for the specified occupancy." << endl;
    }
}




void Admin::viewAllReservations(const list<Reservation> &reservations) {
    if (reservations.empty()) {
        cout << "There are no reservations at the moment." << endl;
        return;
    }

    cout << "List of all reservations:" << endl;
    for (const auto &reservation: reservations) {
        cout << "Guest: " << reservation.getGuest().toString()
            << ", Check-in: " << reservation.getCheckIn().getDate()
             << ", Check-out: " << reservation.getCheckOut().getDate()
             << ", Room: " << reservation.getRoom().getIdRoom() << endl;
    }
}


