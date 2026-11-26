#pragma once

#include "CommandeReglage.h"

#include <string>

// Feuille du Composite : un seul changement de réglage.
class CommandeElementaire : public CommandeReglage {
public:
    // Texte de l'aperçu, ex. : « Sélectionner le thé noir. ».
    virtual std::string description() const = 0;
    // Texte affiché après l'exécution, ex. : « Thé sélectionné : noir. ».
    virtual std::string confirmation() const = 0;

    std::unique_ptr<IterateurCommandes> creerIterateur() const override;
};
