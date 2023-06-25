#include "ObiectMiscator.h"

#include "Run.h"
#include "exceptions.hpp"

ObiectMiscator::ObiectMiscator(class ClockO* cl): clock(cl) { clock->Attach(shared_from_this()); }

ObiectMiscator::ObiectMiscator(class ClockO* cl, const std::shared_ptr<Strada> s): clock(cl)  {
   if (s!= nullptr)
   {
       if (s->getOrientare() == 1) {
           x = s->getCoordX();
           y = 1;
           directie = dreapta;
       }
       else {
           x = 1;
           y = s->getCoordY();
           directie = jos;
       }
   }
   clock->Attach(shared_from_this());
//   else {
//       int tip = rand()%2 + 1;
//       if(tip == 1)
//       {
//           //int nr = rand() % Run::s_verticale.size();
//       }
//       return m;
//   }
}


ObiectMiscator::ObiectMiscator(class ClockO* cl, int a, int b, int dir): clock(cl), x(a), y(b), directie(dir) {
    clock->Attach(shared_from_this());
}

ObiectMiscator::~ObiectMiscator(){
    clock->Detach(shared_from_this());
}

void ObiectMiscator::Update(class Subject_obiecte* s) {
    if (clock == s) //din 6 in 6 unitati de timp schimbam semaforul
        Misca();
}

void ObiectMiscator::verificaDacaIeseDinTabla() const {
    if (x> 30 || x < 1 || y > 30 || y < 1)
        throw OutofRange("A iesit de pe table");
}

void ObiectMiscator::Misca() {
    
    int cePoateFace = poateMergeLaUrmatoareaPozitie();
    if (cePoateFace != 0)
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
        if (cePoateFace == 2)
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
            directie = dir;
        }
    }
    verificaDacaIeseDinTabla();
}

int ObiectMiscator::poateMergeLaUrmatoareaPozitie() const {
    std::vector<std::shared_ptr <Intersectie>> vi = Run::getVectIntersection();
    
    int next_x = x, next_y = y;
    
    switch (directie)
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
    
    for (int i = 0; i<nrInters; i++) //este in vreo intersectie
        if (next_x == vi[i]->getX() && next_y == vi[i]->getY())
        {
            if (vi[i]->getSemafor() == 1) // verde
            {
                if (directie == stanga || directie == dreapta)
                    return 2; //poate sa mearga in orice directie pt ca a intrat in intersectie
                else
                    return 0; //trebuie sa mai astepte
            }
            else
            {
                if (directie == sus || directie == jos)
                    return 2; //poate sa mearga in orice directie pt ca a intrat in inters
                else
                    return 0; //trebuie sa mai astepte
            }
        }
    return 1; //nu e intersectie, deci poate sa mearga in directia obisnuita
}

