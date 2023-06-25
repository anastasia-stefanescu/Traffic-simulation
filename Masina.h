#pragma once

#ifndef Masina_h
#define Masina_h

#include <memory>
#include "ObiectMiscator.h"
#include "Clock.h"
#include "Strada.h"
#include "StrategyPattern.h"

class Masina: public ObiectMiscator, public Interfata_Transport {
    
protected:
    Masina(const Masina& other) = default; //cc
    Masina& operator=(const Masina& other) = default; //op=
    

    
public:
    Masina(Clock* cl, const std::shared_ptr<Strada> s);
    Masina(Clock* cl, int a, int b, int dir);
    
    void transport();
    
    // std::shared_ptr<ObiectMiscator> clone() const override { return std::dynamic_pointer_cast<Masina>(ObiectMiscator::shared_from_this()); }
};

#endif /* Masina_h */
