#ifndef Template_h
#define Template_h

#include "ObiecteMiscatoare.h"
#include "Strazi.h"
#include "exceptions.h"
#include "Clock.h"

//template<typename T> void Move(T elem, int cePoateFace)
//{
//    if(cePoateFace != 0)
//    {
//        switch(directie)
//        {
//            case sus:
//                x--;
//                break;
//            case dreapta:
//                y++;
//                break;
//            case jos:
//                x++;
//                break;
//            case stanga:
//                y--;
//                break;
//        }
//        if(cePoateFace == 2)
//        {
//            int dir = rand()%4 + 1;
//            switch(dir)
//            {
//                case 1:
//                    x--;
//                    break;
//                case 2:
//                    y++;
//                    break;
//                case 3:
//                    x++;
//                    break;
//                case 4:
//                    y--;
//                    break;
//            }
//        }
//    }
//}




template<typename T> class Masina{
private:
    Clock* clock;
    int x, y; //coordonatele curente
    int directie;
    int viteza; // TODO - 1 pentru Pieton, 2 pentru Masini, 4 pentru pompieri
public:
    static const int sus = 1;
    static const int dreapta = 2;
    static const int jos = 3;
    static const int stanga = 4;
    
    Masina() {}
    Masina(Clock* cl, int a, int b, int dir): clock(cl), x(a), y(b), directie(dir) {
        clock->Attach(this);
    }
    
    virtual ~Masina(){
        clock->Detach(this);
    }
    
    std::shared_ptr <ObiectMiscator> Creare(const std::shared_ptr<Strada> s){ //strada poate fi si nullptr
        std::shared_ptr<ObiectMiscator> m;
        if(s!= nullptr)
        {
            
            if(s->getOrientare() == 1)
                m = std::make_shared<T>(s->getCoordX(), s->getCoordY(), dreapta, 2);
            else
                m = std::make_shared<T>(s->getCoordX(), s->getCoordY(), jos, 2);
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
    
    
}


#endif /* Template_h */
