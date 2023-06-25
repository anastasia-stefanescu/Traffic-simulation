#include "Subject.h"

#include "ObiectMiscator.h"
#include "Intersectie.h"

template <class T> void Subject<T>::Attach(std::shared_ptr<T> o)
{
    _observers.push_back(o);
}

template <class T> void Subject<T>::Detach(std::shared_ptr<T> o)
{
    _observers.erase(std::remove(_observers.begin(), _observers.end(), o), _observers.end());
}

template <class T> void Subject<T>::Notify()
{
    for (const auto& obs : _observers)
        obs->Update(this);
}
