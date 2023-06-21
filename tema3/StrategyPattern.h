#ifndef Strategy_h
#define Strategy_h

#include "Strazi.h"

class Interfata_Transport{
public:
    virtual void transport(std::vector<std::shared_ptr<Intersectie>> vi) const= 0;
};


#endif /* Strategy_h */
