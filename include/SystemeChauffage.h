#pragma once

#include <string>

// Composant abstrait : chauffe l'eau à la température demandée.
// Chaque modèle de machine fournit sa propre vitesse de chauffage.
class SystemeChauffage {
public:
    virtual ~SystemeChauffage() = default;

    // objet : précision facultative, ex. « de l’eau de rinçage ».
    void chauffer(double temperatureCible, const std::string& objet = "") const;

protected:
    virtual double degresParSeconde() const = 0;
};
