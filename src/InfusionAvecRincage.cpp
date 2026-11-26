#include "InfusionAvecRincage.h"

#include "Machine.h"

#include <utility>

InfusionAvecRincage::InfusionAvecRincage(ParametresInfusion parametres, double volumeRincage)
    : ProfilInfusion(std::move(parametres)), volumeRincage_(volumeRincage)
{
}

double InfusionAvecRincage::volumeEauTotal() const
{
    return volumeRincage_ + ProfilInfusion::volumeEauTotal();
}

void InfusionAvecRincage::executerEtapes(Machine& machine) const
{
    const ParametresInfusion& p = parametres();

    // Phase de rinçage.
    machine.chaufferEau(p.temperature, "de l’eau de rinçage");
    machine.verserEau(volumeRincage_);
    machine.doserThe(p.the, p.quantiteThe);
    machine.rincerFeuilles();
    machine.evacuerEauRincage();

    // Phase d'infusion.
    machine.chaufferEau(p.temperature, "de l’eau de préparation");
    machine.verserEau(p.volumeService);
    infuserEtServir(machine);
}
