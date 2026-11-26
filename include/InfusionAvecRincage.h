#pragma once

#include "ProfilInfusion.h"

// Stratégie concrète : rincer les feuilles, puis les infuser.
// Les feuilles sont dosées une seule fois et conservées après le rinçage.
class InfusionAvecRincage : public ProfilInfusion {
public:
    InfusionAvecRincage(ParametresInfusion parametres, double volumeRincage);

    double volumeEauTotal() const override;

protected:
    void executerEtapes(Machine& machine) const override;

private:
    double volumeRincage_;   // mL
};
