# LOG2400 – TP2 – Discussion de la conception

**Équipe :** matricule1, matricule2

> Brouillon à relire. À exporter en PDF sous le nom
> `LOG2400_TP2_matricule1_matricule2_discussion.pdf` (3 pages au maximum).
> Si l’approbation du ou de la chargé·e a été obtenue en séance, l’indiquer ici.

## 1. Diagramme de classes

Voir [diagramme-classes.md](diagramme-classes.md) (à insérer ici sous forme d’image).

## 2. Choix des patrons

### Fabrique abstraite — modèles de machine

`FabriqueMachine` déclare la création des trois composants (`SystemeChauffage`,
`DistributeurEau`, `DistributeurThe`). `FabriqueCompact` et `FabriquePro` créent
chacune les composants de leur modèle. La `Machine` reçoit une seule fabrique à sa
construction : tous ses composants appartiennent donc forcément au même modèle.
Seul `main` connaît les fabriques concrètes. Ajouter un modèle revient à ajouter
une fabrique et ses composants, sans toucher aux profils ni à `Machine`.

Les différences d’efficacité sont dans les composants : le chauffage connaît sa
vitesse (`degresParSeconde`), les distributeurs connaissent leurs pertes
(`quantiteReelle`). Aucune classe ne teste le type de machine.

### Stratégie et Méthode gabarit — profils d’infusion

`ProfilInfusion` est la stratégie choisie selon le thé sélectionné. Il fournit les
paramètres (quantité de thé, volume, température, durée) et les étapes.
`InfusionDirecte` et `InfusionAvecRincage` définissent les deux séquences
d’étapes; les thés vert, noir et oolong sont des instances paramétrées.
`ProfilInfusion::preparer` est une méthode gabarit : elle encadre la préparation
et délègue les étapes à `executerEtapes`.

Le profil ne fait aucune opération matérielle lui-même : il appelle la `Machine`
(`chaufferEau`, `verserEau`, `doserThe`, …), qui délègue aux composants.
`Machine::preparer` coordonne la préparation sans connaître le profil concret :
ajouter un profil ne la modifie pas.

### Observateur — notifications des réserves

`Reserves` est le sujet. Chaque `Reserve` connaît son seuil et signale un
changement d’état (`DevenueFaible`, `RedevenueSuffisante`) seulement lorsqu’un
retrait ou un ajout lui fait franchir ce seuil. `Reserves` avertit alors
immédiatement ses observateurs, même en cours de préparation.

`AlerteEcran` et `NotificationDistante` implémentent `ObservateurReserves`.
Désactiver les notifications à distance désabonne seulement cet observateur :
l’écran reste abonné, et une réactivation ne retransmet rien. Un nouveau
destinataire est une nouvelle classe d’observateur, sans modifier `Reserves`.

### Commande — changements de réglages et historique

`CommandeReglage` représente un changement de réglage (`executer`, `annuler`).
`CommandeSelection` et `CommandePortions` mémorisent la valeur précédente au
moment de l’exécution, ce qui permet de restaurer exactement les réglages
antérieurs. `Historique` gère deux piles (annulables, rétablissables) et ne
dépend que de l’interface : un nouveau type de changement ne le modifie pas.
Une commande invalide est rejetée par la console avant d’atteindre l’historique.

### Composite — routines

`Routine` implémente `CommandeReglage` et contient des `CommandeReglage`, y
compris d’autres routines : `matin` contient la routine `duo`, pas ses commandes.
Elle s’exécute dans l’ordre et s’annule dans l’ordre inverse. L’historique la
traite comme n’importe quelle commande : une routine est une seule opération.

Les routines prédéfinies servent de modèles. Chaque exécution en fait une copie
(`cloner`), qui garde son propre état antérieur : deux exécutions de la même
routine s’annulent donc indépendamment. Construire les routines n’exécute rien.

### Itérateur — aperçu d’une routine

`creerIterateur` retourne un `IterateurCommandes` qui parcourt les commandes
élémentaires dans leur ordre d’exécution, sous-routines comprises. L’aperçu lit
seulement leur description : il n’exécute rien, ne modifie ni les réglages ni
l’historique, et ne voit pas la structure interne de la routine.

### Façade — point d’entrée

`PolyInfusion` assemble le système et offre une opération par instruction.
La boucle de `main` ne fait que distribuer les instructions de la console.

## 3. Plusieurs portions

`Machine::preparer(profil, portions)` calcule d’abord les besoins de l’ensemble
des portions, pertes du modèle incluses, à l’aide des distributeurs. Si une
réserve est insuffisante, la préparation est refusée sans aucune consommation.
Sinon, le même profil est exécuté une fois par portion : les profils et les
composants du TP2a sont réutilisés tels quels.
