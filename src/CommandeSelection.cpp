#include "CommandeSelection.h"

#include "Reglages.h"

#include <utility>

CommandeSelection::CommandeSelection(Reglages& reglages, std::string the)
    : reglages_(reglages), the_(std::move(the))
{
}

void CommandeSelection::executer()
{
    thePrecedent_ = reglages_.the();
    reglages_.definirThe(the_);
}

void CommandeSelection::annuler()
{
    reglages_.definirThe(thePrecedent_);
}

std::unique_ptr<CommandeReglage> CommandeSelection::cloner() const
{
    return std::make_unique<CommandeSelection>(*this);
}

std::string CommandeSelection::description() const
{
    return "Sélectionner le thé " + the_ + ".";
}

std::string CommandeSelection::confirmation() const
{
    return "Thé sélectionné : " + the_ + ".";
}
