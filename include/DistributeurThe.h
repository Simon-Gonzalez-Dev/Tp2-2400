#pragma once

#include <string>

class Reserves;

// Composant abstrait : dose les feuilles de thé depuis la réserve.
// Chaque modèle de machine applique ses propres pertes.
class DistributeurThe {
public:
    virtual ~DistributeurThe() = default;

    // Quantité réellement puisée pour obtenir la dose demandée.
    virtual double quantiteReelle(double grammes) const = 0;

    void distribuer(Reserves& reserves, const std::string& the, double grammes) const;
};
