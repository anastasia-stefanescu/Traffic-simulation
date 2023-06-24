#pragma once

#ifndef ObiectMiscator_h
#define ObiectMiscator_h

#include "exceptions.hpp"
#include "Intersectie.h"
#include "Strada.h"
#include "Clock.h"
#include "Subject.h"
#include "Observer.h"

class ObiectMiscator : public Observer, public std::enable_shared_from_this<ObiectMiscator> {
protected:
    Clock* clock;
    int x, y; //coordonatele curente
    int directie;
    int viteza; // 1 pentru Pieton, 2 pentru Masini, 4 pentru Masini prioritate
public:
    static const int sus = 1;
    static const int dreapta = 2;
    static const int jos = 3;
    static const int stanga = 4;
    
    //virtual ObiectMiscator* clone() const = 0;
    //constructor virtual
    
    ObiectMiscator(Clock* cl);
    
    ObiectMiscator(Clock* cl, const std::shared_ptr<Strada> s);
    
    ObiectMiscator(Clock* cl, int a, int b, int dir);
    
    virtual ~ObiectMiscator();
    
    //cc, op=, etc

    void Update(Subject* theChangedSubject) override;// TODO override
    
    void verificaDacaIeseDinTabla() const ;
    
    virtual void Misca();
    
    virtual int poateMergeLaUrmatoareaPozitie() const;
    

};

#endif /* ObiectMiscator_h */

