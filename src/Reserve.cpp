#include "Reserve.h"

#include "Format.h"

#include <algorithm>
#include <utility>

namespace {
// Tolérance pour les comparaisons de quantités décimales.
constexpr double kTolerance = 1e-9;
}

Reserve::Reserve(std::string titre, std::string complement, std::string unite,
                 double quantiteInitiale, double seuil)
    : titre_(std::move(titre)),
      complement_(std::move(complement)),
      unite_(std::move(unite)),
      quantite_(quantiteInitiale),
      seuil_(seuil)
{
}

bool Reserve::peutFournir(double quantite) const
{
    return quantite <= quantite_ + kTolerance;
}

TransitionReserve Reserve::retirer(double quantite)
{
    return modifier(-quantite);
}

TransitionReserve Reserve::ajouter(double quantite)
{
    return modifier(quantite);
}

std::string Reserve::formater(double quantite) const
{
    return affichage::formaterNombre(quantite) + " " + unite_;
}

bool Reserve::estFaible() const
{
    return quantite_ < seuil_ - kTolerance;
}

TransitionReserve Reserve::modifier(double variation)
{
    const bool etaitFaible = estFaible();
    quantite_ = std::max(0.0, quantite_ + variation);
    if (quantite_ < kTolerance) {
        quantite_ = 0.0;
    }
    if (estFaible() == etaitFaible) {
        return TransitionReserve::Aucune;
    }
    return etaitFaible ? TransitionReserve::RedevenueSuffisante
                       : TransitionReserve::DevenueFaible;
}
