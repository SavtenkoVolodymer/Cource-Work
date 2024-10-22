#include "Admin.h"
#include "fstream"
#include "GuestList.h"
#include "RoomList.h"

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
    cout << "------------------------------------------------";
}



void Admin::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Admins.txt)", ios_base::app);
    fout << login << "\t" << password << endl;
    fout.close();
}

void Admin::saveReservationsToFile(const list<Reservation>& reservations) {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Reservations.txt)", ios_base::trunc);

    if (!fout.is_open()) {
        cerr << "Error opening file for writing reservations!" << endl;
        return;
    }

    for (const auto& reservation : reservations) {
        fout << reservation.getGuest()->toString() << "\t"
             << reservation.getCheckIn().getDate() << "\t"
             << reservation.getCheckOut().getDate() << "\t"
             << reservation.getRoom().getIdRoom() << "\n";
    }

    fout.close();
    cout << "Reservations saved to file successfully." << endl;
}


void Admin::registerAdmin() {
    string login, password;

    cout << "\nRegistering Admin:" << endl;
    cout << "Enter login: ";
    cin >> login;
    cout << "Enter password: ";
    cin >> password;

    for (char c : password) {
        if (!isdigit(c)) {
            throw invalid_argument("Invalid password! Admin password must be a numeric string.");
        }
    }

    if (password != "777") {
        throw invalid_argument("Invalid password! Admin password must be '777'.");
    }
    Admin admin(login, password);
    cout << "Admin successfully registered!" << endl;
    cout << "Admin details: " << admin << endl;
    Admin admin1;
    Admin::shtrix();
    admin.writeToFile();
}



void Admin::adminMenu(Admin &admin, list<Reservation> &reservations) {
    int choice = 0;
    while (choice != 7) {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Add Room" << endl;
        cout << "2. View Guest list" << endl;
        cout << "3. View All Reservations" << endl;
        cout << "4. Remove Reservation by ID" << endl;
        cout << "5. Check Available Rooms" <<endl;
        cout << "6. Sort Guests By Name"<< endl;
        cout << "7. Exit Admin Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

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
            case 3:{
                Admin::viewAllReservations(reservations);
                for(Reservation& reservation:reservations){
                    cout << "Guest: " << reservation.getGuest()->toString()
                         << ", Check-in: " << reservation.getCheckIn().getDate()
                         << ", Check-out: " << reservation.getCheckOut().getDate()
                         << ", Room: " << reservation.getRoom().getIdRoom() << endl;
                }
                break;
                }
            case 4: {
                int idGuest;
                cout << "Enter the guest ID to remove reservation: ";
                cin >> idGuest;
                Admin::removeReservationById(idGuest, reservations);
//                Admin::saveReservationsToFile(reservations);
                //refresh reservation записувати весь список резервейшн txt заново(list<Reservation>reservations)
                break;
            }
            case 5:{
                Date checkIn, checkOut;
                cout << "Enter the start date of the period:"<< endl;
                checkIn.setDate();
                cout << "Enter the period end date: "<< endl;
                checkOut.setDate();
                Admin::checkAvailableRooms(Date(), Date(),reservations);
                break;
            }
            case 6:{
                GuestList guestList;
                guestList.sortGuestsByName("Volodymyr");
                break;
            }
            case 7: {
                cout << "Exiting Admin Menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please select 1, 2, 3, 4, 5 ,6 or 7." << endl;
        }
    }
}


void Admin::addRoom() {
    unique_ptr<int> choice(new int{10});
    cout << "Add room" << endl;
    try {
        cout << "Make your choice: " << endl;
        unique_ptr<int> id1 = make_unique<int>(getInput<int>("Enter id: "));
        unique_ptr<double> price = make_unique<double>(getInput<double>("Enter price: "));
        unique_ptr<int> occ = make_unique<int>(getInput<int>("Enter current Occupancy: "));
        Room room(*id1, false, *price, *occ);
        room.writeToFile();

    } catch (exception &e) {
        cerr << e.what() << endl;
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

void Admin::removeReservationById(int idGuest, list<Reservation> &reservations) {
    for (auto it = reservations.begin(); it != reservations.end();) {

        auto guestPtr = it->getGuest();

        if (guestPtr && guestPtr->getIdGuest() == idGuest) {
            it = reservations.erase(it);
            cout << "Reservation for guest with ID " << idGuest << " has been removed." << endl;
        } else {
            ++it;
        }
    }
}





void Admin::checkAvailableRooms(const Date &checkIn, const Date &checkOut, const list<Reservation> &reservations) {
    cout << "Checking available rooms for the period: " << checkIn.getDate() << " to " << checkOut.getDate() << endl;

    bool available = false;

    for (const auto &res: reservations) {
        if (res.getCheckOut() < checkIn || res.getCheckIn() > checkOut) {
            cout << "Room " << res.getRoom().getIdRoom() << " is available for the specified period." << endl;
            available = true;
        }
    }
    if (!available) {
        cout << "No rooms are available for the specified period." << endl;
    }
}

void Admin::viewAllReservations(const list<Reservation> &reservations) {
    if (reservations.empty()) {
        cout << "There are no reservations at the moment." << endl;
        return;
    }

    cout << "List of all reservations:" << endl;
    for (const auto &reservation: reservations) {
        cout << "Guest: " << reservation.getGuest()->toString()
            << ", Check-in: " << reservation.getCheckIn().getDate()
             << ", Check-out: " << reservation.getCheckOut().getDate()
             << ", Room: " << reservation.getRoom().getIdRoom() << endl;
    }
}
