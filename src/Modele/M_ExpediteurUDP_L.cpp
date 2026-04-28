#include "../../include/Modele/M_ExpediteurUDP_L.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

M_ExpediteurUDP_L::M_ExpediteurUDP_L(const string &ipGroupe, const int port) {
    descripteurSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (descripteurSocket != -1) {
        adresseDest.sin_family = AF_INET;
        adresseDest.sin_port = htons(port);
        inet_pton(AF_INET, ipGroupe.c_str(), &adresseDest.sin_addr);
    }
}

M_ExpediteurUDP_L::~M_ExpediteurUDP_L() {
    if (descripteurSocket != -1) {
        close(descripteurSocket);
    }
}

bool M_ExpediteurUDP_L::envoyer(const void *donnees, const int taille) {
    if (descripteurSocket == -1) return false;

    return sendto(descripteurSocket, donnees, taille, 0,
                  reinterpret_cast<sockaddr *>(&adresseDest), sizeof(adresseDest)) != -1;
}

void M_ExpediteurUDP_L::transmettreCommande(const TypeCommande type, const float valeur) {
    const PaquetControle p{ type, valeur};
    envoyer(&p, sizeof(p));
}