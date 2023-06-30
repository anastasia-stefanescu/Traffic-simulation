#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <string>

class Eroare: public std::out_of_range {
public:
    explicit Eroare(const std::string& message) : std::out_of_range(message) {}
};

class OutofRange: public Eroare {
public:
    explicit OutofRange(const std::string& message) :  Eroare (message) {}
};

class NotonStreet: public Eroare {
public:
    explicit NotonStreet(const std::string& message) : Eroare(message) {}
};

//================================================================
class Interfata_Transport {
public:
    virtual void transport() = 0;
};
//================================================================
class Calator {
private:
    std::shared_ptr<Interfata_Transport> modTransport;
public:
    explicit Calator(std::shared_ptr<Interfata_Transport> modInitial);
    
    void setModTransport(std::shared_ptr<Interfata_Transport> modNou);
    
    void deplasare();
    
    virtual ~Calator();
};

Calator::Calator(std::shared_ptr<Interfata_Transport> modInitial): modTransport(modInitial) {
    
}

void Calator::setModTransport(std::shared_ptr<Interfata_Transport> modNou)
{
    modTransport = modNou;
}

void Calator::deplasare()
{
    if(modTransport != nullptr)
        modTransport -> transport();
}

Calator::~Calator() {}
//============================================================================

class Strada{
protected:
    int x, y; // coord inceputului de strada (intr-un caroiaj)
    int orientare; // 1 orizontala si 0 verticala
public:
    //TODO: constructor virtual (clone)
    
    Strada(const int a, const int b, const int c);
    Strada() = default;
    
    std::shared_ptr <Strada> citire();

    int getCoordX() const;
    int getCoordY() const;
    int getOrientare() const;
    
    //cc, op=, etc - trebuie suprascrise;
    Strada(const Strada& other) = default;
    Strada& operator=(const Strada& other) = default;
    friend std::istream& operator>>(std::istream &is, Strada& str){
        is>> str.x >> str.y >> str.orientare;
        return is;
    }
    
    ~Strada() = default;
};
Strada::Strada(const int a, const int b, const int c): x(a), y(b), orientare(c) {
//    std::cout << "Am initializat strada " << x << " " << y << " " << orientare;
    
}

std::shared_ptr <Strada> Strada::citire()
{
    Strada str;
    operator>>(std::cin, str);
    //coordonatele trebuie sa fie intre 1 si 29
    if((str.x >= 1 && str.x<= 29) && (str.y >= 1 && str.y <= 29))
    {
        auto s = std::make_shared<Strada>(str.x, str.y, str.orientare);
        return s;
    }
    throw OutofRange("inserati o strada corecta (coord intre 1 si 29)");
}

int Strada::getCoordX() const {return x;};
int Strada::getCoordY() const {return y;};
int Strada::getOrientare() const {return orientare;}

//==============================================================
template <class T> class Subject {
private:
std::vector<T*> _observers;
    
public:
    Subject() = default;
virtual ~Subject()= default;

void Attach(T* o);

void Detach(T* o);

virtual void Notify();
};

template <class T> void Subject<T>::Attach(T* o)
{
    _observers.push_back(o);
}

template <class T> void Subject<T>::Detach(T* o)
{
    _observers.erase(std::remove(_observers.begin(), _observers.end(), o), _observers.end());
}

template <class T> void Subject<T>::Notify()
{
    for (const auto& obs : _observers)
    {
        obs->Update(this);
    }
}
 //==============================================================

template <class U> class Clock: public Subject<U>{
    int timp;
    
public:
    Clock();
    explicit Clock(int start);
    
    int getTime();
    
    void tick();
};

template <class U> Clock<U>::Clock() : Subject<U>() {}
template <class U> Clock<U>::Clock(int start): timp(start) {}

template <class U> int Clock<U>::getTime() {return timp;}

template <class U> void Clock<U>::tick() {
    timp++;
    Subject<U>::Notify();
}

//===============================================================
template<class T> class Observer {
    
public:
    virtual ~Observer() = default;
    virtual void Update(Subject<T>*){}
protected:
    Observer() = default;
};

//==============================================================
class Intersectie: public Observer<Intersectie>, public std::enable_shared_from_this<Intersectie> {
private:
    Clock<Intersectie>* clock;
    int semafor; // 1 cand e verde, 0 altfel
    int x, y;    //coordonatele - sunt legate de intersectii
    
public:
    Intersectie() {}
    Intersectie(Clock<Intersectie>* cl, int sem, int a, int b);
    ~Intersectie();
    
    //TODO: constructori de copiere, op=, op<< !!!!!!!!
    
    int getX();
    int getY();
    int getSemafor();
    
    void schimbaSemafor();
    
    void Update(Subject<Intersectie>* s) override;
};

//template class Subject <Intersectie>;
//using Subject_intersectii = Subject<Intersectie>;
Intersectie::Intersectie(Clock<Intersectie>*
                         cl, int sem, int a, int b): clock(cl), semafor(sem), x(a), y(b) {
    clock->Attach(this);
}

int Intersectie::getX() {return x;}
int Intersectie::getY() {return y;}
int Intersectie::getSemafor() {return semafor;}

Intersectie::~Intersectie() {
    clock->Detach(this);
};

void Intersectie::schimbaSemafor(){
    semafor = 1-semafor;
}

void Intersectie::Update(Subject<Intersectie>* s){
        auto c = dynamic_cast<Subject<Intersectie>*>(clock);
    if (c == s && clock->getTime() % 6 == 0) //din 6 in 6 unitati de timp schimbam semaforul
    {
        schimbaSemafor();
    }
}
//==============================================================

class ObiectMiscator : public Observer<ObiectMiscator>, public std::enable_shared_from_this<ObiectMiscator> {
protected:
    Clock<ObiectMiscator>* clock;
    int x, y; //coordonatele curente
    int directie;
    int viteza; // 1 pentru Pieton, 2 pentru Masini, 4 pentru Masini prioritate
    
public:
    static const int sus = 1;
    static const int dreapta = 2;
    static const int jos = 3;
    static const int stanga = 4;
    
    int getX() {return x;}
    int getY() {return y;}
    
    explicit ObiectMiscator(Clock<ObiectMiscator>* cl);
    
    ObiectMiscator(Clock<ObiectMiscator>* cl, const std::shared_ptr<Strada> s);
    
    ObiectMiscator(Clock<ObiectMiscator>* cl, int a, int b, int dir);
    
    virtual ~ObiectMiscator();
    
    //virtual ObiectMiscator* clone() const = 0;
    //virtual std::shared_ptr<ObiectMiscator> clone() const = 0;
    
    //cc, op=, etc
    
    void verificaDacaIeseDinTabla() const ;
    
    virtual void Misca();
    
    virtual int poateMergeLaUrmatoareaPozitie() const;
    
    void Update(Subject<ObiectMiscator>* s) override;
};

ObiectMiscator::ObiectMiscator(Clock<ObiectMiscator>* cl): clock(cl) { clock->Attach(this); }

ObiectMiscator::ObiectMiscator(Clock<ObiectMiscator>* cl, const std::shared_ptr<Strada> s): clock(cl)  {
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
   clock->Attach(this);
}


ObiectMiscator::ObiectMiscator(Clock<ObiectMiscator>* cl, int a, int b, int dir): clock(cl), x(a), y(b), directie(dir) {
    clock->Attach(this);
}

ObiectMiscator::~ObiectMiscator(){
    clock->Detach(this);
}

void ObiectMiscator::Update(Subject<ObiectMiscator>* s) {
    auto c = dynamic_cast<Subject<ObiectMiscator>*>(clock);
    if (c == s) //din 6 in 6 unitati de timp schimbam semaforul
    {
        try{
            Misca();
        }catch(OutofRange& err)
        {
            std::cout << "Obiectul " << x << " " << y << " " << directie << err.what() << '\n';
            if(directie% 2 == 0)
                directie--;
            else
                directie++;
            if(x >= 30)
                x = 29;
            else
            {
                if(y >= 30)
                    y = 29;
                else
                {
                    if(x < 1)
                        x = 1;
                    else
                        y = 1;
                }
            }
            std::cout<< " Noile coord sunt: " << x << " " << y << " " << directie << '\n' << '\n';
        }
    }
}

void ObiectMiscator::verificaDacaIeseDinTabla() const {
    if (x>= 30 || x < 1 || y >= 30 || y < 1) {
       // delete this;
        //std::cout << "Obiectul" << x << " " << y << " " << directie << " a iesit de pe tabla" << '\n';
        throw OutofRange(" a iesit de pe tabla ");
    }
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


//=================================================================

class Masina_prioritara: public ObiectMiscator, public Interfata_Transport {
public:
    Masina_prioritara(const Masina_prioritara& other) = default; //cc
    Masina_prioritara& operator=(const Masina_prioritara& other) = default; //op=
    
    explicit Masina_prioritara(Clock<ObiectMiscator>* cl);
    
    Masina_prioritara(Clock<ObiectMiscator>* cl, const std::shared_ptr<Strada> s);
    
    Masina_prioritara(Clock<ObiectMiscator>* cl, int a, int b, int dir);
    
    void Misca() override;
    
    void transport() override;
    //std::shared_ptr<ObiectMiscator> clone() const override { return std::make_shared<Masina_prioritara>(*this); }
    
    
};

Masina_prioritara::Masina_prioritara(Clock<ObiectMiscator>* clock): ObiectMiscator(clock) { viteza = 4; };

Masina_prioritara::Masina_prioritara(Clock<ObiectMiscator>* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) { viteza = 4; }

Masina_prioritara::Masina_prioritara(Clock<ObiectMiscator>* clock, const std::shared_ptr<Strada> s) : ObiectMiscator(clock, s)
{ viteza = 4; }

void Masina_prioritara::Misca()
{
    switch(directie)
    {
        case sus:
            x -= viteza;
            break;
        case dreapta:
            y+= viteza;
            break;
        case jos:
            x+= viteza;
            break;
        case stanga:
            y-= viteza;
            break;
    }
    verificaDacaIeseDinTabla();
}

void Masina_prioritara::transport() { Masina_prioritara::Misca(); }


//=================================================================

class Masina: public ObiectMiscator, public Interfata_Transport {
public:
    Masina(const Masina& other) = default; //cc
    Masina& operator=(const Masina& other) = default; //op=
    Masina(Clock<ObiectMiscator>* cl, const std::shared_ptr<Strada> s);
    Masina(Clock<ObiectMiscator>* cl, int a, int b, int dir);
    
    void transport() override;
    
    //std::shared_ptr<ObiectMiscator> clone() const override { return std::make_shared<Masina>(*this); }
};

Masina::Masina(Clock<ObiectMiscator>* cl, const std::shared_ptr<Strada> s): ObiectMiscator(cl, s) { viteza = 2; }

Masina::Masina(Clock<ObiectMiscator>* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) { viteza = 2; }

void Masina::transport() { Misca(); }

//=================================================================

class Pieton: public ObiectMiscator{
    
public:
    Pieton(const Pieton& other) = default; //cc
    Pieton& operator=(const Pieton& other) = default; //op=

    explicit Pieton(Clock<ObiectMiscator>* cl);
    Pieton(Clock<ObiectMiscator>* cl, int a, int b, int dir);
    
    int poateMergeLaUrmatoareaPozitie() const override;
    
    //ObiectMiscator* clone() const override { return new Pieton(*this); }
    //std::shared_ptr<ObiectMiscator> clone() const override { return std::make_shared<Pieton>(*this); }
};

Pieton::Pieton(Clock<ObiectMiscator>* cl) : ObiectMiscator(cl) {
    x = rand() % 31;
    y = rand() % 31;
    directie = rand()%4+1;
    viteza = 1;
}

Pieton::Pieton(Clock<ObiectMiscator>* cl, int a, int b, int dir) : ObiectMiscator(cl, a, b, dir) {viteza = 1; }




//=================================================================


class Run{
    
    static Clock<Intersectie>* clock_i;
    static Clock<ObiectMiscator>* clock_o;
    
//    const int stanga = 1;
//    const int dreapta = 2;
//    const int jos = 3;
//    const int sus = 4;
    
    static std::vector <std::shared_ptr<Intersectie>> v_intersectii;
    std::vector <std::shared_ptr<ObiectMiscator>> v_masini;
    std::vector <std::shared_ptr<ObiectMiscator>> v_pietoni;
    std::vector <std::shared_ptr<ObiectMiscator>> v_calatori;
    
    std::vector <std::shared_ptr<Strada>> v_strazi_orizontale;
    std::vector <std::shared_ptr<Strada>> v_strazi_verticale;
    std::vector <std::shared_ptr<Strada>> strazi;
    
public:
    
    Run();
    
    void play();
    
    void afisare();
    
    static std::vector <std::shared_ptr<Intersectie>> getVectIntersection() {return v_intersectii;}
};

Clock<Intersectie>* Run::clock_i;
Clock<ObiectMiscator>* Run::clock_o;

std::vector<std::shared_ptr<Intersectie>> Run::v_intersectii;

Run::Run() {
  
    int nrStrazi;
    int i, j;
    
    
    //adaugam un clock
    clock_i = new Clock<Intersectie>(0);
    clock_o = new Clock<ObiectMiscator>(0);
    
    // adaugam strazile
    std::cin >> nrStrazi;

    std::shared_ptr <Strada> s;
    for (i = 1; i<= nrStrazi; i++)
    {
        
        do{
            try{
                s = s->citire();
                break;
            } catch (OutofRange& err){
                std::cout << "range gresit la strada : " << err.what() << '\n';
            }
        } while(true);
        
        // adaugam intersectii
        if (s->getOrientare() == 1) // strada orizontala
        {
            v_strazi_orizontale.push_back(s);
            int NrVerticale = (int)v_strazi_verticale.size();
            for(j = 0; j<NrVerticale; j++)
            {
                auto intersectie = std::make_shared<Intersectie>(clock_i, 1, s->getCoordY(), v_strazi_verticale[j]->getCoordX());
                v_intersectii.push_back(intersectie);
            }
        }
        else
        {
            v_strazi_verticale.push_back(s);
            int NrOrizontale = (int)v_strazi_orizontale.size();
            for(j = 0; j<NrOrizontale; j++)
            {
                auto intersectie = std::make_shared<Intersectie>(clock_i, 1, s->getCoordX(), v_strazi_orizontale[j]->getCoordY());
                v_intersectii.push_back(intersectie);
            }
        }
        
        // adaugam o masina la inceputul acestei strazi;
        int tip = rand() % 2;
        if (tip == 1) { //alegem random tipul de masina care se spawneaza
            auto baseMasina = std::make_shared<Masina>(clock_o, s);
            v_masini.push_back(baseMasina);
        }
        else {
            auto baseMasina = std::make_shared<Masina_prioritara>(clock_o, s);
            v_masini.push_back(baseMasina);
        }
    }
    
    //adaugam pietoni
    for (i = 1; i <= 10; i++)
    {
        //std::shared_ptr <ObiectMiscator> basePieton = std::make_shared<Pieton>(clock);
        v_pietoni.emplace_back(std::make_shared<Pieton>(clock_o));
    }
    
    //adaugam calatori
    std::shared_ptr<Interfata_Transport> m1 = std::make_shared<Masina>(clock_o, v_strazi_verticale[1]);
    std::shared_ptr<Interfata_Transport> m2 = std::make_shared<Masina_prioritara>(clock_o, v_strazi_orizontale[1]);
    Calator c1(m1);
    c1.setModTransport(m2);
    Calator c2(m1);
    try{
        c1.deplasare();
    }catch(NotonStreet& err)
    {
        std::cout << "Calatorul a iesit de pe tabla: " << err.what() << '\n';
    }
    
    try{
        c2.deplasare();
    }catch(NotonStreet& err)
    {
        std::cout << "Calatorul a iesit de pe tabla: " << err.what() << '\n';
    }
}

void Run::play(){
    int i;
    
    for (i = 1; i<= 10; i++)
    {
        clock_i->tick();
        clock_o->tick();
        afisare();
    }
}

void Run::afisare(){
    int i, j;
    char tabla[30][30][10];
    
    for(i = 1; i<= 29; i++)
        for(j = 1; j<= 29; j++)
            strcpy(tabla[i][j],"|_");
        

    for (const auto& inters: v_intersectii)
        strcpy(tabla[inters->getX()][inters->getY()], "|X");
    
    for (const auto& masina: v_masini)
    {
        auto m = dynamic_pointer_cast<Masina>(masina);
        if(m)
            strcpy(tabla[masina->getX()][masina->getY()], "|M");
        else
            strcpy(tabla[masina->getX()][masina->getY()], "|M");
    }
    
    for (const auto& pietoni: v_pietoni)
        strcpy(tabla[pietoni->getX()][pietoni->getY()], "|P");
    
    for(i = 1; i<= 29; i++)
    {
        for(j = 1; j<= 29; j++)
            std::cout << tabla[i][j];
        std::cout << '\n';
    }
        
}

//===================================================================
int Pieton::poateMergeLaUrmatoareaPozitie() const {
    int i;
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
    
    for (i = 0; i<nrInters; i++) //este in vreo intersectie
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

int ObiectMiscator::poateMergeLaUrmatoareaPozitie() const {
    int i;
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

    for (i = 0; i<nrInters; i++) //este in vreo intersectie
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

//==========================================================================================================
int main()
{
    Run run_simulation;
    run_simulation.play();
    
    return 0;
}
