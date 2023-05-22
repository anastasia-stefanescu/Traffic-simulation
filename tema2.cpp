#include <iostream>
#include <vector>
#include <cstdlib>

// --------------------------------------
class Intersectie{
private:
    int semafor; //1 cand e verde pt orizontala, 0 altfel
    int x, y; //coordonatele - sunt legate de intersectii
    
public:
    Intersectie() {}
    Intersectie(int sem, int a, int b): semafor(sem), x(a), y(b) {}
    
    void schimbaSemafor(){
        semafor = 1-semafor;
    }
    
    int getX() {return x;}
    int getY() {return y;}
    int getSemafor() {return semafor;}
    
    ~Intersectie() = default;
};

// --------------------------------------
class Strada{
protected: //sau private?
    int x; //coord fixa
    int orientare;
    //std::vector <Intersectie*> shared_ptr
    //TODO: intersectiile pe strazi; de folosit: smart pointers, suprascriere cc si op=.
public:
    //constructor virtual
    
    Strada(const int a, const int b): x(a), orientare(b) {
        std::cout << "Am initializat strada " << x << " " << orientare;
        
    }
    
    int getCoord() {return x;};
    
    //cc, op=, etc - trebuie suprascrise;
    Strada(const Strada& other) = default; //cc
    Strada& operator=(const Strada& other) = default; //op=
    
    ~Strada() = default;
};


// --------------------------------------
class ObiectMiscator{
protected:
    int x, y; //coordonatele curente
    int directie;
    //static const viteza; // TODO - 1 pentru Pieton, 2 pentru Masini, 4 pentru pompieri
public:
    const static int sus = 1;
    const static int dreapta = 2;
    const static int jos = 3;
    const static int stanga = 4;
    
    //constructor virtual
    ObiectMiscator(int a, int b, int dir): x(a), y(b), directie(dir) {}
    
    virtual ObiectMiscator* clone() const = 0;
    
    virtual ~ObiectMiscator() = default;
    //cc, op=, etc
    //destructor
    
    virtual int poateMergeLaUrmatoareaPozitie(std::vector <Intersectie> vi) { return 0; }
        
    virtual void Misca(int ){}
    
};


// --------------------------------------
class Masina: public ObiectMiscator{
protected:
    Masina(const Masina& other) = default; //cc
    Masina& operator=(const Masina& other) = default; //op=
public:
    Masina(int a, int b, int dir) : ObiectMiscator(a, b, dir) {}
    
    std::shared_ptr<ObiectMiscator> Masina::clone() const override {
        return std::make_shared<Masina>(*this);
    }
//
//    ObiectMiscator* clone() const override {
//        return new Masina(*this);
//    }

    
    int poateMergeLaUrmatoareaPozitie(std::vector <Intersectie> vi) override {
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
            if(next_x == vi[i].getX() && next_y == vi[i].getY())
            {
                if(vi[i].getSemafor() == 1)
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
};


// --------------------------------------
class Pieton: public ObiectMiscator{

protected:
    Pieton(const Pieton& other) = default; //cc
    Pieton& operator=(const Pieton& other) = default; //op=
public:
    Pieton(int a, int b, int dir) : ObiectMiscator(a, b, dir) {}
    
    ObiectMiscator* clone() const override {
        return new Pieton(*this);
    }
    
    int poateMergeLaUrmatoareaPozitie(std::vector <Intersectie> vi) override {
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
            if(next_x == vi[i].getX() && next_y == vi[i].getY())
            {
                if(vi[i].getSemafor() == 1)
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



// --------------------------------------
int main()
{
    int nrStrazi;
    int x,orientare;
    std::vector <Strada> v_strazi_orizontale;
    std::vector <Strada> v_strazi_verticale;
    std::vector <Intersectie> v_intersectii;
    std::vector <Masina> v_masini;
    std::vector <Pieton> v_pietoni;
    //TODO: pt dynamic cast
    // std::vector <ObiectMiscator> v_obiectMiscator (atat pentru masini si pietoni)
    // si apoi cu dynamic cast in ultimul for vedem in functie de tipul obiectului ce functie Misca() apelam
//    if(dynamic_cast<Masina*>(v_obiectMiscator[i])) {
//          v_obiectMiscator.Misca();
    
    std::cin >> nrStrazi;
    //strada trebuie sa fie intre 1 si 29.
    for (int i = 1; i<= nrStrazi; i++)
    {
        std::cin >> x >> orientare;
        //TODO: aruncat exceptii pt valori neconforme
        Strada s{x, orientare};
        if(orientare == 1)
        {
            v_strazi_orizontale.push_back(s);
            int NrVerticale = (int)v_strazi_verticale.size();
            for(int i = 0; i<NrVerticale; i++)
            {
                Intersectie inters{1, s.getCoord(), v_strazi_verticale[i].getCoord()};
                v_intersectii.push_back(inters);
            }
            //adaugam o masina la inceputul acestei strazi;
            Masina m(s.getCoord(), 1, ObiectMiscator::dreapta);
            v_masini.push_back(m);
        }
        else
        {
            v_strazi_verticale.push_back(s);
            int NrOrizontale = (int)v_strazi_orizontale.size();
            for(int i = 0; i<NrOrizontale; i++)
            {
                Intersectie inters(1, s.getCoord(), v_strazi_orizontale[i].getCoord());
                v_intersectii.push_back(inters);
            }
            //adaugam o masina la inceputul acestei strazi;
            Masina m(1, s.getCoord(), ObiectMiscator::jos);
            v_masini.push_back(m);
        }
    }
    
    for (int i = 1; i<= 10; i++)
    {
        int x = rand() % 31;
        int y = rand() % 31;
        int directie = rand()%4+1;
        Pieton p(x, y, directie);
        v_pietoni.push_back(p);
    }
    
    //simulam miscarea masinilor si pietonilor pt 100 de unitati de timp
    for(int timp = 1; timp <= 100; timp++)
    {
        if(timp % 6)
        {
            int nrInters = (int)v_intersectii.size();
            for(int i = 0; i< nrInters; i++)
                v_intersectii[i].schimbaSemafor();
        }
        int NrMasini = (int)v_masini.size();
        int NrPietoni = (int)v_pietoni.size();
        for (int i = 0; i<NrMasini; i++)
        {
            v_masini[i].Misca(v_masini[i].poateMergeLaUrmatoareaPozitie(v_intersectii));
        }
        for (int i = 0; i<NrPietoni; i++)
        {
            v_pietoni[i].Misca(v_pietoni[i].poateMergeLaUrmatoareaPozitie(v_intersectii));
            //TO DO!!!
        }
    }
    
    return 0;
}
