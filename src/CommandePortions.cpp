#include "CommandePortions.h"

#include "Reglages.h"

CommandePortions::CommandePortions(Reglages& reglages, int portions)
    : reglages_(reglages), portions_(portions)
{
}

void CommandePortions::executer()
{
    portionsPrecedentes_ = reglages_.portions();
    reglages_.definirPortions(portions_);
}

void CommandePortions::annuler()
{
    reglages_.definirPortions(portionsPrecedentes_);
}

std::unique_ptr<CommandeReglage> CommandePortions::cloner() const
{
    return std::make_unique<CommandePortions>(*this);
}

std::string CommandePortions::description() const
{
    return "Régler le nombre de portions à " + std::to_string(portions_) + ".";
}

std::string CommandePortions::confirmation() const
{
    return "Nombre de portions : " + std::to_string(portions_) + ".";
}
