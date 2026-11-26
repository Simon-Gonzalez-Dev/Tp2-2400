#pragma once

#include "DistributeurEau.h"
#include "DistributeurThe.h"
#include "SystemeChauffage.h"

// Famille de composants du modèle Compact.

class ChauffageCompact : public SystemeChauffage {
protected:
    double degresParSeconde() const override { return 5.0; }
};

class DistributeurEauCompact : public DistributeurEau {
public:
    // 20 % de pertes.
    double quantiteReelle(double volumeMl) const override { return volumeMl * 120.0 / 100.0; }
};

class DistributeurTheCompact : public DistributeurThe {
public:
    // 10 % de pertes.
    double quantiteReelle(double grammes) const override { return grammes * 110.0 / 100.0; }
};
