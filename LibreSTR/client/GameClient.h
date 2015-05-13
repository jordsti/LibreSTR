#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <string>
#include <SGThread.h>
#include <vector>

enum ClientState {
    CS_NotConnected,
    CS_Lobby

};

class GameClient
{
public:
    GameClient(std::string m_host, int m_port);
    virtual ~GameClient();

    std::string getPlayerName(void);
    void setPlayerName(std::string m_playerName);

    std::string getHost(void);
    int getPort(void);

    ClientState getState(void);
    void setState(ClientState m_state);

    bool isRunning(void);

    void start(void);

    int getPlayerId(void);
    void setPlayerId(int m_playerId);

    void addPlayer(std::string m_playerName);
    void clearPlayers(void);

private:
    std::vector< std::string > players;
    std::string playerName;
    int playerId;
    bool running;
    ClientState state;
    std::string host;
    StiGame::Thread *clientThread;
    int port;
};

int GameClient_Loop(void *data_ptr);

#endif // GAMECLIENT_H
