#include "Calator.h"

Calator::Calator(int cod, std::shared_ptr<Interfata_Transport> modInitial): cnp(cod), modTransport(modInitial) {
    
}

void Calator::setModTransport(std::shared_ptr<Interfata_Transport> modNou)
{
    modTransport = modNou;
}

void Calator::deplasare()
{
    if(modTransport == nullptr)
        throw "Selecteaza mod transport";
    modTransport -> transport();
}

Calator::~Calator() {}
