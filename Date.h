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
public:
    Date();
    Date(int y, int m, int d);
    ~Date();
    friend ofstream& operator<<(ofstream& ofs, const Date& date);
    friend ifstream& operator>>(ifstream& is, Date& date);

    Date& operator=(const Date& date);
    Date& operator=(Date&& date) noexcept;

    string getDate();
    Date(const Date &date);
    Date(Date &&date) noexcept ;

    void setCurrentDate();
    void setYesterdayDay();
    void setDate();

    [[nodiscard]] string getDate() const;

    bool operator <(const Date &rhs) const;
    bool operator ==(const Date &rhs) const;
    bool operator!=(const Date& rhs) const;
    bool operator>(const Date& rhs) const;

    friend bool isFuture(const Date &lhs, const Date &rhs);
    friend bool isNow(const Date &lhs,const Date &rhs);
    static Date getCurrentDate();
};



#endif //DATE_H
