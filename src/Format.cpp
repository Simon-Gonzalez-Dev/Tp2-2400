#include "Format.h"

#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>

namespace affichage {

std::string formaterNombre(double valeur)
{
    std::ostringstream sortie;
    sortie.imbue(std::locale::classic());
    sortie << std::fixed << std::setprecision(2) << valeur;
    std::string texte = sortie.str();

    texte.erase(texte.find_last_not_of('0') + 1);
    if (texte.back() == '.') {
        texte.pop_back();
    }
    if (texte == "-0") {
        texte = "0";
    }
    std::replace(texte.begin(), texte.end(), '.', ',');
    return texte;
}

} // namespace affichage
