#pragma once

#ifndef Clock_h
#define Clock_h

#include "Subject.h"

class Clock: public Subject {
    
    int timp;
    
public:
    Clock();
    Clock(int start);
    
    int getTime();
    
    void tick();
};

#endif
