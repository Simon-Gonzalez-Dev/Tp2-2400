#pragma once

#include "CommandeReglage.h"

#include <vector>

// Patron Composite : regroupe des commandes de réglage, y compris d'autres
// routines, et s'utilise comme une seule commande.
class Routine : public CommandeReglage {
public:
    Routine() = default;

    void ajouter(std::unique_ptr<CommandeReglage> commande);

    void executer() override;   // dans l'ordre prévu
    void annuler() override;    // dans l'ordre inverse
    std::unique_ptr<CommandeReglage> cloner() const override;
    std::unique_ptr<IterateurCommandes> creerIterateur() const override;

private:
    std::vector<std::unique_ptr<CommandeReglage>> commandes_;
};
