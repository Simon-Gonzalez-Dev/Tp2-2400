#pragma once

#include <optional>
#include <string>

// Configuration courante de la machine (récepteur des commandes de réglage).
class Reglages {
public:
    const std::optional<std::string>& the() const { return the_; }
    int portions() const { return portions_; }

    void definirThe(std::optional<std::string> the);
    void definirPortions(int portions);

    void afficher() const;

private:
    std::optional<std::string> the_;   // aucun thé sélectionné au démarrage
    int portions_ = 1;
};
