#pragma once

#ifndef Pieton_h
#define Pieton_h

#include "ObiectMiscator.h"
#include "Intersectie.h"
#include "Clock.h"

class Pieton: public ObiectMiscator{
    
protected:
    Pieton(const Pieton& other) = default; //cc
    Pieton& operator=(const Pieton& other) = default; //op=
    

    
public:
    Pieton(Clock* cl);
    Pieton(Clock* cl, int a, int b, int dir);
    
    int poateMergeLaUrmatoareaPozitie() const override;
    
    ObiectMiscator* clone() const override { return new Pieton(*this); }
    //std::shared_ptr<ObiectMiscator> clone() const override { return std::dynamic_pointer_cast<Pieton>(ObiectMiscator::shared_from_this()); }
};

#endif /* Pieton_h */
