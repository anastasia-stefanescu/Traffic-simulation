#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <cstdlib>

std::ifstream fin ("tema1.in");
std::ofstream fout ("tema1.out");



class Strada{
    double x1, y1, x2, y2; //coord de start si finish
public:
    Strada():x1{0}, y1{0}, x2{0}, y2{0}  {
        
    }
    Strada(const double x1_, const double y1_, const double x2_, const double y2_): x1{x1_}, y1{y1_}, x2{x2_}, y2{y2_} {
        std::cout << "Am intializat var"<< x1 << " " << y1 << " " << x2 << " " << y2<< '\n';
    }
    
    Strada(const Strada& other) : x1{other.x1}, y1{other.y1}, x2{other.x2}, y2{other.y2} {
        std::cout << "Constr de copiere " << other.x1 << " " << other.y1 << " "<< other.x2 << " " << other.y2 << '\n';
    }
    
    Strada& operator=(const Strada& other) {
        x1 = other.x1;
        y1 = other.y1;
        x2 = other.x2;
        y2 = other.y2;
        std::cout << "operator= copiere: "<< other.x1 << " " << other.y1 << " "<< other.x2 << " " << other.y2 << '\n';
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Strada& str) {
        os << "operator << " << " coef_x1:" << str.x1 << " coef_y1:" << str.y1 << " coef_x2:" << str.x1 << " coef_y2:" << str.y1 << "\n";
        return os;
    }
    
    double getx1() const { return x1; }
    double gety1() const { return y1; }
    double getx2() const { return x2; }
    double gety2() const { return y2; }
    
    ~Strada() {
        std::cout << "Destr Strada\n";
    }
    
};

class Masina{
    double viteza;
    double x1, y1; //de aici deducem si sensul; trb verificat ca punctul de spawning este pe o strada valida
    int moment;
public:
    Masina() {}
    
    Masina(const double viteza_, const double x1_, const double y1_, int moment_): viteza{viteza_}, x1{x1_}, y1{y1_}, moment{moment_} {
        std::cout << "Am intializat var " <<'\n';
    } //de vazut daca initializam automat masina cu viteza si toate cele aici
    
    Masina(const Masina& other) : viteza{other.viteza}, x1{other.x1}, y1{other.y1}, moment{other.moment} {
        std::cout << "Constr de copiere " << other.viteza << " " << other.x1 << " " << other.y1 << " "<< other.moment << '\n';
    }
    
    Masina& operator=(const Masina& other) {
        viteza = other.viteza;
        x1 = other.x1;
        y1 = other.y1;
        moment = other.moment;
        std::cout << "operator= copiere: "<< other.viteza<< " "<< " " << other.x1 << " " << other.y1 << " " << other.moment<< '\n';
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Masina& ma) {
        os << "Vit: " << ma.viteza << "coord x " << ma.x1 << " coord y " << ma.y1 << " moment " << ma.moment << "\n";
        return os;
    }
    
    ~Masina() {
        std::cout << "Destr Masina\n";
    }
    
};


class Semafor{ // daca avem semafor avem automat si trecere
    bool activare;
    double x1, y1;
    Strada str;
    int moment;
public:
    Semafor(const bool activare_, double x1_, const double y1_, Strada& str_, const int moment_ ): activare{activare_}, x1{x1_}, y1{y1_}, str{str_}, moment{moment_} {
        std::cout << "Am intializat var " << '\n';
    }
    
    Semafor(const Semafor& other) : activare{other.activare}, x1{other.x1}, y1{other.y1}, str{other.str}, moment{other.moment} {
        std::cout << "Constr de copiere "<< '\n';
    }
    
    Semafor& operator=(const Semafor& other) {
        activare=other.activare;
        x1 = other.x1;
        y1 = other.y1;
        str = other.str;
        moment = other.moment;
        std::cout << "operator= copiere: "<< other.activare << " " << other.x1 << " " << other.y1 <<" " << other.str << " " << other.moment << '\n';
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Semafor& sm) {
        os << "Stare semafor: " << sm.activare << " coef_x:" << sm.x1 << " coef_y:" << sm.y1 << "str:" << sm.str << "moment" << sm.moment << "\n";
        return os;
    }
    
    ~Semafor() {
        std::cout << "Destr SEmafor\n";
    }
    
    
    double getCoordx() const { return x1; }
    double getCoordy() const { return y1; }
    
};

class Pieton{ // daca avem semafor avem automat si trecere
    double x1, y1;
    Semafor sm;
    int moment;
public:
    Pieton(double x1_, const double y1_, Semafor& sm_, const int moment_ ): x1{x1_}, y1{y1_}, sm{sm_}, moment{moment_} {
        std::cout << "Am intializat var " << '\n';
    }
    
    Pieton(const Pieton& other) : x1{other.x1}, y1{other.y1}, sm{other.sm}, moment{other.moment} {
        std::cout << "Constr de copiere "<< '\n';
    }
    
    Pieton& operator=(const Pieton& other) {
        x1 = other.x1;
        y1 = other.y1;
        sm = other.sm;
        moment = other.moment;
        std::cout << "operator= copiere: " << other.x1 << " " << other.y1 <<" " << other.sm << " " << other.moment << '\n';
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Pieton& p) {
        os << " coef_x: " << p.x1 << " coef_y: " << p.y1 << " semafor " << p.sm<< " moment" << p.moment << "\n";
        return os;
    }
    
    ~Pieton() {
        std::cout << "Destr pieton\n";
    }
};

class Run {
private:
    std::vector <Strada>str;
    std::vector <Masina> masini;
    int tp_univ; //timpul valabil peste tot
public:
    void play(){
    
        Strada s1{0, 5, 14, 7};
        Strada s2{5, 0, 8, 17};
        Strada s3{s1};
        
        
        Masina m1{3, 5, 6, 2};
        Masina m2{4, 6, 9, 1};
        
        operator<<(operator<<(std::cout, s1), s2);
        
        
        str.push_back(s1);
        str.push_back(s2);
        str.push_back(s3);
        
        masini.push_back(m1);
        masini.push_back(m2);
        
        for (int i = 1; i<= 3; i++)
        {
            spawn_masina();
            tp_univ++;
        }
    }
    
    void spawn_masina(){
        int moment =(abs(rand() - tp_univ)) % (tp_univ + 50) + tp_univ;
        double viteza = rand() % 7;
        int ind =rand() % str.size();
        double x1 = str[ind].getx1();
        double y1 = str[ind].gety1();
        Masina m{viteza, x1, y1, moment};
        masini.push_back(m);
    }
    
};
int main()
{
    Run simulare;
    simulare.play();
}
