
#ifndef Run_h
#define Run_h

#include <iostream>
#include "exceptions.hpp"
#include "Strazi.h"
#include "Clock.h"
#include "ObiecteMiscatoare.h"
#include "StrategyPattern.h"

class Run{
protected:
    Clock* clock;
    
    const int stanga = 1;
    const int dreapta = 2;
    const int jos = 3;
    const int sus = 4;
    int nrStrazi;
    int x, orientare;
    std::vector <std::shared_ptr<Strada>> v_strazi_orizontale;
    std::vector <std::shared_ptr<Strada>> v_strazi_verticale;
    std::vector <std::shared_ptr<Strada>> strazi;
    std::vector <std::shared_ptr<Intersectie>> v_intersectii;
    std::vector <std::shared_ptr<ObiectMiscator>> v_masini;
    
    std::vector <std::shared_ptr<ObiectMiscator>> v_pietoni;
public:
    friend int poateMergeLaUrmatoareaPozitie(Run);
    
    std::vector <std::shared_ptr<Intersectie>> getVectInters() {return v_intersectii;}
    
    Run() {
        //creem clock-ul
        clock = new Clock(0);
        
        std::cin >> nrStrazi;
        //strada trebuie sa fie intre 1 si 29.
        for (int i = 1; i<= nrStrazi; i++)
        {
            std::shared_ptr <Strada> s;
            do{
                try{
                    s = s->citire();
                    break;
                }catch (OutofRange& err){
                    std::cout << "range gresit : " << err.what() << '\n';
                }
            }while(true);
            
            adauga_intersectii(s);
            
            //adaugam o masina la inceputul acestei strazi;
            int tip = rand() % 2 + 1;
            std::shared_ptr<ObiectMiscator> baseMasina;
            if(tip == 1)//alegem random tipul de masina care se spawneaza
                baseMasina = std::make_shared<Masina>(s);
            else
                baseMasina = std::make_shared<Masina_prioritara>(s);
            v_masini.push_back(baseMasina);
        }
        
        //adaugam pietoni
        for (int i = 1; i<= 10; i++)
        {
            std::shared_ptr <ObiectMiscator> basePieton = std::make_shared<Pieton>();
            v_pietoni.push_back(basePieton);
        }
        
        //adaugam calatori
        std::shared_ptr<ObiectMiscator> m1 = std::make_shared<Masina>(v_strazi_verticale[1]);
        std::shared_ptr<ObiectMiscator> m2 = std::make_shared<Masina_prioritara>(v_strazi_orizontale[1]);
        Calator c1(19836, m1);
        Calator c2(236847, m2);
        c1.deplasare(v_intersectii);
        c2.deplasare(v_intersectii);
        
        play();
        
    }
    
    void play(){
        for (int i = 1; i<= 10; i++)
            clock.tick();
    }
  
    
    void adauga_intersectii(const std::shared_ptr<Strada>& s)
    {
        if(s->getOrientare() == 1)
        {
            v_strazi_orizontale.push_back(s);
            int NrVerticale = (int)v_strazi_verticale.size();
            for(int i = 0; i<NrVerticale; i++)
            {
                auto inters = std::make_shared<Intersectie>(clock, 1, s->getCoordX(), v_strazi_verticale[i]->getCoordY());
                v_intersectii.push_back(inters);
            }
        }
        else
        {
            v_strazi_verticale.push_back(s);
            int NrOrizontale = (int)v_strazi_orizontale.size();
            for(int i = 0; i<NrOrizontale; i++)
            {
                auto inters = std::make_shared<Intersectie>(clock, 1, s->getCoordY(), v_strazi_orizontale[i]->getCoordX());
                v_intersectii.push_back(inters);
            }
        }
    }
};

#endif /* Run_h */
