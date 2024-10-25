#include "Date.h"
#include "fstream"
// Constructors
Date::~Date() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Destructor from Date"<< endl;
    fout.close();
}

Date::Date() : year(std::make_unique<int>()), month(std::make_unique<int>()), day(std::make_unique<int>()) {}

Date::Date(int y, int m, int d) : year(std::make_unique<int>(y)), month(std::make_unique<int>(m)), day(std::make_unique<int>(d)) {
    if (!IsValidDate(y, m, d)) {
        throw std::invalid_argument("Invalid date");
    }
}

Date::Date(const Date &date) :
        year(std::make_unique<int>(*date.year)), month(std::make_unique<int>(*date.month)), day(std::make_unique<int>(*date.day)) {}

Date::Date(Date &&date) noexcept :
        year(std::move(date.year)), month(std::move(date.month)), day(std::move(date.day)) {}

ofstream& operator<<(ofstream& os, const Date& date) {
    os << *date.year << " " << *date.month << " " << *date.day << endl;
    return os;
}
ifstream& operator>>(ifstream& is, Date& date){
    is >> *date.year >> *date.month >> *date.day;
    return is;
}


Date& Date::operator=(const Date& date) {
    if (this != &date) {
        year = std::make_unique<int>(*date.year);
        month = std::make_unique<int>(*date.month);
        day = std::make_unique<int>(*date.day);
    }
    return *this;
}

Date& Date::operator=(Date&& date) noexcept {
    if (this != &date) {
        year = std::move(date.year);
        month = std::move(date.month);
        day = std::move(date.day);
    }
    return *this;
}
void Date::SetCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    tm localTime = *std::localtime(&t);

    *year = localTime.tm_year + 1900;
    *month = localTime.tm_mon + 1;
    *day = localTime.tm_mday;
}

Date Date::getCurrentDate() {
    Date date;
    date.SetCurrentDate();
    return date;
}

bool Date::IsValidDate(int y, int m, int d) {
    if (y < 1900 || m < 1 || m > 12 || d < 1 || d > 31) {
        return false;
    }
    // Check for months with 30 days
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
        return false;
    }
    // Check for February
    if (m == 2) {
        bool isLeapYear = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if ((isLeapYear && d > 29) || (!isLeapYear && d > 28)) {
            return false;
        }
    }
    return true;
}

bool Date::isLeapYear(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return true;
    }
    return false;
}

int Date::daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

int Date::operator-(const Date& rhs) const {

    auto daysFromStart = [](int year, int month, int day) {
        int days = day;

        for (int m = 1; m < month; ++m) {
            days += Date::daysInMonth(m, year);
        }

        for (int y = 0; y < year; ++y) {
            days += isLeapYear(y) ? 366 : 365;
        }

        return days;
    };

    int days1 = daysFromStart(*year, *month, *day);
    int days2 = daysFromStart(*rhs.year, *rhs.month, *rhs.day);

    return abs(days1 - days2);
}

void Date::setDate() {
    while (true) {
//        cout << " Enter date (YYYY-MM-DD): \n";
        string input;
        getline(cin >> ws, input);

        stringstream ss(input);
        char dateDelimiter;

        ss >> *year >> dateDelimiter >> *month >> dateDelimiter >> *day;

        if (!IsValidDate(*year, *month, *day)) {
            std::cerr << "Invalid date entered. Try again.\n";
        } else {
            break;
        }
    }
}


std::string Date::getDate() const {
    std::string g_year = std::to_string(*year);
    std::string g_month = (*month < 10)? ( '0' + std::to_string(*month)):std::to_string(*month);
    std::string g_day = (*day < 10)? ( '0' + std::to_string(*day)):std::to_string(*day);
    std::string date = g_year + ' ' + g_month + ' ' + g_day + ' ';
    return date;
}

// Getters
int Date::getYear() const {
    return *year;
}

int Date::getMonth() const {
    return *month;
}

int Date::getDay() const {
    return *day;
}

//Setters
void Date::setYear(int newYear) {
    year = make_unique<int>(newYear);
}

void Date::setMonth(int newMonth) {
    month = make_unique<int>(newMonth);
}

void Date::setDay(int newDay) {
    day = make_unique<int>(newDay);
}
// Operators !=, == , > , <
bool Date::operator!=(const Date& rhs) const {
    return !(*this == rhs);
}

bool Date::operator==(const Date &rhs) const {
    if (*year == *rhs.year && *month == *rhs.month && *day == *rhs.day)
        return true;

    return false;

}

bool Date::operator>(const Date& rhs) const {
    return rhs < *this;
}

bool Date::operator<(const Date &rhs) const{
    if (*year < *rhs.year)
        return true;
    if(*year > *rhs.year)
        return false;

    if (*month < *rhs.month)
        return true;
    if(*month > *rhs.month)
        return false;

    if (*day < *rhs.day)
        return true;
    if(*year > *rhs.day)
        return false;

    return false;
}



