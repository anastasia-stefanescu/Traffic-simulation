#include "Intersectie.h"
#include "Clock.h"

Intersectie::Intersectie(class ClockI*
                         cl, int sem, int a, int b): clock(cl), semafor(sem), x(a), y(b) {
    clock->Attach(shared_from_this());
}

int Intersectie::getX() {return x;}
int Intersectie::getY() {return y;}
int Intersectie::getSemafor() {return semafor;}

Intersectie::~Intersectie() {
    clock->Detach(shared_from_this());
};

void Intersectie::schimbaSemafor(){
    semafor = 1-semafor;
}

    void Intersectie::Update(Subject_intersectii* s) {
    if (clock == s && clock->getTime() % 6 == 0) //din 6 in 6 unitati de timp schimbam semaforul
    {
        schimbaSemafor();
    }
}
