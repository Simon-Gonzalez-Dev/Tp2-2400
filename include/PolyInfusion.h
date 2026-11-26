#pragma once

#include "Machine.h"
#include "AlerteEcran.h"
#include "NotificationDistante.h"
#include "Historique.h"
#include "Reglages.h"
#include "Reserves.h"

#include <map>
#include <memory>
#include <string>

class CommandeReglage;
class FabriqueMachine;
class ProfilInfusion;

// Patron Façade : point d'entrée unique de la console vers le système.
// Assemble la machine, les réserves, les notifications, les profils
// d'infusion, les réglages et les routines prédéfinies.
class PolyInfusion {
public:
    explicit PolyInfusion(const FabriqueMachine& fabrique);
    ~PolyInfusion();

    void afficherDemarrage() const;

    // Réglages (opérations réversibles).
    void selectionner(const std::string& the);
    void reglerPortions(int portions);
    void appliquerRoutine(const std::string& nom);
    void annuler();
    void retablir();

    // Consultation.
    void afficherConfiguration() const;
    void afficherApercu(const std::string& nom) const;
    void afficherReserves() const;

    // Machine et réserves.
    void infuser();
    void remplirEau(double quantiteMl);
    void remplirThe(const std::string& the, double quantiteG);
    void reglerNotificationsDistantes(bool actives);

private:
    void ajouterProfil(std::unique_ptr<ProfilInfusion> profil);
    void construireRoutines();
    const CommandeReglage* trouverRoutine(const std::string& nom) const;
    void remplir(const std::string& cle, double quantite);

    Reserves reserves_;
    AlerteEcran alerteEcran_;
    NotificationDistante notificationDistante_;
    Machine machine_;
    std::map<std::string, std::unique_ptr<ProfilInfusion>> profils_;
    Reglages reglages_;
    Historique historique_;
    std::map<std::string, std::unique_ptr<CommandeReglage>> routines_;
};
