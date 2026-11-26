#pragma once

#include <string>

// Changement d'état d'une réserve par rapport à son seuil d'alerte.
enum class TransitionReserve { Aucune, DevenueFaible, RedevenueSuffisante };

// Une ressource de la machine (eau ou un type de thé) et son seuil d'alerte.
class Reserve {
public:
    // titre : « Eau », « Thé vert »; complement : « d’eau », « de thé vert ».
    Reserve(std::string titre, std::string complement, std::string unite,
            double quantiteInitiale, double seuil);

    const std::string& titre() const { return titre_; }
    const std::string& complement() const { return complement_; }
    const std::string& unite() const { return unite_; }
    double quantite() const { return quantite_; }

    bool peutFournir(double quantite) const;
    TransitionReserve retirer(double quantite);
    TransitionReserve ajouter(double quantite);

    // Ex. : « 5,5 g », « 300 mL ».
    std::string formater(double quantite) const;

private:
    bool estFaible() const;
    TransitionReserve modifier(double variation);

    std::string titre_;
    std::string complement_;
    std::string unite_;
    double quantite_;
    double seuil_;
};
