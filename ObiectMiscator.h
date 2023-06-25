#pragma once

#ifndef ObiectMiscator_h
#define ObiectMiscator_h

#include "exceptions.hpp"
#include "Intersectie.h"
#include "Strada.h"
#include "Clock.h"
#include "Subject.h"
#include "Observer.h"
class ClockO;
class Subject_obiecte;

class ObiectMiscator : public Observer, public std::enable_shared_from_this<ObiectMiscator> {
protected:
    class ClockO* clock;
    int x, y; //coordonatele curente
    int directie;
    int viteza; // 1 pentru Pieton, 2 pentru Masini, 4 pentru Masini prioritate
    
public:
    static const int sus = 1;
    static const int dreapta = 2;
    static const int jos = 3;
    static const int stanga = 4;
    
    ObiectMiscator(class ClockO* cl);
    
    ObiectMiscator(class ClockO* cl, const std::shared_ptr<Strada> s);
    
    ObiectMiscator(class ClockO* cl, int a, int b, int dir);
    
    virtual ~ObiectMiscator();
    
    virtual ObiectMiscator* clone() const = 0;
    //virtual std::shared_ptr<ObiectMiscator> clone() const = 0;
    
    //cc, op=, etc
    
    void verificaDacaIeseDinTabla() const ;
    
    virtual void Misca();
    
    virtual int poateMergeLaUrmatoareaPozitie() const;
    
    void Update(class Subject_obiecte* s) override;
};

#endif /* ObiectMiscator_h */

