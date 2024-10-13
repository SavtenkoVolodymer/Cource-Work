#include "Date.h"
#include "fstream"
// Constructors
Date::~Date() {
    ofstream fout(R"(C:\Users\User\Desktop\CourceWork\HotelManegement\files\Log.txt)", ios_base::app);
    fout << "Year: "<< *year << " Month: " << *month<< " Day: "<< *day<<endl;
    fout.close();
}

Date::Date() : year(std::make_unique<int>(1900)), month(std::make_unique<int>(1)), day(std::make_unique<int>(1)) {}

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

void Date::setCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    tm localTime = *std::localtime(&t);

    *year = localTime.tm_year + 1900;
    *month = localTime.tm_mon + 1;
    *day = localTime.tm_mday;
}

void Date::setYesterdayDay() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    tm localTime = *std::localtime(&t);
    // Decrease the day by one
    *day = --localTime.tm_mday;

    // Check if the day is now less than 1
    if (*day < 1) {
        // Decrease the month by one
        --(*month);

        // If the month is now less than 1, roll back to December of the previous year
        if (*month < 1) {
            --(*year);
            *month = 12; // December
        }

        // Set the day to the last day of the previous month
        if (*month == 1 || *month == 3 || *month == 5 || *month == 7 || *month == 8 || *month == 10 || *month == 12) {
            *day = 31;
        } else if (*month == 4 || *month == 6 || *month == 9 || *month == 11) {
            *day = 30;
        } else if (*month == 2) {
            bool isLeapYear = (*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0);
            *day = isLeapYear ? 29 : 28;
        }
    }
}


void Date::setDate() {
    while (true) {
        std::cout << "Enter date (YYYY-MM-DD): \n";
        std::string input;
        std::getline(std::cin >> std::ws, input);  // Use getline to read the entire line

        std::stringstream ss(input);
        char dateDelimiter;

        ss >> *year >> dateDelimiter >> *month >> dateDelimiter >> *day;

        if (!IsValidDate(*year, *month, *day)) {
            std::cerr << "Invalid date or time entered.\n" << std::endl;
            *year = *month = *day =  0;
        } else {
            //std::cout << "Date and time entered successfully.\n" << std::endl;
            break;
        }
    }
}

std::string Date::getDate() const {
    std::string g_year = std::to_string(*year);
    std::string g_month = (*month < 10)? ( '0' + std::to_string(*month)):std::to_string(*month);
    std::string g_day = (*day < 10)? ( '0' + std::to_string(*day)):std::to_string(*day);
    std::string date = g_year + ' ' + g_month + ' ' + g_day;
    return date;
}

int Date::getYear() const {
    return *year;
}

int Date::getMonth() const {
    return *month;
}

int Date::getDay() const {
    return *day;
}

// Сеттери
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

bool isFuture(const Date &lhs, const Date &rhs) {
    return lhs < rhs;
}

bool isNow(const Date &lhs, const Date &rhs){
    return lhs == rhs;
}

Date Date::getCurrentDate() {
    Date date;
    date.setCurrentDate();
    return date;
}