#pragma once

#include "Reserve.h"

#include <string>
#include <utility>
#include <vector>

class ObservateurReserves;

// Patron Observateur (sujet) : ensemble des réserves de la machine.
// Les observateurs abonnés sont avertis dès qu'une réserve franchit son seuil.
class Reserves {
public:
    static const std::string kEau;

    Reserves();

    void ajouterThe(const std::string& the);

    void abonner(ObservateurReserves& observateur);
    void desabonner(ObservateurReserves& observateur);

    const Reserve& reserve(const std::string& cle) const;
    void retirer(const std::string& cle, double quantite);
    void ajouter(const std::string& cle, double quantite);

    void afficher() const;

private:
    Reserve& trouver(const std::string& cle);
    void signaler(const Reserve& reserve, TransitionReserve transition) const;

    // Vecteur plutôt que map : l'ordre d'insertion est l'ordre d'affichage.
    std::vector<std::pair<std::string, Reserve>> reserves_;
    std::vector<ObservateurReserves*> observateurs_;
};
