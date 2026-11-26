#pragma once

#include "CommandeElementaire.h"

class Reglages;

// Commande concrète : régler le nombre de portions à préparer.
class CommandePortions : public CommandeElementaire {
public:
    CommandePortions(Reglages& reglages, int portions);

    void executer() override;
    void annuler() override;
    std::unique_ptr<CommandeReglage> cloner() const override;
    std::string description() const override;
    std::string confirmation() const override;

private:
    Reglages& reglages_;
    int portions_;
    int portionsPrecedentes_ = 1;
};
