#include "Clock.h"

Clock::Clock(int start): timp(start) {}

int Clock::getTime() {return timp;}

void Clock::tick() {
    timp++;
    Notify();
}
