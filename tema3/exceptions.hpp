#ifndef exceptions_hpp
#define exceptions_hpp

#include <string>
#include <stdexcept>

class Eroare: public std::out_of_range {
public:
    Eroare(const std::string& message) : std::out_of_range(message) {}
};

class OutofRange: public Eroare {
public:
    OutofRange(const std::string& message) :  Eroare (message) {}
};

class NotonStreet: public Eroare {
public:
    NotonStreet(const std::string& message) : Eroare(message) {}
};

#endif /* exceptions_hpp */
