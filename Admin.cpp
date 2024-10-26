#include "Admin.h"
#include "fstream"
#include "GuestList.h"
#include "RoomList.h"
#include "Reservation.h"

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
                break;
            }
            case 2:{
                GuestList guestList;
                guestList.printGuests();
                break;
            }

            case 3: {
                int idGuest;
                cout << "Enter the ID of the reservation guest you want to delete:  ";
                cin >> idGuest;
                Admin::removeReservationById(idGuest);
                break;
            }
            case 4: {

                Admin::checkAvailableRooms();
                shtrix();
                break;
            }
            case 5: {
                GuestList guestList;
                string name;
                cout << "Enter the name of the Guest: ";
                cin >> name;
                guestList.sortGuestsByName(name);
                shtrix();
                break;
            }
            case 6: {
                int idRoom = getInput<int>("Enter room ID: ");
                auto newPrice = getInput<double>("Enter new price: ");
                updateRoomPrice(idRoom, newPrice);
                shtrix();
                break;
            }
            case 7: {
                Admin::viewGuestsWithoutReservations();
                shtrix();
                break;
            }
            case 8: {
                cout << "Exiting Admin Menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please select a number between 1 and 8." << endl;
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

void Admin::removeReservationById(int idGuest) {
    const string reservationsFilePath = R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)";
    const string tempFilePath = R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\TempReservations.txt)";
    const string departureFilePath = R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\DepartureOfGuests.txt)";

    ifstream inputFile(reservationsFilePath);
    ofstream tempFile(tempFilePath);
    ofstream departureFile(departureFilePath, ios_base::app);  // Відкриваємо файл для дописування

    if (!inputFile.is_open() || !tempFile.is_open() || !departureFile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    bool reservationRemoved = false;
    int guestId, yearGuest, year, month, day;
    string name, surname;
    int roomId, isOccupied;
    double pricePerNight;
    int currentOccupancy;

    // Зчитуємо дані з файлу Reservations.txt і копіюємо в тимчасовий файл, якщо ID не збігається
    while (inputFile >> guestId >> name >> surname >> yearGuest >> year >> month >> day >> roomId >> isOccupied >> pricePerNight >> currentOccupancy) {
        if (guestId == idGuest) {
            // Записуємо видалене резервування в DepartureOfGuests.txt
            departureFile << guestId << " " << name << " " << surname << " " << yearGuest << " "
                          << year << " " << month << " " << day << " "
                          << roomId << " " << isOccupied << " " << pricePerNight << " " << currentOccupancy << endl;
            cout << "Reservation for guest with ID " << idGuest << " has been removed and added to DepartureOfGuests." << endl;
            reservationRemoved = true;
        } else {
            // Зберігаємо резервування в тимчасовому файлі, якщо ID не співпадає
            tempFile << guestId << " " << name << " " << surname << " " << yearGuest << " "
                     << year << " " << month << " " << day << " "
                     << roomId << " " << isOccupied << " " << pricePerNight << " " << currentOccupancy << endl;
        }
    }

    inputFile.close();
    tempFile.close();
    departureFile.close();

    // Замінюємо оригінальний файл Reservations.txt на тимчасовий файл, якщо було видалене резервування
    if (reservationRemoved) {
        if (remove(reservationsFilePath.c_str()) != 0) {
            cerr << "Error deleting original reservations file." << endl;
        } else if (rename(tempFilePath.c_str(), reservationsFilePath.c_str()) != 0) {
            cerr << "Error renaming temporary file to reservations file." << endl;
        }
    } else {
        cout << "No reservations found for guest with ID " << idGuest << "." << endl;
        remove(tempFilePath.c_str());  // Видаляємо тимчасовий файл, якщо видалення не відбулося
    }
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





