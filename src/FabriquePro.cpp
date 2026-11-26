#include "FabriquePro.h"

#include "ComposantsPro.h"

std::string FabriquePro::nomModele() const
{
    return "Pro";
}

std::unique_ptr<SystemeChauffage> FabriquePro::creerChauffage() const
{
    return std::make_unique<ChauffagePro>();
}

std::unique_ptr<DistributeurEau> FabriquePro::creerDistributeurEau() const
{
    return std::make_unique<DistributeurEauPro>();
}

std::unique_ptr<DistributeurThe> FabriquePro::creerDistributeurThe() const
{
    return std::make_unique<DistributeurThePro>();
}
