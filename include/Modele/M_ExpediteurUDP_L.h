#pragma once

#include <string>
#include <cstdint>
#include <netinet/in.h>

enum class Expediteur : uint8_t {
    MASTER = 0,
    AUTRE = 1,
};

enum class TypeCommande : uint8_t {
    ORDRE = 0,
    CONNECTION = 1,
};

enum class Action : uint8_t {
    PLAY = 0,
    PAUSE = 1,
    STOP = 2,
    VOLUME = 3,
    PROGRESSION = 4,
    VITESSE = 5
};

#pragma pack(push, 1)
struct PaquetControle {
    Expediteur exp;
    TypeCommande type;
    Action action;
    float valeur;
};
#pragma pack(pop)

class M_ExpediteurUDP_L {
public:
    M_ExpediteurUDP_L(const std::string &ipBroadcast, int port);
    ~M_ExpediteurUDP_L();

    bool envoyer(const void *donnees, int taille);
    void transmettreCommande(Expediteur exp, TypeCommande type, Action action, float valeur);

private:
    int descripteurSocket = -1;
    struct sockaddr_in adresseDest{};
};