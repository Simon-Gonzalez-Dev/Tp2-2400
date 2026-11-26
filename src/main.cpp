#include "console/Console.h"

#include "FabriqueCompact.h"
#include "FabriquePro.h"
#include "PolyInfusion.h"

#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (argc != 2 || (std::string(argv[1]) != "compact" && std::string(argv[1]) != "pro")) {
        std::cerr << "Utilisation : PolyInfusion <compact|pro>\n";
        return 1;
    }
    const std::string modele = argv[1];

    // La fabrique choisie ici détermine tous les composants de la machine.
    std::unique_ptr<FabriqueMachine> fabrique;
    if (modele == "compact") {
        fabrique = std::make_unique<FabriqueCompact>();
    } else {
        fabrique = std::make_unique<FabriquePro>();
    }
    PolyInfusion application(*fabrique);

    std::cout << "Machine PolyInfusion démarrée : modèle "
              << (modele == "compact" ? "Compact" : "Pro") << ".\n";

    for (std::string ligne; std::cout << "> " << std::flush, std::getline(std::cin, ligne);) {
        const auto instruction = console::analyser(ligne);
        switch (instruction.type) {
        case console::TypeInstruction::Vide:
            break;
        case console::TypeInstruction::Aide:
            console::afficherAide();
            break;
        case console::TypeInstruction::Quitter:
            std::cout << "Arrêt de PolyInfusion.\n";
            return 0;
        case console::TypeInstruction::Invalide:
            std::cout << "Erreur : " << instruction.erreur << '\n';
            break;
        case console::TypeInstruction::Selection:
            application.selectionner(instruction.the);
            break;
        case console::TypeInstruction::Portions:
            application.reglerPortions(instruction.portions);
            break;
        case console::TypeInstruction::Configuration:
            application.afficherConfiguration();
            break;
        case console::TypeInstruction::Routine:
            application.appliquerRoutine(instruction.routine);
            break;
        case console::TypeInstruction::Apercu:
            application.afficherApercu(instruction.routine);
            break;
        case console::TypeInstruction::Annuler:
            application.annuler();
            break;
        case console::TypeInstruction::Retablir:
            application.retablir();
            break;
        case console::TypeInstruction::Infuser:
            application.infuser();
            break;
        case console::TypeInstruction::Reserves:
            application.afficherReserves();
            break;
        case console::TypeInstruction::RemplirEau:
            application.remplirEau(instruction.quantite);
            break;
        case console::TypeInstruction::RemplirThe:
            application.remplirThe(instruction.the, instruction.quantite);
            break;
        case console::TypeInstruction::Notifications:
            application.reglerNotificationsDistantes(instruction.notificationsActives);
            break;
        }
    }
    std::cout << "\nArrêt de PolyInfusion.\n";
    return 0;
}
