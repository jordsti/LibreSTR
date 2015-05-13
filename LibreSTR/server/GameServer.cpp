#include "GameServer.h"
#include "Match.h"
#include <PacketStream.h>
#include <iostream>

using namespace StiGame;
using namespace Net;

GameServer::GameServer(std::string m_gameName) :
    dispatcher(DEFAULT_GAME_SERVER_PORT)
{
    currentPlayerId = 0;
    matchId = -1;
    port = DEFAULT_GAME_SERVER_PORT;
    gameName = m_gameName;
    dispatcher.setHandler(this);
    maxPlayers = 8;
    loadAssets();
}

GameServer::GameServer(std::string m_gameName, int m_port) :
    dispatcher(m_port)
{
    currentPlayerId = 0;
    matchId = -1;
    port = m_port;
    gameName = m_gameName;
    dispatcher.setHandler(this);
    maxPlayers = 8;
    loadAssets();
}

GameServer::~GameServer()
{

}

void GameServer::setMaxPlayers(int m_maxPlayers)
{
    maxPlayers = m_maxPlayers;
}

void GameServer::loadAssets(void)
{
    assets = new AssetManager();
}

void GameServer::readPacket(UdpPacket *packet)
{
    PacketStream stream = packet->stream();
    STRData::MatchMasterPacket type = static_cast<STRData::MatchMasterPacket>(stream.readInt32());
    if(type == STRData::MMP_MATCH)
    {
        matchId = stream.readInt32();
        std::cout << "Game Server registered to the master server with id : " << matchId << std::endl;
    }
    else if(type == STRData::MMP_PLAYER_JOIN)
    {
        std::string player_name = stream.readString();

        if(players.size() < maxPlayers - 1)
        {
            currentPlayerId++;
            PlayerConnection *pCon = new PlayerConnection();
            pCon->playerName = player_name;
            pCon->playerId = currentPlayerId;

            std::string host (SDLNet_ResolveIP(packet->ipAddress()));

            pCon->host = host;
            pCon->port = packet->ipAddress()->port;

            players.push_back(pCon);

            //todo
            //must update master server

            UdpPacket *respPacket = new UdpPacket(64);
            PacketStream respStream = respPacket->stream();
            respStream.writeInt32(STRData::MMP_PLAYER_JOIN);
            respStream.writeInt32(pCon->playerId);
            packet->applyAddress(packet->ipAddress());

            //sending player id to player
            dispatcher.sendPacket(packet);

            //updating master server
            UdpPacket masterUpdate (64);
            PacketStream mStream = masterUpdate.stream();
            mStream.writeInt32(STRData::MMP_MATCH_UPDATE);
            mStream.writeInt32(matchId);
            mStream.writeInt32(players.size());

            masterSocket.send(masterUpdate.packet(), masterChannel);
        }
    }
}

void GameServer::start(void)
{
    //server loop gonna be there at the moments
    dispatcher.start();
    //registering to the master server

    SDL_Delay(20);

    masterSocket.open(0);

    IPaddress addr;
    SDLNet_ResolveHost(&addr, assets->getMasterServer().c_str(), STRData::MATCH_MASTER_PORT);
    masterChannel = masterSocket.bind(-1, &addr);

    if(masterChannel != -1)
    {
        UdpPacket registerPacket (128);

        /* int port = stream.readInt32();
         * std::string name = stream.readString();
         * int curPlayers = stream.readInt32();
         * int maxPlayers = stream.readInt32();
         * bool passwordProtected = stream.readBool();
        */
        PacketStream stream = registerPacket.stream();
        stream.writeInt32(STRData::MMP_REGISTER);
        stream.writeInt32(port);
        stream.writeString(gameName);
        stream.writeInt32(0);
        stream.writeInt32(maxPlayers);
        stream.writeBool(false);

        masterSocket.send(registerPacket.packet(), masterChannel);
    }

    while(dispatcher.isRunning())
    {
        SDL_Delay(10);
    }
}

void GameServer::stop(void)
{

    masterSocket.unbind(masterChannel);
    masterSocket.close();

    dispatcher.stop();
}
