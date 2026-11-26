#pragma once

#include <string>

namespace affichage {

// Formate une quantité avec une virgule décimale et sans zéros superflus
// (ex. : 5.5 -> "5,5", 300.0 -> "300").
std::string formaterNombre(double valeur);

} // namespace affichage
