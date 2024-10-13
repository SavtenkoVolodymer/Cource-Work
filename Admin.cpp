#include "Admin.h"
#include "fstream"

// Constructors
Admin::Admin() : login(""), password("") {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)");
    fout << "Login: "<< login << " Password: " << password << " Logged in as admin"<<endl;
}

Admin::Admin(string  newLogin, string  newPassword)
        : login(std::move(newLogin)), password(std::move(newPassword)) {}

Admin::Admin(const Admin& admin)
        : login(admin.login), password(admin.password) {}

Admin::Admin(Admin&& admin) noexcept
        : login(std::move(admin.login)), password(std::move(admin.password)) {}

Admin::~Admin() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Login: "<< login << " Password: " << password << endl;
    fout.close();
}

istream& operator>>(istream& is, Admin& admin) {
    is >> admin.login;
    is >> admin.password;
    return is;
}

ostream& operator<<(ostream& os, const Admin& admin) {
    os << "Admin Login: " << admin.login << ", Password: " << admin.password;
    return os;
}

// Operator =
Admin& Admin::operator=(const Admin& admin) {
    if (this != &admin) {
        login = admin.login;
        password = admin.password;
    }
    return *this;
}

Admin& Admin::operator=(Admin&& admin) noexcept {
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

void Admin::setLogin(const string& _login) {
    login = _login;
}

void Admin::setPassword(const string& _password) {
    password = _password;
}
// Operators == , != , >, <
bool Admin::operator==(const Admin& other) const {
    return login == other.login && password == other.password;
}

bool Admin::operator!=(const Admin& other) const {
    return !(*this == other);
}

bool Admin::operator<(const Admin& other) const {
    if (login != other.login) {
        return login < other.login;
    }
    return password < other.password;
}

bool Admin::operator>(const Admin& other) const {
    return other < *this;
}



void Admin::writeToFile() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Admins.txt)", ios_base::app);
    fout << login << "\t" << password << endl;
    fout.close();
}

void Admin::addRoom() {
    unique_ptr<int> choice  (new int {10});
    while (*choice !=0) {
    cout << "Which room would you like to add" << endl;
    cout << "1 - Single room" << endl;
    cout << "2 - Double room" << endl;
    cout << "3 - Triple room" << endl;
    cout << "0 - exit" << endl;

        try {
            choice = make_unique<int>(getInput<int>("Make your choice: "));
            switch (*choice) {
                case 1 : {
                    cout << "Single room: " << endl;
                    unique_ptr <int> id1 = make_unique <int> (getInput<int>("Enter id: " ));
                    unique_ptr <double> price = make_unique <double> (getInput<double>("Enter price: " ));
                    SingleRoom singleRoom (*id1, false, *price,0);
                    singleRoom.addToFile();
                    break;
                }
                case 2 : {
                    cout << "Double room: " << endl;
                    unique_ptr <int> id1 = make_unique <int> (getInput<int>("Enter id: " ));
                    unique_ptr <double> price = make_unique <double> (getInput<double>("Enter price: " ));
                    DoubleRoom doubleRoom (*id1, false, *price,0);
                    doubleRoom.addToFile();
                    break;
                }
                case 3 : {
                    cout << "Triple room: " << endl;
                    unique_ptr <int> id1 = make_unique <int> (getInput<int>("Enter id: " ));
                    unique_ptr <double> price = make_unique <double> (getInput<double>("Enter price: " ));
                    TripleRoom tripleRoom (*id1, false, *price,0);
                    tripleRoom.addToFile();
                    break;
                }
                case 0 : {
                    break;
                }
                default : {
                    throw runtime_error("Wrong choice!!!!");
                }
            }
        }catch (exception &e) {
        cerr << e.what()<<endl;
        }

    }
}

