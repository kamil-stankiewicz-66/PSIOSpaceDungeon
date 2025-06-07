#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <iostream>

class ISerializable {

public:
    virtual  ~ISerializable() = default;

    // Funkcja do zapisu obiektu do strumienia
    virtual void serialize(std::ostream& os)  const = 0;


    // Funkcja do odczytu obiektu ze strumienia
    virtual void deserialize(std::istream& is) = 0;
};

#endif // ISERIALIZABLE_H
