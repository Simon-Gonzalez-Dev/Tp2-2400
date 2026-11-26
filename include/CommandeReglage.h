#pragma once

#include <memory>

class IterateurCommandes;

// Patron Commande : un changement de réglage exécutable et annulable.
// Sert aussi de composant du patron Composite (voir Routine).
class CommandeReglage {
public:
    virtual ~CommandeReglage() = default;

    virtual void executer() = 0;
    virtual void annuler() = 0;

    // Copie indépendante : chaque exécution mémorise son propre état antérieur.
    virtual std::unique_ptr<CommandeReglage> cloner() const = 0;

    virtual std::unique_ptr<IterateurCommandes> creerIterateur() const = 0;
};
