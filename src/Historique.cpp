#include "Historique.h"

#include "CommandeReglage.h"

#include <utility>

Historique::Historique() = default;
Historique::~Historique() = default;

void Historique::executer(std::unique_ptr<CommandeReglage> commande)
{
    commande->executer();
    annulables_.push_back(std::move(commande));
    retablissables_.clear();
}

bool Historique::annuler()
{
    if (annulables_.empty()) {
        return false;
    }
    annulables_.back()->annuler();
    retablissables_.push_back(std::move(annulables_.back()));
    annulables_.pop_back();
    return true;
}

bool Historique::retablir()
{
    if (retablissables_.empty()) {
        return false;
    }
    retablissables_.back()->executer();
    annulables_.push_back(std::move(retablissables_.back()));
    retablissables_.pop_back();
    return true;
}
