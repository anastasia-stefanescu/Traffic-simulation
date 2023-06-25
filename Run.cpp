#include "Run.h"

#include "Strada.h"
#include "Pieton.h"
#include "Masina.h"
#include "Masina_prioritara.h"
#include "Calator.h"
#include "exceptions.hpp"

Run::Run() {
    std::vector <std::shared_ptr<Strada>> v_strazi_orizontale;
    std::vector <std::shared_ptr<Strada>> v_strazi_verticale;
    std::vector <std::shared_ptr<Strada>> strazi;
    int nrStrazi;
    
    //adaugam un clock
    clock_i = new class ClockI(0);
    clock_o = new class ClockO(0);
    
    // adaugam strazile
    std::cin >> nrStrazi;

    for (int i = 1; i<= nrStrazi; i++)
    {
        std::shared_ptr <Strada> s;
        do{
            try{
                s = s->citire();
                break;
            } catch (OutofRange& err){
                std::cout << "range gresit la strada : " << err.what() << '\n';
            }
        } while(true);
        
        // adaugam intersectii
        adaugaIntersectii(v_strazi_orizontale, v_strazi_verticale, s);
        
        // adaugam o masina la inceputul acestei strazi;
        int tip = rand() % 2 + 1;
        std::shared_ptr<ObiectMiscator> baseMasina;
        if (tip == 1)//alegem random tipul de masina care se spawneaza
            baseMasina = std::make_shared<Masina>(clock, s);
        else
            baseMasina = std::make_shared<Masina_prioritara>(clock, s);
        v_masini.push_back(baseMasina);
    }
    
    //adaugam pietoni
    for (int i = 1; i <= 10; i++)
    {
        std::shared_ptr <ObiectMiscator> basePieton = std::make_shared<Pieton>(clock);
        v_pietoni.push_back(basePieton);
    }
    
    //adaugam calatori
    std::shared_ptr<Interfata_Transport> m1 = std::make_shared<Masina>(v_strazi_verticale[1]);
    std::shared_ptr<Interfata_Transport> m2 = std::make_shared<Masina_prioritara>(v_strazi_orizontale[1]);
    Calator c1(19836, m1);
    Calator c2(236847, m2);
    c1.deplasare();
    c2.deplasare();
}

void Run::adaugaIntersectii(std::vector <std::shared_ptr<Strada>> v_strazi_orizontale,
                            std::vector <std::shared_ptr<Strada>> v_strazi_verticale, std::shared_ptr <Strada> s) {
    if (s->getOrientare() == 1) // strada orizontala
    {
        v_strazi_orizontale.push_back(s);
        int NrVerticale = (int)v_strazi_verticale.size();
        for(int i = 0; i<NrVerticale; i++)
        {
            auto intersectie = std::make_shared<Intersectie>(clock, 1, s->getCoordX(), v_strazi_verticale[i]->getCoordY());
            v_intersectii.push_back(intersectie);
        }
    }
    else
    {
        v_strazi_verticale.push_back(s);
        int NrOrizontale = (int)v_strazi_orizontale.size();
        for(int i = 0; i<NrOrizontale; i++)
        {
            auto intersectie = std::make_shared<Intersectie>(clock, 1, s->getCoordY(), v_strazi_orizontale[i]->getCoordX());
            v_intersectii.push_back(intersectie);
        }
    }
}

void Run::play(){
    
    for (int i = 1; i<= 10; i++)
    {
        clock_i->tick();
        clock_o->tick();
    }
}
