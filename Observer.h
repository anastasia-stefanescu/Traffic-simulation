#pragma once

#ifndef observer_h
#define observer_h

#include "Subject.h"
class Subject_intersectii;
class Subject_obiecte;

class Observer {
    
public:
    virtual ~Observer();
    virtual void Update(class Subject_intersectii* changedSubject){}
    virtual void Update(class Subject_obiecte* changedSubject){}
protected:
    Observer();
};

#endif /* observer_h*/
