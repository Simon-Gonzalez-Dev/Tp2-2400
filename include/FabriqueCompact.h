#pragma once

#include "FabriqueMachine.h"

// Fabrique concrète : composants du modèle Compact.
class FabriqueCompact : public FabriqueMachine {
public:
    std::string nomModele() const override;
    std::unique_ptr<SystemeChauffage> creerChauffage() const override;
    std::unique_ptr<DistributeurEau> creerDistributeurEau() const override;
    std::unique_ptr<DistributeurThe> creerDistributeurThe() const override;
};
