#ifndef observer_h
#define observer_h

#include "Subject.h"

class Observer {
    
public:
    virtual ~ Observer();
    virtual void Update(Subject* theChangedSubject) = 0;
protected:
    Observer();
};

#endif /* observer_h*/
