#pragma once

#ifndef Subject_h
#define Subject_h

class ObiectMiscator;
class Intersectie;

#include <iostream>
//#include "ObiectMiscator.h"
//#include "Intersectie.h"

class Subject {
private:
    std::vector<std::shared_ptr<ObiectMiscator>> _observers_obiectmiscator;
    std::vector<std::shared_ptr<Intersectie>> _observers_intersectie;
protected:
    Subject();
public:
    virtual ~Subject();
    
    void Attach(std::shared_ptr<ObiectMiscator> o);
    
    void Attach(std::shared_ptr<Intersectie> o);

    void Detach(std::shared_ptr<ObiectMiscator> o);
    
    void Detach(std::shared_ptr<Intersectie> o);

    virtual void Notify();
};

#endif /* Subject_h */

//class Subject {
//public:
//    virtual ~Subject();
//    template<typename T>  void Attach(std::shared_ptr<T> o)
//    {
//        //de facut dynamic cast
//        Object_observers->Append(o)
//    }
//    template<typename T>  void Detach(std::shared_ptr<T> o)
//    {
//        if(auto tip = dynamic_pointer_cast<ObiectMiscator>
//        Object_observers->Remove(o);
//    }
//
//    virtual void Notify()
//    {
//        ListIterator<std::shared_ptr<ObiectMiscator>> i(Object_observers);
//        //construieste un iterator, i, pentru containerul_observers
//        for (i.First(); !i.IsDone(); i.Next()) { i.CurrentItem()->Update(this);}
//
//        ListIterator<std::shared_ptr<Intersectie>> i(Intersection_observers);
//        //construieste un iterator, i, pentru containerul_observers
//        for (i.First(); !i.IsDone(); i.Next()) { i.CurrentItem()->Update(this);}
//    }
//
//
//protected:
//    Subject();
//
//private:
//    List<std::shared_ptr<ObiectMiscator>> Object_observers;
//    List<std::shared_ptr<Intersectie>> Intersection_observers;
//};
//


