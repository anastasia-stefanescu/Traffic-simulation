

#ifndef Subject_h
#define Subject_h

#include "ObiecteMiscatoare.h"
#include "Strazi.h"

template <typename T> class Subject {
private:
    List<std::shared_ptr<T>> _observers;
protected:
    Subject();
public:
    virtual ~Subject();
    void Attach(std::shared_ptr<T> o)
    {
        _observers->Append(o)
    }
    void Detach(std::shared_ptr<T> o)
    {
        _observers->Remove(o);
    }
    virtual void Notify()
    {
        ListIterator<std::shared_ptr<T>> i(_observers);
        //construieste un iterator, i, pentru containerul_observers
        for (i.First(); !i.IsDone(); i.Next()) { i.CurrentItem()->Update(this);}
    }

};

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

#endif /* Subject_h */
