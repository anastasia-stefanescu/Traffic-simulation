
#ifndef Calator_h
#define Calator_h

#include "StrategyPattern.h"
#include "Strazi.h"

class Calator{
private:
    int cnp;
    Transport* modTransport;
public:
    Calator(int cod, Transport* modInitial): cnp(cod), modTransport(modInitial) {
        
    }
    
    void setModTransport(Transport* modNou)
    {
        if(modTransport != NULL)
            delete modTransport;
        modTransport = modNou;
    }
    void deplasare(std::vector<std::shared_ptr<Intersectie>> vi)
    {
        if(modTransport == NULL)
            throw "Selecteaza mod transport";
        modTransport -> transport(vi);
    }
    
    virtual ~Calator() {delete modTransport;}
}

#endif /* Calator_h */
