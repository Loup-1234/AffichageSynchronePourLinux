cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_VERSION_MINIMUM 3.20)

project(AffichageSynchronePourLinux CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# GESTION DES DÉPENDANCES SYSTÈME (via paru/pacman)
# ==========================================

find_package(PkgConfig REQUIRED)

# On demande à CMake de trouver les bibliothèques installées sur le système
# L'utilisation de IMPORTED_TARGET permet de mieux gérer les inclusions système (évite d'inclure /usr/include directement)
pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib)
pkg_check_modules(VLC REQUIRED IMPORTED_TARGET libvlc)
pkg_check_modules(FFTW REQUIRED IMPORTED_TARGET fftw3)

# ==========================================
# FICHIERS DU PROJET
# ==========================================

set(SOURCE_FILES
        src/main.cpp
        src/Vue/V_Master.cpp
        src/Modele/M_ExpediteurUDP_L.cpp
        src/Modele/M_VideoComplexe.cpp
        src/Modele/M_SessionLecture.cpp
        src/Controleur/C_LecteurPhysiqueLocal.cpp
        src/Modele/M_LecteurPhysique.cpp
)

set(HEADER_FILES
        include/Vue/V_Master.h
        include/Modele/M_ExpediteurUDP_L.h
        include/Modele/M_VideoComplexe.h
        include/Modele/M_SessionLecture.h
        include/Controleur/C_LecteurPhysiqueLocal.h
        include/Modele/M_LecteurPhysique.h
)

add_executable(AffichageSynchronePourLinux ${SOURCE_FILES} ${HEADER_FILES})

# ==========================================
# INCLUSIONS ET LIENS
# ==========================================

target_include_directories(AffichageSynchronePourLinux PRIVATE
        include
)

target_link_libraries(AffichageSynchronePourLinux PRIVATE
        PkgConfig::RAYLIB
        PkgConfig::VLC
        PkgConfig::FFTW
        m        # Bibliothèque mathématique
        pthread  # Threads POSIX
)

# ==========================================
# DOCUMENTATION (Doxygen & Sphinx)
# ==========================================

find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_target(doxygen_generate
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/docs/Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
            COMMENT "Génération du XML Doxygen..."
    )

    add_custom_target(sphinx_generate
            COMMAND sphinx-build -b html source build/html
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
            COMMENT "Génération du HTML Sphinx..."
            DEPENDS doxygen_generate
    )

    set_target_properties(doxygen_generate sphinx_generate PROPERTIES FOLDER "Documentation")
endif ()