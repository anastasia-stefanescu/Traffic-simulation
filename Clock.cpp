#include "Clock.h"
template <class U> Clock<U>::Clock() : Subject<U>(U()) {}
template <class U> Clock<U>::Clock(int start): timp(start) {}

template <class U> int Clock<U>::getTime() {return timp;}

template <class U> void Clock<U>::tick() {
    timp++;
    Subject<U>::Notify();
}
