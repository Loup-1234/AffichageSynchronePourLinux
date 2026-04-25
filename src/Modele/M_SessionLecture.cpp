#include "../../include/Modele/M_SessionLecture.h"

#include <fstream>
#include <iostream>

void M_SessionLecture::preparerSessionLecture(const vector<vector<string> > &specLecteurs) {
    IdLecteurs.clear();
    IpLecteurs.clear();
    NbVideos.clear();

    for (const auto & specLecteur : specLecteurs) {
        IdLecteurs.push_back(stoi(specLecteur[0]));
        IpLecteurs.push_back(specLecteur[1]);
        NbVideos.push_back(stoi(specLecteur[2]));
    }
}

void M_SessionLecture::genererVideoComplexe(const vector<string> &listeFichierEntree) {
    if (listeFichierEntree.empty()) {
        return;
    }

    vector<vector<string> > videosParLecteur(NbVideos.size());
    int placesDisponibles = 0;

    for (size_t i = 0; i < NbVideos.size(); i++) {
        if (NbVideos[i] > 0) {
            videosParLecteur[i].push_back(listeFichierEntree[0]); // La première vidéo (audio) pour tous
        }
        placesDisponibles += (NbVideos[i] - videosParLecteur[i].size());
    }

    size_t indexVideo = 1;
    size_t lecteurActuel = 0;

    while (indexVideo < listeFichierEntree.size() && placesDisponibles > 0) {
        if (videosParLecteur[lecteurActuel].size() < NbVideos[lecteurActuel]) {
            videosParLecteur[lecteurActuel].push_back(listeFichierEntree[indexVideo]);
            indexVideo++;
            placesDisponibles--;
        }

        lecteurActuel++;
        if (lecteurActuel >= NbVideos.size()) {
            lecteurActuel = 0;
        }
    }

    for (size_t i = 0; i < videosParLecteur.size(); i++) {
        vector<string> mesVideos = videosParLecteur[i];

        if (!mesVideos.empty()) {
            string nomFichierSortie = "videosComplexes/VideoComplexe_" + to_string(IdLecteurs[i]) + ".mp4";
            VideoComplexe.genererVideoComplexe(mesVideos, nomFichierSortie);
        }
    }
}