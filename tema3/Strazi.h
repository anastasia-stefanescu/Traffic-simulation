

#ifndef Strazi_h
#define Strazi_h

//#include <iostream>
#include "exceptions.hpp"
#include "Observer.h"
#include "Clock.h"

class Intersectie: public Observer{
private:
    Clock* clock;
    int semafor; //1 cand e verde pt orizontala, 0 altfel
    int x, y; //coordonatele - sunt legate de intersectii
    
public:
    Intersectie() {}
    Intersectie(Clock* cl, int sem, int a, int b): clock(cl), semafor(sem), x(a), y(b) {
        clock->Attach(this);
    }
    
    //TODO: constructori de copiere, op=, op<< !!!!!!!!
    
    int getX() {return x;}
    int getY() {return y;}
    int getSemafor() {return semafor;}
    
    ~Intersectie() {
        clock->Detach(this);
    };
    
    void schimbaSemafor(){
        semafor = 1-semafor;
    }
    
    void Update() override {
        if(clock->getTime() % 6 == 0) //din 6 in 6 unitati de timp schimbam semaforul
        {
            schimbaSemafor();
        }
    }
};

class Strada{
protected: //sau private?
    int x, y; //coord fixa
    int orientare;
    //std::vector <Intersectie*> shared_ptr
    //TODO: intersectiile pe strazi; de folosit: smart pointers, suprascriere cc si op=.
public:
    //constructor virtual
    
    Strada(const int a, const int b, const int c): x(a), y(b), orientare(c) {
        std::cout << "Am initializat strada " << x << " " << orientare;
        
    }
    
    std::shared_ptr <Strada> citire()
    {
        std::cin >> x >> y>> orientare;
        if(x >= 1 && x<= 29)
        {
            auto s = std::make_shared<Strada>(x, orientare);
            return s;
        }
        throw OutofRange("inserati o strada corect");
    }
    
    int getCoordX() const {return x;};
    int getCoordY() const {return y;};
    int getOrientare() const {return orientare;}
    
    //cc, op=, etc - trebuie suprascrise;
    Strada(const Strada& other) = default; //cc
    Strada& operator=(const Strada& other) = default; //op=
    
    ~Strada() = default;
};


#endif /* Strazi_h */
