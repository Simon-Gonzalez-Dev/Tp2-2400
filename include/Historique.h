#pragma once

#include <memory>
#include <vector>

class CommandeReglage;

// Historique des commandes de réglage exécutées (undo / redo).
// Ne connaît que l'interface CommandeReglage : il ne distingue pas une
// commande élémentaire d'une routine.
class Historique {
public:
    Historique();
    ~Historique();

    // Exécute la commande et la conserve; les rétablissements possibles sont perdus.
    void executer(std::unique_ptr<CommandeReglage> commande);

    // Retournent false s'il n'y a aucune opération à annuler / rétablir.
    bool annuler();
    bool retablir();

private:
    std::vector<std::unique_ptr<CommandeReglage>> annulables_;
    std::vector<std::unique_ptr<CommandeReglage>> retablissables_;
};
