#pragma once

#include "ObservateurReserves.h"

// Observateur concret : notifications à distance (simulées dans la console).
class NotificationDistante : public ObservateurReserves {
public:
    void notifier(const std::string& message) override;
};
