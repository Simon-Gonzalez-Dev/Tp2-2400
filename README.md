# PolyInfusion — TP2 (LOG2400)

Application console C++17 qui simule une machine à thé PolyInfusion
(modèles `compact` et `pro`), conçue à base de patrons de conception.

## Prérequis

- CMake 3.15 ou plus récent.
- Un compilateur C++17 : MSVC, GCC ou Clang.
- Un terminal prenant en charge UTF-8. Les fichiers sources sont encodés en UTF-8.

## Compiler et exécuter

### Avec Visual Studio Code

Ouvrez le dossier `PolyInfusion` dans VS Code (extensions recommandées :
C/C++ et CMake Tools).

- **Compiler** : `Ctrl+Shift+B` (`Cmd+Shift+B` sur macOS) lance la tâche « Compiler ».
- **Exécuter** : *Terminal → Run Task…* → « Exécuter : compact » ou « Exécuter : pro ».
- **Déboguer** : `F5`, puis choisir la configuration du modèle et de la plateforme.

### En ligne de commande

Depuis le dossier contenant `CMakeLists.txt` :

**Linux et macOS**

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/PolyInfusion compact
```

**Windows — générateur Visual Studio**

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\PolyInfusion.exe compact
```

Pour le modèle Pro, remplacer `compact` par `pro`.
Avec un générateur à configuration unique (Ninja ou MinGW), l’exécutable se trouve
généralement dans `build` plutôt que dans `build/Debug`.

## Instructions

| Instruction | Effet |
|---|---|
| `selection <vert\|noir\|oolong>` | Sélectionner le thé à préparer (réversible). |
| `portions <nombre>` | Régler le nombre de portions, entier strictement positif (réversible). |
| `configuration` | Afficher le thé sélectionné et le nombre de portions. |
| `routine <solo\|duo\|matin>` | Appliquer une routine prédéfinie (réversible, une seule opération). |
| `apercu <solo\|duo\|matin>` | Afficher les changements de réglages d’une routine. |
| `undo` / `redo` | Annuler / rétablir le dernier changement de réglages. |
| `infuser` | Préparer le nombre de portions configuré du thé sélectionné. |
| `reserves` | Afficher les réserves d’eau et de thé. |
| `remplir eau <quantite>` | Ajouter de l’eau, en millilitres. |
| `remplir <vert\|noir\|oolong> <quantite>` | Ajouter du thé, en grammes. |
| `notifications <activer\|désactiver>` | Gérer les notifications à distance. |
| `h` / `q` | Afficher l’aide / quitter. |

Les instructions sont en minuscules. Les quantités de remplissage doivent être
strictement positives; utilisez un point pour les décimales (`remplir vert 1.5`).
Les erreurs de syntaxe ne déclenchent aucune instruction métier.

## Conception

| Patron | Classes | Rôle |
|---|---|---|
| Fabrique abstraite | `FabriqueMachine`, `FabriqueCompact`, `FabriquePro` | Créer une famille cohérente de composants pour le modèle choisi. |
| Stratégie + Méthode gabarit | `ProfilInfusion`, `InfusionDirecte`, `InfusionAvecRincage` | Étapes et paramètres de préparation selon le thé. |
| Observateur | `Reserves`, `ObservateurReserves`, `AlerteEcran`, `NotificationDistante` | Alertes lorsqu’une réserve franchit son seuil. |
| Commande | `CommandeReglage`, `CommandeSelection`, `CommandePortions`, `Historique` | Changements de réglages exécutables, annulables et rétablissables. |
| Composite | `Routine` | Regrouper des commandes et des sous-routines en une seule opération. |
| Itérateur | `IterateurCommandes` | Parcourir les commandes élémentaires d’une routine pour l’aperçu. |
| Façade | `PolyInfusion` | Point d’entrée unique utilisé par la console. |

Le diagramme de classes se trouve dans [docs/diagramme-classes.md](docs/diagramme-classes.md).

## Organisation

```text
PolyInfusion/
├── CMakeLists.txt
├── README.md
├── .vscode/    Projet Visual Studio Code (tâches et débogage)
├── docs/       Diagramme de classes et document de discussion
├── include/    Tous les fichiers .h
└── src/        Tous les fichiers .cpp, dont main.cpp
```

Pour ajouter un fichier `.cpp`, l’inscrire dans la liste `add_executable` de
`CMakeLists.txt`, puis relancer la configuration CMake.
