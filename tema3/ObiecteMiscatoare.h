
#ifndef ObiecteMiscatoare_h
#define ObiecteMiscatoare_h

//#include <iostream>
#include "exceptions.hpp"
#include "Strazi.h"
#include "Clock.h"
#include "Observer.h"

class ObiectMiscator : public Observer, public Interfata_Transport{
protected:
    Clock* clock;
    int x, y; //coordonatele curente
    int directie;
    int viteza; // TODO - 1 pentru Pieton, 2 pentru Masini, 4 pentru pompieri
public:
    static const int sus = 1;
    static const int dreapta = 2;
    static const int jos = 3;
    static const int stanga = 4;
    //   virtual ObiectMiscator* clone() const = 0;
    //constructor virtual
    ObiectMiscator() {}
    ObiectMiscator(Clock* cl, int a, int b, int dir): clock(cl), x(a), y(b), directie(dir) {
        clock->Attach(this);
    }
    virtual ~ObiectMiscator(){
        clock->Detach(this);
    }
    //cc, op=, etc
    virtual void Creare() const = 0;
    
    void transport(std::vector<std::shared_ptr <Intersectie>> vi) override { Misca(vi); }

    void Update() override {
       Misca(
    }
    
    virtual void Misca(std::vector<std::shared_ptr <Intersectie>> vi){
        
        int cePoateFace = poateMergeLaUrmatoareaPozitie(vi);
        if(cePoateFace != 0)
        {
            switch(directie)
            {
                case sus:
                    x--;
                    break;
                case dreapta:
                    y++;
                    break;
                case jos:
                    x++;
                    break;
                case stanga:
                    y--;
                    break;
            }
            if(cePoateFace == 2)
            {
                int dir = rand()%4 + 1;
                switch(dir)
                {
                    case 1:
                        x--;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x++;
                        break;
                    case 4:
                        y--;
                        break;
                }
            }
        }
    }
    int poateMergeLaUrmatoareaPozitie(std::vector<std::shared_ptr <Intersectie>> vi){
        int next_x = x, next_y = y;
        Intersectie inters;
        
        switch(directie)
        {
            case sus:
                next_x--;
                break;
            case dreapta:
                next_y++;
                break;
            case jos:
                next_x++;
                break;
            case stanga:
                next_y--;
                break;
        }
        
        int nrInters = (int)vi.size();
        
        for(int i = 0; i<nrInters; i++) //este in vreo intersectie
            if(next_x == vi[i]->getX() && next_y == vi[i]->getY())
            {
                if(vi[i]->getSemafor() == 1)
                {
                    if(directie == stanga || directie == dreapta)
                        return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                    else
                        return 1; //trebuie sa mai astepte
                }
                else
                {
                    if(directie == sus || directie == jos)
                        return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                    else
                        return 0; //trebuie sa mai astepte
                }
            }
        return 1; //nu e intersectie, deci poate sa mearga in directia obisnuita
        
    }
    void verifDacaIeseDinTabla(){
        if (x> 30 || x < 1 || y > 30 || y < 1)
            throw OutofRange;
    }
    
    
};

// ----------------------------------------------
//masinile prioritare nu stau la semafor; de aceea, pot aparea coliziuni
class Masina_prioritara: public ObiectMiscator{
protected:
    Masina_prioritara(const Masina_prioritara& other) = default; //cc
    Masina_prioritara& operator=(const Masina_prioritara& other) = default; //op=
public:
    Masina_prioritara(): ObiectMiscator() {}
    Masina_prioritara(){
        
    }
    Masina_prioritara(Clock* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) {}
    
    //std::shared_ptr<ObiectMiscator>
    //    Masina* clone() const override {
    //        return new Masina(*this);
    //    }
    
    //    ObiectMiscator* clone() const override {
    //        return new Masina(*this);
    //    }
    
    Masina_prioritara(const std::shared_ptr<Strada> s)
    { //strada poate fi si nullptr
        
        if(s->getOrientare() == 1)
        {
            auto b = std::make_shared<Masina_prioritara>(s->getCoordX(), 1, dreapta);
            return b;
        }
        else
        {
            auto b = std::make_shared<Masina_prioritara>(1, s->getCoordY(), jos);
            return b;
        }
    }
    
    int poateMergeLaUrmatoareaPozitie(std::vector<std::shared_ptr <ObiectMiscator>> vm) override {
        int next_x = x, next_y = y; //ce facem apoi cu next_x, next_y?
        
        switch(directie)
        {
            case sus:
                next_x--;
                break;
            case dreapta:
                next_y++;
                break;
            case jos:
                next_x++;
                break;
            case stanga:
                next_y--;
                break;
        }
        
        for(const auto& masina : )
            if(next_x == inters->getX() && next_y == inters->getY())
            {
                if(inters->getSemafor() == 1) //semaforul e
                {
                    if(directie == stanga || directie == dreapta)
                        return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                    else
                        return 1; //trebuie sa mai astepte
                }
                else
                {
                    if(directie == sus || directie == jos)
                        return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                    else
                        return 0; //trebuie sa mai astepte
                }
            }
        return 1; //nu e intersectie, deci poate sa mearga in directia obisnuita
        
    }
    
    void Misca(int cePoateFace) override
    {
        if(cePoateFace != 0)
        {
            switch(directie)
            {
                case sus:
                    x--;
                    break;
                case dreapta:
                    y++;
                    break;
                case jos:
                    x++;
                    break;
                case stanga:
                    y--;
                    break;
            }
            if(cePoateFace == 2)
            {
                int dir = rand()%4 + 1;
                switch(dir)
                {
                    case 1:
                        x--;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x++;
                        break;
                    case 4:
                        y--;
                        break;
                }
            }
        }
    }
    
    void Update(Clock* cl) override {
        if(cl == clock){
            int cePoateFace = poateMergeLaUrmatoareaPozitie(std::vector<std::shared_ptr <Intersectie>> vi)
            Misca(cePoateFace);
        }
    }
};


class Masina: public ObiectMiscator{
protected:
    Masina(const Masina& other) = default; //cc
    Masina& operator=(const Masina& other) = default; //op=
public:
    Masina(): ObiectMiscator() {}
    Masina(Clock* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) {}
    
    //std::shared_ptr<ObiectMiscator>
    //    Masina* clone() const override {
    //        return new Masina(*this);
    //    }
    
    //    ObiectMiscator* clone() const override {
    //        return new Masina(*this);
    //    }
    
    std::shared_ptr <ObiectMiscator> Creare(const std::shared_ptr<Strada> s){ //strada poate fi si nullptr
        std::shared_ptr<ObiectMiscator> m;
        if(s!= nullptr)
        {
            
            if(s->getOrientare() == 1)
                m = std::make_shared<Masina>(clock, s->getCoordX(), 1, dreapta, 2);
            else
                m = std::make_shared<Masina>(clock, 1, s->getCoordY(), jos, 2);
            return m;
        }
        else{
            int tip = rand()%2 + 1;
            if(tip == 1)
            {
                //int nr = rand() % Run::s_verticale.size();
            }
            return m;
        }
    }
};


// --------------------------------------
class Pieton: public ObiectMiscator{
    
protected:
    Pieton(const Pieton& other) = default; //cc
    Pieton& operator=(const Pieton& other) = default; //op=
public:
    Pieton() : ObiectMiscator() {}
    Pieton(Clock* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) {}
    
    std::shared_ptr <ObiectMiscator> Creare() override
    {
        int x = rand() % 31;
        int y = rand() % 31;
        int directie = rand()%4+1;
        auto p = std::make_shared<Pieton>(clock, x, y, directie);
        return p;
    }
    
    //    ObiectMiscator* clone() const override {
    //        return new Pieton(*this);
    //    }
    
    int poateMergeLaUrmatoareaPozitie(std::vector<std::shared_ptr <Intersectie>> vi) override {
        // TODO de actualizat metoda cu uitat pe diagonale
        int next_x = x, next_y = y;
        Intersectie inters;
        
        switch(directie)
        {
            case sus:
                next_x--;
                break;
            case dreapta:
                next_y++;
                break;
            case jos:
                next_x++;
                break;
            case stanga:
                next_y--;
                break;
        }
        int nrInters = (int)vi.size();
        for(int i = 0; i<nrInters; i++)
            if(next_x == vi[i]->getX() && next_y == vi[i]->getY())
            {
                if(vi[i]->getSemafor() == 1)
                {
                    if(directie == stanga || directie == dreapta)
                        return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                    else
                        return 1; //trebuie sa mai astepte
                }
                else
                {
                    if(directie == sus || directie == jos)
                        return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                    else
                        return 0; //trebuie sa mai astepte
                }
            }
        return 1; //nu e intersectie, deci poate sa mearga in directia obisnuita
        
    }
    
    void Misca(int cePoateFace) override
    {
        // TODO de actualizat metoda??
        if(cePoateFace != 0)
        {
            switch(directie)
            {
                case sus:
                    x--;
                    break;
                case dreapta:
                    y++;
                    break;
                case jos:
                    x++;
                    break;
                case stanga:
                    y--;
                    break;
            }
            if(cePoateFace == 2)
            {
                int dir = rand()%4 + 1;
                switch(dir)
                {
                    case 1:
                        x--;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x++;
                        break;
                    case 4:
                        y--;
                        break;
                }
            }
        }
    }
    
};





#endif /* ObiecteMiscatoare_h */
