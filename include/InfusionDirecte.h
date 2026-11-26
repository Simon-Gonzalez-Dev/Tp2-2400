#pragma once

#include "ProfilInfusion.h"

// Stratégie concrète : chauffer l'eau, infuser les feuilles, servir.
class InfusionDirecte : public ProfilInfusion {
public:
    using ProfilInfusion::ProfilInfusion;

protected:
    void executerEtapes(Machine& machine) const override;
};
