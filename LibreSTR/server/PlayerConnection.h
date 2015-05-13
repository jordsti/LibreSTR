#ifndef PLAYERCONNECTION_H
#define PLAYERCONNECTION_H

#include <string>
class PlayerConnection
{
public:
    PlayerConnection();
    virtual ~PlayerConnection();

    int playerId;
    std::string playerName;
    std::string host;
    int port;
};

#endif // PLAYERCONNECTION_H
