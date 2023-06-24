#pragma once

#ifndef Calator_h
#define Calator_h

#include "StrategyPattern.h"
#include "Intersectie.h"
#include <iostream>

class Calator {
private:
    int cnp;
    std::shared_ptr<Interfata_Transport> modTransport;
public:
    Calator(int cod, std::shared_ptr<Interfata_Transport> modInitial);
    
    void setModTransport(std::shared_ptr<Interfata_Transport> modNou);
    
    void deplasare();
    
    virtual ~Calator();
};

#endif /* Calator_h */
