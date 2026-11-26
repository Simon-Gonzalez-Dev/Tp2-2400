#pragma once

#include "CommandeElementaire.h"

#include <optional>
#include <string>

class Reglages;

// Commande concrète : sélectionner le thé à préparer.
class CommandeSelection : public CommandeElementaire {
public:
    CommandeSelection(Reglages& reglages, std::string the);

    void executer() override;
    void annuler() override;
    std::unique_ptr<CommandeReglage> cloner() const override;
    std::string description() const override;
    std::string confirmation() const override;

private:
    Reglages& reglages_;
    std::string the_;
    std::optional<std::string> thePrecedent_;
};
