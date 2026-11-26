#include "ProfilInfusion.h"

#include "Machine.h"

#include <iostream>
#include <utility>

ProfilInfusion::ProfilInfusion(ParametresInfusion parametres)
    : parametres_(std::move(parametres))
{
}

double ProfilInfusion::volumeEauTotal() const
{
    return parametres_.volumeService;
}

void ProfilInfusion::preparer(Machine& machine) const
{
    std::cout << "Préparation d’un thé " << parametres_.the << ".\n";
    executerEtapes(machine);
    std::cout << "Votre thé est prêt.\n";
}

void ProfilInfusion::infuserEtServir(Machine& machine) const
{
    machine.infuser(parametres_.dureeInfusion);
    machine.servir(parametres_.volumeService);
}
