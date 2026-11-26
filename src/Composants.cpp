#include "DistributeurEau.h"
#include "DistributeurThe.h"
#include "SystemeChauffage.h"

#include "Format.h"
#include "Reserves.h"

#include <iostream>

namespace {

constexpr double kTemperatureInitiale = 20.0;

// Affiche la consommation, puis la retire de la réserve (ce qui peut
// déclencher une alerte immédiatement après).
void consommer(Reserves& reserves, const std::string& cle, double quantite)
{
    const Reserve& reserve = reserves.reserve(cle);
    std::cout << "Consommation " << reserve.complement() << " : "
              << reserve.formater(quantite) << ".\n";
    reserves.retirer(cle, quantite);
}

} // namespace

void SystemeChauffage::chauffer(double temperatureCible, const std::string& objet) const
{
    const double duree = (temperatureCible - kTemperatureInitiale) / degresParSeconde();
    std::cout << "Chauffage " << (objet.empty() ? "" : objet + " ") << "à "
              << affichage::formaterNombre(temperatureCible) << " °C : "
              << affichage::formaterNombre(duree) << " secondes simulées.\n";
}

void DistributeurEau::distribuer(Reserves& reserves, double volumeMl) const
{
    consommer(reserves, Reserves::kEau, quantiteReelle(volumeMl));
}

void DistributeurThe::distribuer(Reserves& reserves, const std::string& the, double grammes) const
{
    consommer(reserves, the, quantiteReelle(grammes));
}
