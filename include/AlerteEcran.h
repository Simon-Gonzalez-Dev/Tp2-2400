#pragma once

#include "ObservateurReserves.h"

// Observateur concret : alertes affichées à l'écran de la machine.
class AlerteEcran : public ObservateurReserves {
public:
    void notifier(const std::string& message) override;
};
