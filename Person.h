#ifndef HOTELMANEGEMENT_PERSON_H
#define HOTELMANEGEMENT_PERSON_H


class Person {
public:
    Person()=default;
    virtual ~Person() = default;

    virtual void writeToFile() =0;
};


#endif //HOTELMANEGEMENT_PERSON_H
