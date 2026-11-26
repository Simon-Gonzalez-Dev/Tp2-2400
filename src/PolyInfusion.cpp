#include "PolyInfusion.h"

#include "InfusionAvecRincage.h"
#include "InfusionDirecte.h"
#include "CommandePortions.h"
#include "CommandeSelection.h"
#include "IterateurCommandes.h"
#include "Routine.h"

#include <iostream>
#include <utility>

PolyInfusion::PolyInfusion(const FabriqueMachine& fabrique)
    : machine_(fabrique, reserves_)
{
    //                                            thé       g    mL     °C     s
    ajouterProfil(std::make_unique<InfusionDirecte>(
        ParametresInfusion{"vert", 5.0, 250.0, 80.0, 120.0}));
    ajouterProfil(std::make_unique<InfusionDirecte>(
        ParametresInfusion{"noir", 5.0, 250.0, 95.0, 180.0}));
    ajouterProfil(std::make_unique<InfusionAvecRincage>(
        ParametresInfusion{"oolong", 5.0, 250.0, 90.0, 90.0}, 50.0));

    reserves_.abonner(alerteEcran_);
    reserves_.abonner(notificationDistante_);

    construireRoutines();
}

PolyInfusion::~PolyInfusion() = default;

void PolyInfusion::afficherDemarrage() const
{
    std::cout << "Machine PolyInfusion démarrée : modèle " << machine_.nomModele() << ".\n";
}

void PolyInfusion::selectionner(const std::string& the)
{
    if (profils_.find(the) == profils_.end()) {
        std::cout << "Erreur : thé inconnu : " << the << ".\n";
        return;
    }
    CommandeSelection commande(reglages_, the);
    historique_.executer(commande.cloner());
    std::cout << commande.confirmation() << '\n';
}

void PolyInfusion::reglerPortions(int portions)
{
    CommandePortions commande(reglages_, portions);
    historique_.executer(commande.cloner());
    std::cout << commande.confirmation() << '\n';
}

void PolyInfusion::appliquerRoutine(const std::string& nom)
{
    const CommandeReglage* routine = trouverRoutine(nom);
    if (routine == nullptr) {
        return;
    }
    // Une copie par exécution : chaque exécution s'annule indépendamment.
    historique_.executer(routine->cloner());

    for (auto it = routine->creerIterateur(); it->aSuivant();) {
        std::cout << it->suivant().confirmation() << '\n';
    }
    std::cout << "Routine appliquée : " << nom << ".\n";
}

void PolyInfusion::annuler()
{
    std::cout << (historique_.annuler() ? "Opération annulée."
                                        : "Erreur : aucune opération à annuler.")
              << '\n';
}

void PolyInfusion::retablir()
{
    std::cout << (historique_.retablir() ? "Opération rétablie."
                                         : "Erreur : aucune opération à rétablir.")
              << '\n';
}

void PolyInfusion::afficherConfiguration() const
{
    reglages_.afficher();
}

void PolyInfusion::afficherApercu(const std::string& nom) const
{
    const CommandeReglage* routine = trouverRoutine(nom);
    if (routine == nullptr) {
        return;
    }
    int numero = 1;
    for (auto it = routine->creerIterateur(); it->aSuivant(); ++numero) {
        std::cout << numero << ". " << it->suivant().description() << '\n';
    }
}

void PolyInfusion::afficherReserves() const
{
    reserves_.afficher();
}

void PolyInfusion::infuser()
{
    if (!reglages_.the()) {
        std::cout << "Erreur : aucun thé sélectionné.\n";
        return;
    }
    machine_.preparer(*profils_.at(*reglages_.the()), reglages_.portions());
}

void PolyInfusion::remplirEau(double quantiteMl)
{
    remplir(Reserves::kEau, quantiteMl);
}

void PolyInfusion::remplirThe(const std::string& the, double quantiteG)
{
    remplir(the, quantiteG);
}

void PolyInfusion::reglerNotificationsDistantes(bool actives)
{
    if (actives) {
        reserves_.abonner(notificationDistante_);
        std::cout << "Notifications à distance activées.\n";
    } else {
        reserves_.desabonner(notificationDistante_);
        std::cout << "Notifications à distance désactivées.\n";
    }
}

void PolyInfusion::ajouterProfil(std::unique_ptr<ProfilInfusion> profil)
{
    const std::string the = profil->the();
    reserves_.ajouterThe(the);
    profils_[the] = std::move(profil);
}

// Les routines sont seulement construites ici : aucune commande n'est exécutée.
void PolyInfusion::construireRoutines()
{
    auto solo = std::make_unique<Routine>();
    solo->ajouter(std::make_unique<CommandeSelection>(reglages_, "vert"));
    solo->ajouter(std::make_unique<CommandePortions>(reglages_, 1));

    auto duo = std::make_unique<Routine>();
    duo->ajouter(std::make_unique<CommandeSelection>(reglages_, "noir"));
    duo->ajouter(std::make_unique<CommandePortions>(reglages_, 2));

    // « matin » contient la sous-routine « duo », pas ses commandes élémentaires.
    auto matin = std::make_unique<Routine>();
    matin->ajouter(duo->cloner());
    matin->ajouter(std::make_unique<CommandeSelection>(reglages_, "oolong"));

    routines_["solo"] = std::move(solo);
    routines_["duo"] = std::move(duo);
    routines_["matin"] = std::move(matin);
}

const CommandeReglage* PolyInfusion::trouverRoutine(const std::string& nom) const
{
    const auto it = routines_.find(nom);
    if (it == routines_.end()) {
        std::cout << "Erreur : routine inconnue : " << nom << ".\n";
        return nullptr;
    }
    return it->second.get();
}

void PolyInfusion::remplir(const std::string& cle, double quantite)
{
    const Reserve& reserve = reserves_.reserve(cle);
    std::cout << "Ajout " << reserve.complement() << " : " << reserve.formater(quantite) << ".\n";
    reserves_.ajouter(cle, quantite);
}
