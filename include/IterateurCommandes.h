#pragma once

class CommandeElementaire;

// Patron Itérateur : parcourt les commandes élémentaires d'une commande de
// réglage, dans leur ordre d'exécution, sans exposer sa structure interne.
class IterateurCommandes {
public:
    virtual ~IterateurCommandes() = default;
    virtual bool aSuivant() const = 0;
    virtual const CommandeElementaire& suivant() = 0;
};
