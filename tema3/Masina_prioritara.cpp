#include "Masina_prioritara.h"


Masina_prioritara::Masina_prioritara(Clock* clock): ObiectMiscator(clock) { viteza = 4; };

Masina_prioritara::Masina_prioritara(Clock* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) { viteza = 4; }

//std::shared_ptr<ObiectMiscator>
//    Masina* clone() const override {
//        return new Masina(*this);
//    }

//    ObiectMiscator* clone() const override {
//        return new Masina(*this);
//    }

Masina_prioritara::Masina_prioritara(Clock* clock, const std::shared_ptr<Strada> s) : ObiectMiscator(clock, s)
{ viteza = 4; }

void Masina_prioritara::Misca()
{
    switch(directie)
    {
        case sus:
            x -= viteza;
            break;
        case dreapta:
            y+= viteza;
            break;
        case jos:
            x+= viteza;
            break;
        case stanga:
            y-= viteza;
            break;
    }
    verificaDacaIeseDinTabla();
}

void Masina_prioritara::Update(Subject* s) {
    if(clock == s){
        Masina_prioritara::Misca();
    }
}

void Masina_prioritara::transport() { Masina_prioritara::Misca(); }
