#pragma once

#include <string>

class Machine;

// Paramètres communs à tous les profils d'infusion.
struct ParametresInfusion {
    std::string the;
    double quantiteThe;      // g
    double volumeService;    // mL
    double temperature;      // °C
    double dureeInfusion;    // s
};

// Patron Stratégie : un profil détermine les étapes et les paramètres de la
// préparation d'un thé. Les opérations matérielles sont déléguées à la machine.
// Patron Méthode gabarit : preparer() fixe le début et la fin de la
// préparation; les sous-classes fournissent les étapes.
class ProfilInfusion {
public:
    explicit ProfilInfusion(ParametresInfusion parametres);
    virtual ~ProfilInfusion() = default;

    const std::string& the() const { return parametres_.the; }
    double quantiteThe() const { return parametres_.quantiteThe; }

    // Volume d'eau nominal pour une portion, toutes étapes confondues.
    virtual double volumeEauTotal() const;

    // Prépare une portion.
    void preparer(Machine& machine) const;

protected:
    virtual void executerEtapes(Machine& machine) const = 0;

    const ParametresInfusion& parametres() const { return parametres_; }

    // Étapes partagées par les profils : infuser les feuilles, puis servir.
    void infuserEtServir(Machine& machine) const;

private:
    ParametresInfusion parametres_;
};
