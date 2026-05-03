#include "../include/Modele/M_ExpediteurUDP_L.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

M_ExpediteurUDP_L::M_ExpediteurUDP_L(const std::string &ipBroadcast, const int port) {
    descripteurSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (descripteurSocket != -1) {
        int broadcastOpt = 1;
        setsockopt(descripteurSocket, SOL_SOCKET, SO_BROADCAST, &broadcastOpt, sizeof(broadcastOpt));

        adresseDest.sin_family = AF_INET;
        adresseDest.sin_port = htons(port);

        if (inet_pton(AF_INET, ipBroadcast.c_str(), &adresseDest.sin_addr) <= 0) {}
    }
}

M_ExpediteurUDP_L::~M_ExpediteurUDP_L() {
    if (descripteurSocket != -1) {
        close(descripteurSocket);
    }
}

bool M_ExpediteurUDP_L::envoyer(const void *donnees, const int taille) {
    if (descripteurSocket == -1) return false;

    ssize_t resultat = sendto(descripteurSocket, donnees, taille, 0,
                              (struct sockaddr *)&adresseDest, sizeof(adresseDest));

    return resultat != -1;
}

void M_ExpediteurUDP_L::transmettreCommande(Expediteur exp, TypeCommande type, Action action, float valeur) {
    const PaquetControle p{ exp, type, action, valeur };
    envoyer(&p, sizeof(p));
}