#include "Routine.h"

#include "IterateurCommandes.h"

#include <utility>

namespace {

// Parcourt, l'un après l'autre, les itérateurs des commandes d'une routine.
// Les sous-routines sont ainsi parcourues en profondeur.
class IterateurRoutine : public IterateurCommandes {
public:
    explicit IterateurRoutine(std::vector<std::unique_ptr<IterateurCommandes>> iterateurs)
        : iterateurs_(std::move(iterateurs))
    {
        avancer();
    }

    bool aSuivant() const override { return position_ < iterateurs_.size(); }

    const CommandeElementaire& suivant() override
    {
        const CommandeElementaire& commande = iterateurs_[position_]->suivant();
        avancer();
        return commande;
    }

private:
    // Saute les itérateurs épuisés (ex. : une sous-routine vide).
    void avancer()
    {
        while (position_ < iterateurs_.size() && !iterateurs_[position_]->aSuivant()) {
            ++position_;
        }
    }

    std::vector<std::unique_ptr<IterateurCommandes>> iterateurs_;
    std::size_t position_ = 0;
};

} // namespace

void Routine::ajouter(std::unique_ptr<CommandeReglage> commande)
{
    commandes_.push_back(std::move(commande));
}

void Routine::executer()
{
    for (auto& commande : commandes_) {
        commande->executer();
    }
}

void Routine::annuler()
{
    for (auto it = commandes_.rbegin(); it != commandes_.rend(); ++it) {
        (*it)->annuler();
    }
}

std::unique_ptr<CommandeReglage> Routine::cloner() const
{
    auto copie = std::make_unique<Routine>();
    for (const auto& commande : commandes_) {
        copie->ajouter(commande->cloner());
    }
    return copie;
}

std::unique_ptr<IterateurCommandes> Routine::creerIterateur() const
{
    std::vector<std::unique_ptr<IterateurCommandes>> iterateurs;
    for (const auto& commande : commandes_) {
        iterateurs.push_back(commande->creerIterateur());
    }
    return std::make_unique<IterateurRoutine>(std::move(iterateurs));
}
