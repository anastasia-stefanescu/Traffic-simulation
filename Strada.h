#pragma once

#ifndef Strada_h
#define Strada_h

class Strada{
protected:
    int x, y; // coord inceputului de strada (intr-un caroiaj)
    int orientare; // 1 orizontala si 0 verticala
public:
    //TODO: constructor virtual (clone)
    
    Strada(const int a, const int b, const int c);
    
    std::shared_ptr <Strada> citire();

    int getCoordX() const;
    int getCoordY() const;
    int getOrientare() const;
    
    //cc, op=, etc - trebuie suprascrise;
    Strada(const Strada& other) = default;
    Strada& operator=(const Strada& other) = default;
    
    ~Strada();
};


#endif
