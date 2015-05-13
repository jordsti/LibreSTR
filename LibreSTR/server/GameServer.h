#ifndef GAMESERVER_H
#define GAMESERVER_H
#include <MessageDispatcher.h>
#include <MessageHandler.h>
#include <UdpSocket.h>
#include "AssetManager.h"
#include "PlayerConnection.h"

enum ServerState {
    SS_Lobby
};

class GameServer :
        public StiGame::Net::MessageHandler
{
public:
    static const int DEFAULT_GAME_SERVER_PORT = 6870;

    GameServer(std::string m_gameName);
    GameServer(std::string m_gameName, int m_port);
    virtual ~GameServer();

    void readPacket(StiGame::Net::UdpPacket *packet);

    void start(void);
    void stop(void);

    void setMaxPlayers(int m_maxPlayers);

    ServerState getState(void);
    void setState(ServerState m_state);

private:
    void loadAssets(void);
    ServerState state;
    AssetManager *assets;
    std::string gameName;
    int maxPlayers;
    int port;
    int masterChannel;
    int matchId;
    int currentPlayerId;
    StiGame::Net::UdpSocket masterSocket;
    StiGame::Net::MessageDispatcher dispatcher;
    std::list<PlayerConnection*> players;
};

#endif // GAMESERVER_H
