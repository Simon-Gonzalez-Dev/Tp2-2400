cmake_minimum_required(VERSION 3.15)
project(PolyInfusion LANGUAGES CXX)

add_executable(PolyInfusion
    src/main.cpp
    src/Console.cpp
    src/Format.cpp
    src/PolyInfusion.cpp
    src/Composants.cpp
    src/FabriqueCompact.cpp
    src/FabriquePro.cpp
    src/Machine.cpp
    src/AlerteEcran.cpp
    src/NotificationDistante.cpp
    src/InfusionAvecRincage.cpp
    src/InfusionDirecte.cpp
    src/ProfilInfusion.cpp
    src/CommandeElementaire.cpp
    src/CommandePortions.cpp
    src/CommandeSelection.cpp
    src/Historique.cpp
    src/Reglages.cpp
    src/Routine.cpp
    src/Reserve.cpp
    src/Reserves.cpp
)
target_include_directories(PolyInfusion PRIVATE include)
target_compile_features(PolyInfusion PRIVATE cxx_std_17)
set_target_properties(PolyInfusion PROPERTIES CXX_EXTENSIONS OFF)
if(MSVC)
    target_compile_options(PolyInfusion PRIVATE /W4 /utf-8)
else()
    target_compile_options(PolyInfusion PRIVATE -Wall -Wextra -Wpedantic)
endif()
