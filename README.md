# PolyInfusion — TP2

Projet console C++17 du cours LOG2400.

## Conception

- Fabrique abstraite : `FabriqueMachine` crée les composants du modèle choisi.
- Stratégie : `ProfilInfusion` définit les étapes de préparation de chaque thé.
- Observateur : `Reserves` avertit l’écran et les notifications à distance.
- Commande et Composite : `CommandeReglage`, `Routine` et `Historique` (undo/redo).
- Itérateur : `IterateurCommandes` parcourt une routine pour l’aperçu.

## Prérequis

- CMake 3.15 ou plus récent.
- Un compilateur C++17 : MSVC, GCC ou Clang.
- Un terminal prenant en charge UTF-8. Les fichiers sources sont encodés en UTF-8.

## Compiler et exécuter

Depuis le dossier contenant `CMakeLists.txt` :

### Windows — générateur Visual Studio

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\PolyInfusion.exe compact
```

Pour le modèle Pro, remplacer `compact` par `pro`.
Avec un générateur à configuration unique (Ninja ou MinGW), l’exécutable se trouve
généralement dans `build` plutôt que dans `build/Debug`.

### Linux et macOS — générateur à configuration unique

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/PolyInfusion compact
```

Avec Visual Studio Code, la tâche de compilation par défaut (`Ctrl+Shift+B`)
compile le projet; les tâches « Exécuter : compact » et « Exécuter : pro » le lancent.

## Utilisation

Entrez `h` pour l’aide et `q` pour quitter. Une ligne vide est ignorée.
Les instructions sont en minuscules. `infuser` ne prend aucun argument.
Les quantités de remplissage doivent être strictement positives et finies;
utilisez un point pour les décimales, par exemple `remplir vert 1.5`.
`notifications désactiver` et `notifications desactiver` sont acceptées.
Les erreurs de syntaxe ne déclenchent aucune instruction métier.

## Organisation

```text
PolyInfusion/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── console/Console.h
│   └── *.h
└── src/
    ├── main.cpp
    ├── console/Console.cpp
    └── *.cpp
```

Chaque nouveau `.cpp` doit être ajouté à la liste `add_executable` du fichier
`CMakeLists.txt`.
