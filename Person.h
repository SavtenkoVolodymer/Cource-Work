#ifndef HOTELMANEGEMENT_PERSON_H
#define HOTELMANEGEMENT_PERSON_H


class Person {
public:
    virtual ~Person() = default;

    virtual void writeToFile() =0;

    virtual void addReservation() const =0;

};


#endif //HOTELMANEGEMENT_PERSON_H
