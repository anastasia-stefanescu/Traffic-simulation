#pragma once

#ifndef Clock_h
#define Clock_h

#include "Subject.h"

template <class U> class Clock: public Subject<U>{
    int timp;
    
public:
    Clock();
    Clock(int start);
    
    int getTime();
    
    void tick();
};

Clock<ObiectMiscator> ClockO;
Clock<Intersectie> ClockI;

//class Clock_intersectii: public Subject_intersectii {
//
//    int timp;
//
//public:
//    Clock();
//    Clock(int start);
//
//    int getTime();
//
//    void tick();
//};
//
//class Clock_intersectii: public Subject_obiecte {
//
//    int timp;
//
//public:
//    Clock_intersectii();
//    Clock(int start);
//
//    int getTime();
//
//    void tick();
//};

#endif
