#pragma once

#ifndef Intersectie_h
#define Intersectie_h

class Clock;

#include "Observer.h"
#include <iostream>
#include <memory>
// #include "Clock.h"

class Intersectie: public Observer, public std::enable_shared_from_this<Intersectie> {
private:
    Clock* clock;
    int semafor; // 1 cand e verde, 0 altfel
    int x, y;    //coordonatele - sunt legate de intersectii
    
public:
    Intersectie() {}
    Intersectie(Clock* cl, int sem, int a, int b);
    ~Intersectie();
    
    //TODO: constructori de copiere, op=, op<< !!!!!!!!
    
    int getX();
    int getY();
    int getSemafor();
    
    void schimbaSemafor();
    
    void Update(Subject*) override;
};

#endif /* Intersectie_h */
