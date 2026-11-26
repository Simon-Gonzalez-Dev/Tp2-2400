#pragma once

#include <string>

// Patron Observateur : destinataire des alertes sur l'état des réserves.
class ObservateurReserves {
public:
    virtual ~ObservateurReserves() = default;
    virtual void notifier(const std::string& message) = 0;
};
