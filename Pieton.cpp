#include "Pieton.h"

#include "Run.h"

#include "exceptions.hpp"


Pieton::Pieton(Clock* cl) : ObiectMiscator(cl) {
    x = rand() % 31;
    y = rand() % 31;
    directie = rand()%4+1;
    viteza = 1;
}

Pieton::Pieton(Clock* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) {viteza = 1; }

int Pieton::poateMergeLaUrmatoareaPozitie() const {
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
                    return 1; //poate sa mearga in orice directie pt ca a intrat in intersectie
                else
                    return 0; //trebuie sa mai astepte
            }
            else
            {
                if (directie == sus || directie == jos)
                    return 1; //poate sa mearga in orice directie pt ca a intrat in inters
                else
                    return 0; //trebuie sa mai astepte
            }
        }
    return 2; //nu e intersectie, deci poate sa mearga in orice directia
}
