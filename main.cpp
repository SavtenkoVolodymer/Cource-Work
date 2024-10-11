#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Date.h"
#include "Reservation.h"

int main() {\
Date date(2009,2,3);
    Reservation res("Vova",date, date,1);
    res.writeToFile();
    return 0;
}
