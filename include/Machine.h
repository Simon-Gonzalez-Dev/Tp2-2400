#pragma once

#include <memory>
#include <string>

class DistributeurEau;
class DistributeurThe;
class FabriqueMachine;
class ProfilInfusion;
class Reserves;
class SystemeChauffage;

// Machine à thé : assemble les composants d'un modèle et coordonne la
// préparation. Elle ne connaît ni le modèle concret ni le profil concret.
class Machine {
public:
    Machine(const FabriqueMachine& fabrique, Reserves& reserves);
    ~Machine();

    const std::string& nomModele() const { return nomModele_; }

    // Prépare les portions demandées. Refuse, sans rien consommer, si les
    // réserves ne couvrent pas l'ensemble des portions (pertes incluses).
    bool preparer(const ProfilInfusion& profil, int portions);

    // Opérations matérielles utilisées par les profils d'infusion.
    void chaufferEau(double temperature, const std::string& objet = "");
    void verserEau(double volumeMl);
    void doserThe(const std::string& the, double grammes);
    void rincerFeuilles();
    void evacuerEauRincage();
    void infuser(double dureeSecondes);
    void servir(double volumeMl);

private:
    bool verifierReserve(const std::string& cle, double quantiteRequise) const;

    std::string nomModele_;
    std::unique_ptr<SystemeChauffage> chauffage_;
    std::unique_ptr<DistributeurEau> distributeurEau_;
    std::unique_ptr<DistributeurThe> distributeurThe_;
    Reserves& reserves_;
};
