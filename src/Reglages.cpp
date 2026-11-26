#include "Reglages.h"

#include <iostream>
#include <utility>

void Reglages::definirThe(std::optional<std::string> the)
{
    the_ = std::move(the);
}

void Reglages::definirPortions(int portions)
{
    portions_ = portions;
}

void Reglages::afficher() const
{
    std::cout << "Thé sélectionné : " << the_.value_or("aucun") << ".\n"
              << "Nombre de portions : " << portions_ << ".\n";
}
