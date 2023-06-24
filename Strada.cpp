#include <iostream>
#include "exceptions.hpp"
#include "Strada.h"


Strada::Strada(const int a, const int b, const int c): x(a), y(b), orientare(c) {
    std::cout << "Am initializat strada " << x << " " << y << " " << orientare;
    
}

std::shared_ptr <Strada> Strada::citire()
{
    std::cin >> x >> y >> orientare;
    //coordonatele trebuie sa fie intre 1 si 29
    if((x >= 1 && x<= 29) && (y >= 1 && y <= 29))
    {
        auto s = std::make_shared<Strada>(x, y, orientare);
        return s;
    }
    throw OutofRange("inserati o strada corecta (coord intre 1 si 29)");
}

int Strada::getCoordX() const {return x;};
int Strada::getCoordY() const {return y;};
int Strada::getOrientare() const {return orientare;}

//Strada::Strada(const Strada& other) = default; //cc
//Strada::Strada& operator=(const Strada& other) = default; //op=

Strada::~Strada() {};
