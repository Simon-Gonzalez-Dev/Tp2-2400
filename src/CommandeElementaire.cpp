#include "CommandeElementaire.h"

#include "IterateurCommandes.h"

namespace {

// Itérateur sur une seule commande élémentaire.
class IterateurUnique : public IterateurCommandes {
public:
    explicit IterateurUnique(const CommandeElementaire& commande) : commande_(commande) {}

    bool aSuivant() const override { return !consommee_; }

    const CommandeElementaire& suivant() override
    {
        consommee_ = true;
        return commande_;
    }

private:
    const CommandeElementaire& commande_;
    bool consommee_ = false;
};

} // namespace

std::unique_ptr<IterateurCommandes> CommandeElementaire::creerIterateur() const
{
    return std::make_unique<IterateurUnique>(*this);
}
