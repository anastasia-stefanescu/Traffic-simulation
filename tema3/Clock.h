

#ifndef Header_h
#define Header_h

#include "Subject.h"

class Clock: public Subject<Intersectie>, public Subject<ObiectMiscator>{
    
    int timp;
public:
    Clock();
    Clock(int start): timp(start) {}
    int getTime() {return timp;}
    
    void tick() {
        timp++;
        Notify();
    }
};

#endif
