#ifndef PLAYERCONNECTION_H
#define PLAYERCONNECTION_H
#include "SDL_net.h"
#include <string>
class PlayerConnection
{
public:
    PlayerConnection();
    virtual ~PlayerConnection();

    IPaddress address;
    int playerId;
    std::string playerName;
    std::string host;
    int port;
};

#endif // PLAYERCONNECTION_H
