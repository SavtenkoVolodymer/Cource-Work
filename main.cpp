#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Date.h"
#include "Reservation.h"
#include "Guest.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "TripleRoom.h"
#include "GuestList.h"

int main() {
//    Admin admin ("Katya","777");
//    Admin::addRoom();

    string name = "Vova";
    string surname = "Savtenko";
    Guest guest(name,2,2000,surname);
//    string name1 = "Vova";
//    string surname1 = "Savtenko";
//    Guest guest1(name,2,2000,surname);
//    string name2 = "Vova";
//    string surname2 = "Savtenko";
//    Guest guest2(name,2,2000,surname);
//    string name3 = "Vova";
//    string surname3 = "Savtenko";
//    Guest guest3(name,2,2000,surname);
//    string name4 = "Vova";
//    string surname4 = "Savtenko";
//    Guest guest4(name,2,2000,surname);
//
////    cout << Guest::ifExist(15);
//
//    guest.writeToFile();
//    guest1.writeToFile();
//    guest2.writeToFile();
//    guest3.writeToFile();
//    guest4.writeToFile();
//GuestList guestList ;
//    guestList.printGuests();
    Date date (2021, 01,12);
//    string name = "Vlad";

//    Reservation reservation1 (name,  date , date , 1);
//
//
//    cout<< reservation1.getGuest()<<endl;
//    cout << reservation1.getCheckIn().getDate()<< endl;
//    cout << reservation1.getCheckOut().getDate()<< endl;
//    cout << reservation1.getRoom();

    Reservation reservation (name,date , date , 1);
    cout<< reservation << endl;
    cout << reservation.getPriceFromFile();
    return 0;
}
