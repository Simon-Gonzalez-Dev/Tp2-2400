#include "FabriqueCompact.h"

#include "ComposantsCompact.h"

std::string FabriqueCompact::nomModele() const
{
    return "Compact";
}

std::unique_ptr<SystemeChauffage> FabriqueCompact::creerChauffage() const
{
    return std::make_unique<ChauffageCompact>();
}

std::unique_ptr<DistributeurEau> FabriqueCompact::creerDistributeurEau() const
{
    return std::make_unique<DistributeurEauCompact>();
}

std::unique_ptr<DistributeurThe> FabriqueCompact::creerDistributeurThe() const
{
    return std::make_unique<DistributeurTheCompact>();
}
