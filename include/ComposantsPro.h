#pragma once

#include "DistributeurEau.h"
#include "DistributeurThe.h"
#include "SystemeChauffage.h"

// Famille de composants du modèle Pro.

class ChauffagePro : public SystemeChauffage {
protected:
    double degresParSeconde() const override { return 10.0; }
};

class DistributeurEauPro : public DistributeurEau {
public:
    double quantiteReelle(double volumeMl) const override { return volumeMl; }
};

class DistributeurThePro : public DistributeurThe {
public:
    double quantiteReelle(double grammes) const override { return grammes; }
};
