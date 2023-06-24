#ifndef Run_h
#define Run_h

class Intersectie;
class ObiectMiscator;
class Strada;

#include <iostream>
#include "Clock.h"

class Run{
    
    static Clock* clock;
    
    const int stanga = 1;
    const int dreapta = 2;
    const int jos = 3;
    const int sus = 4;
    
    static std::vector <std::shared_ptr<Intersectie>> v_intersectii;
    std::vector <std::shared_ptr<ObiectMiscator>> v_masini;
    std::vector <std::shared_ptr<ObiectMiscator>> v_pietoni;
    std::vector <std::shared_ptr<ObiectMiscator>> v_calatori;
    
public:
    
    Run();
    
    void play();
    
    static void adaugaIntersectii(std::vector <std::shared_ptr<Strada>> v_strazi_orizontale,
                                  std::vector <std::shared_ptr<Strada>> v_strazi_verticale, std::shared_ptr <Strada> s);
    
    static std::vector <std::shared_ptr<Intersectie>> getVectIntersection() {return v_intersectii;}
};

#endif /* Run_h */
