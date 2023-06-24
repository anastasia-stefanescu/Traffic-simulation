#include "Subject.h"

#include "ObiectMiscator.h"
#include "Intersectie.h"

void Subject::Attach(std::shared_ptr<ObiectMiscator> o)
{
    _observers_obiectmiscator.push_back(o);
}

void Subject::Attach(std::shared_ptr<Intersectie> o)
{
    _observers_intersectie.push_back(o);
}

void Subject::Detach(std::shared_ptr<ObiectMiscator> o)
{
    _observers_obiectmiscator.erase(std::remove(_observers_obiectmiscator.begin(), _observers_obiectmiscator.end(), o), _observers_obiectmiscator.end());
}

void Subject::Detach(std::shared_ptr<Intersectie> o)
{
    _observers_intersectie.erase(std::remove(_observers_intersectie.begin(), _observers_intersectie.end(), o), _observers_intersectie.end());
}

void Subject::Notify()
{
    for (const auto& obs : _observers_intersectie)
        obs->Update(this);
    for (const auto& obs : _observers_obiectmiscator)
        obs->Update(this);
}
