#pragma once

#include <string>
#include <netinet/in.h>

using namespace std;

enum class TypeCommande : uint8_t {
    LECTURE_PAUSE = 0,
    VOLUME = 1,
    PROGRESSION = 2
};

#pragma pack(push, 1)
struct PaquetControle {
    uint32_t signature = 0x5453454D;
    TypeCommande type;
    float valeur;
};
#pragma pack(pop)

class M_ExpediteurUDP_L {
public:
    M_ExpediteurUDP_L(const string &ipGroupe, int port);
    ~M_ExpediteurUDP_L();

    bool envoyer(const void *donnees, int taille);
    void transmettreCommande(TypeCommande type, float valeur);

private:
    int descripteurSocket = -1;
    sockaddr_in adresseDest{};
};