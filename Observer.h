#pragma once

#ifndef observer_h
#define observer_h

class Subject_intersectii;
class Subject_obiecte;
//#include "Subject.h"

class Observer {
    
public:
    virtual ~Observer();
    template <class T> void Update(T* theChangedSubject) {}
    //virtual void Update(Subject* theChangedSubject) = 0; 
protected:
    Observer();
};

#endif /* observer_h*/
