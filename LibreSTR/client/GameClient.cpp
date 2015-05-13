#include "GameClient.h"
#include <UdpSocket.h>
#include <PacketStream.h>
#include "Match.h"
#include <iostream>
using namespace StiGame;
using namespace Net;

GameClient::GameClient(std::string m_host, int m_port)
{
    host = m_host;
    port = m_port;
    running = false;
    playerId = 0;
    state = CS_NotConnected;
}

GameClient::~GameClient()
{

}

std::string GameClient::getHost(void)
{
    return host;
}

int GameClient::getPort(void)
{
    return port;
}

ClientState GameClient::getState(void)
{
    return state;
}

bool GameClient::isRunning(void)
{
    return running;
}

void GameClient::start(void)
{
    clientThread = new Thread(&GameClient_Loop, "client thread", this);
    running = true;
}

int GameClient::getPlayerId(void)
{
    return playerId;
}

void GameClient::setPlayerId(int m_playerId)
{
    playerId = m_playerId;
}

void GameClient::setState(ClientState m_state)
{
    state = m_state;
}


std::string GameClient::getPlayerName(void)
{
    return playerName;
}

void GameClient::setPlayerName(std::string m_playerName)
{
    playerName = m_playerName;
}

void GameClient::addPlayer(std::string m_playerName)
{
    players.push_back(m_playerName);
}

void GameClient::clearPlayers(void)
{
    players.clear();
}

int GameClient_Loop(void *data_ptr)
{
    GameClient *client = static_cast<GameClient*>(data_ptr);

    //connecting to the game server
    UdpSocket socket;

    socket.open(0);

    IPaddress remote;

    SDLNet_ResolveHost(&remote, client->getHost().c_str(), client->getPort());
    std::cout << "Connecting to " << client->getHost() << ":" << client->getPort() << "..." << std::endl;
    int channel = socket.bind(-1, &remote);

    if(channel != -1)
    {
        client->setState(CS_Lobby);
        //ask for a player id

        UdpPacket packet (64);
        PacketStream stream = packet.stream();

        stream.writeInt32(STRData::MMP_PLAYER_JOIN);
        stream.writeString("PlayerName");

        socket.send(packet.packet(), channel);

        SDL_Delay(10);

        while(client->isRunning())
        {
            UdpPacket *recv = socket.recv();
            if(recv != nullptr)
            {
                PacketStream recvStream = recv->stream();
                STRData::MatchMasterPacket type = static_cast<STRData::MatchMasterPacket>(recvStream.readInt32());

                if(type == STRData::MMP_PLAYER_JOIN)
                {
                    //receiving our player id
                    int playerId = recvStream.readInt32();
                    client->setPlayerId(playerId);
                    std::cout << "Player Id received : " << playerId << std::endl;

                    //ask for the player list
                    UdpPacket respPacket(16);
                    PacketStream respStream = respPacket.stream();

                    respStream.writeInt32(STRData::MMP_PLAYER_LIST);

                    socket.send(respPacket.packet(), channel);

                }
                else if(type == STRData::MMP_PLAYER_LIST)
                {
                    client->clearPlayers();
                    //first var is the player count
                    //each player is stored into a string
                    int playerCount = recvStream.readInt32();
                    for(int i=0; i<playerCount; i++)
                    {
                        std::string playerName = recvStream.readString();
                        if(playerName != client->getPlayerName())
                        {
                            client->addPlayer(playerName);
                        }
                    }
                }
                else if(type == STRData::MMP_NEW_PLAYER)
                {
                    //new player in the lobby
                    std::string player_name = recvStream.readString();
                    std::cout << "New Player into the lobby " << player_name << std::endl;
                    client->addPlayer(player_name);
                }
            }

            SDL_Delay(10);
        }

        socket.unbind(channel);
    }

    socket.close();

    return 0;
}
