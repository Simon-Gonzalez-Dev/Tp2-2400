#include "Machine.h"

#include "Format.h"
#include "DistributeurEau.h"
#include "DistributeurThe.h"
#include "FabriqueMachine.h"
#include "SystemeChauffage.h"
#include "ProfilInfusion.h"
#include "Reserves.h"

#include <iostream>

Machine::Machine(const FabriqueMachine& fabrique, Reserves& reserves)
    : chauffage_(fabrique.creerChauffage()),
      distributeurEau_(fabrique.creerDistributeurEau()),
      distributeurThe_(fabrique.creerDistributeurThe()),
      reserves_(reserves)
{
}

Machine::~Machine() = default;

bool Machine::preparer(const ProfilInfusion& profil, int portions)
{
    const double eauRequise = distributeurEau_->quantiteReelle(profil.volumeEauTotal()) * portions;
    const double theRequis = distributeurThe_->quantiteReelle(profil.quantiteThe()) * portions;
    if (!verifierReserve(Reserves::kEau, eauRequise) || !verifierReserve(profil.the(), theRequis)) {
        return false;
    }
    for (int portion = 0; portion < portions; ++portion) {
        profil.preparer(*this);
    }
    return true;
}

void Machine::chaufferEau(double temperature, const std::string& objet)
{
    chauffage_->chauffer(temperature, objet);
}

void Machine::verserEau(double volumeMl)
{
    distributeurEau_->distribuer(reserves_, volumeMl);
}

void Machine::doserThe(const std::string& the, double grammes)
{
    distributeurThe_->distribuer(reserves_, the, grammes);
}

void Machine::rincerFeuilles()
{
    std::cout << "Rinçage des feuilles.\n";
}

void Machine::evacuerEauRincage()
{
    std::cout << "Évacuation de l’eau de rinçage.\n";
}

void Machine::infuser(double dureeSecondes)
{
    std::cout << "Infusion : " << affichage::formaterNombre(dureeSecondes)
              << " secondes simulées.\n";
}

void Machine::servir(double volumeMl)
{
    std::cout << "Service : " << affichage::formaterNombre(volumeMl) << " mL.\n";
}

bool Machine::verifierReserve(const std::string& cle, double quantiteRequise) const
{
    const Reserve& reserve = reserves_.reserve(cle);
    if (reserve.peutFournir(quantiteRequise)) {
        return true;
    }
    std::cout << "Erreur : réserve " << reserve.complement() << " insuffisante.\n"
              << "Quantité requise : " << reserve.formater(quantiteRequise)
              << ". Quantité disponible : " << reserve.formater(reserve.quantite()) << ".\n"
              << "Aucune consommation effectuée.\n";
    return false;
}
