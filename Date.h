#ifndef DATE_H
#define DATE_H
#include<chrono>
#include<memory>
#include<iostream>
#include<sstream>
using namespace std;

class Date {
private:
    unique_ptr<int> year;
    unique_ptr<int> month;
    unique_ptr<int> day;
    static bool IsValidDate(int y, int m, int d);

    static int daysInMonth(int month, int year);
    static bool isLeapYear(int year);
public:
    Date();
    Date(int y, int m, int d);
    ~Date();
    friend ofstream& operator<<(ofstream& ofs, const Date& date);
    friend ifstream& operator>>(ifstream& is, Date& date);

    Date& operator=(const Date& date);
    Date& operator=(Date&& date) noexcept;

    Date(const Date &date);
    Date(Date &&date) noexcept ;
    static Date getCurrentDate();
    void SetCurrentDate();

    [[nodiscard]] int getYear() const;
    [[nodiscard]] int getMonth() const;
    [[nodiscard]] int getDay() const;


    void setYear(int newYear);
    void setMonth(int newMonth);
    void setDay(int newDay);
    void setDate();

    [[nodiscard]] string getDate() const;

    bool operator <(const Date &rhs) const;
    bool operator ==(const Date &rhs) const;
    bool operator!=(const Date& rhs) const;
    bool operator>(const Date& rhs) const;

    int operator-(const Date& rhs) const;

};



#endif //DATE_H
