#pragma once

class Reserves;

// Composant abstrait : puise l'eau dans la réserve.
// Chaque modèle de machine applique ses propres pertes.
class DistributeurEau {
public:
    virtual ~DistributeurEau() = default;

    // Quantité réellement puisée pour obtenir le volume demandé.
    virtual double quantiteReelle(double volumeMl) const = 0;

    void distribuer(Reserves& reserves, double volumeMl) const;
};
