#include "Reserves.h"

#include "ObservateurReserves.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace {
constexpr double kEauInitialeMl = 2000.0;
constexpr double kSeuilEauMl = 500.0;
constexpr double kTheInitialG = 20.0;
constexpr double kSeuilTheG = 10.0;
}

const std::string Reserves::kEau = "eau";

Reserves::Reserves()
{
    reserves_.emplace_back(kEau, Reserve("Eau", "d’eau", "mL", kEauInitialeMl, kSeuilEauMl));
}

void Reserves::ajouterThe(const std::string& the)
{
    reserves_.emplace_back(
        the, Reserve("Thé " + the, "de thé " + the, "g", kTheInitialG, kSeuilTheG));
}

void Reserves::abonner(ObservateurReserves& observateur)
{
    if (std::find(observateurs_.begin(), observateurs_.end(), &observateur) == observateurs_.end()) {
        observateurs_.push_back(&observateur);
    }
}

void Reserves::desabonner(ObservateurReserves& observateur)
{
    observateurs_.erase(
        std::remove(observateurs_.begin(), observateurs_.end(), &observateur),
        observateurs_.end());
}

const Reserve& Reserves::reserve(const std::string& cle) const
{
    return trouver(cle);
}

void Reserves::retirer(const std::string& cle, double quantite)
{
    Reserve& cible = trouver(cle);
    signaler(cible, cible.retirer(quantite));
}

void Reserves::ajouter(const std::string& cle, double quantite)
{
    Reserve& cible = trouver(cle);
    signaler(cible, cible.ajouter(quantite));
}

void Reserves::afficher() const
{
    for (const auto& [nom, reserve] : reserves_) {
        std::cout << reserve.titre() << " : " << reserve.formater(reserve.quantite()) << '\n';
    }
}

Reserve& Reserves::trouver(const std::string& cle)
{
    for (auto& [nom, reserve] : reserves_) {
        if (nom == cle) {
            return reserve;
        }
    }
    throw std::out_of_range("Réserve inconnue : " + cle);
}

const Reserve& Reserves::trouver(const std::string& cle) const
{
    for (const auto& [nom, reserve] : reserves_) {
        if (nom == cle) {
            return reserve;
        }
    }
    throw std::out_of_range("Réserve inconnue : " + cle);
}

void Reserves::signaler(const Reserve& reserve, TransitionReserve transition) const
{
    if (transition == TransitionReserve::Aucune) {
        return;
    }
    const std::string etat =
        transition == TransitionReserve::DevenueFaible ? "faible" : "de nouveau suffisante";
    const std::string message = "Réserve " + reserve.complement() + " " + etat + " : "
        + reserve.formater(reserve.quantite()) + ".";
    for (ObservateurReserves* observateur : observateurs_) {
        observateur->notifier(message);
    }
}
