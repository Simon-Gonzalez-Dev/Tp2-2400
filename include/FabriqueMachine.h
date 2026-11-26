#pragma once

#include <memory>
#include <string>

class DistributeurEau;
class DistributeurThe;
class SystemeChauffage;

// Patron Fabrique abstraite : crée une famille cohérente de composants
// appartenant tous au même modèle de machine.
class FabriqueMachine {
public:
    virtual ~FabriqueMachine() = default;

    virtual std::string nomModele() const = 0;
    virtual std::unique_ptr<SystemeChauffage> creerChauffage() const = 0;
    virtual std::unique_ptr<DistributeurEau> creerDistributeurEau() const = 0;
    virtual std::unique_ptr<DistributeurThe> creerDistributeurThe() const = 0;
};
