#include "MatchMasterClient.h"
#include <UdpSocket.h>
#include <PacketStream.h>
#include <SGThread.h>
#include <iostream>

MatchMasterClient::MatchMasterClient(std::string m_host, int m_port)
{
    host = m_host;
    port = m_port;
    completed = true;
}

MatchMasterClient::~MatchMasterClient()
{

}

void MatchMasterClient::addMatch(STRData::Match *match)
{
    matches.push_back(match);
}

void MatchMasterClient::fetchMatches(void)
{
    if(completed)
    {
        completed = false;
        StiGame::Thread *thread = new StiGame::Thread(&MatchMasterClient_FetchMatches, "fetch matches", this);
    }
}

std::string MatchMasterClient::getHost(void)
{
    return host;
}

int MatchMasterClient::getPort(void)
{
    return port;
}

void MatchMasterClient::setCompleted(bool m_completed)
{
    completed = m_completed;
}

bool MatchMasterClient::isCompleted(void)
{
    return completed;
}

std::list<STRData::Match*>& MatchMasterClient::getMatches(void)
{
    return matches;
}

int MatchMasterClient_FetchMatches(void *data_ptr)
{
    std::cout << "Fetch Matches Thread started" << std::endl;
    MatchMasterClient *client = static_cast<MatchMasterClient*>(data_ptr);
    StiGame::Net::UdpSocket socket;
    IPaddress master;

    SDLNet_ResolveHost(&master, client->getHost().c_str(), client->getPort());

    socket.open(0);

    int channel = socket.bind(-1, &master);

    if(channel != -1)
    {
        //Fetch Request
        StiGame::Net::UdpPacket request (32);
        request.stream().writeInt32(STRData::MMP_FETCH);
        socket.send(request.packet(), channel);
        int tick=0;
        while(true)
        {
            StiGame::Net::UdpPacket *packet = socket.recv();
            if(packet != nullptr)
            {
                StiGame::Net::PacketStream stream = packet->stream();
                STRData::MatchMasterPacket type = static_cast<STRData::MatchMasterPacket>(stream.readInt32());
                if(type == STRData::MMP_MATCH)
                {
                    /*
                     *   stream.writeInt32(MMP_MATCH);
                     *   stream.writeInt32(match->getId());
                     *   stream.writeString(match->getName());
                     *   stream.writeString(match->getHost());
                     *   stream.writeInt32(match->getCurrentPlayers());
                     *   stream.writeInt32(match->getMaxPlayers());
                     *   stream.writeInt32(match->getPort());
                     *   stream.writeBool(match->isPasswordProtected());
                    */
                    //reading match info
                    STRData::Match *match = new STRData::Match();
                    match->setId(stream.readInt32());
                    match->setName(stream.readString());
                    match->setHost(stream.readString());
                    match->setCurrentPlayers(stream.readInt32());
                    match->setMaxPlayers(stream.readInt32());
                    match->setPort(stream.readInt32());
                    match->setPasswordProtected(stream.readBool());

                    client->addMatch(match);
                    std::cout << "Match received!" << std::endl;
                }
                else if(type == STRData::MMP_END)
                {
                    std::cout << "End received !" << std::endl;
                    break;
                }
            }

            tick++;
            SDL_Delay(5);
            if(tick > 10000)
            {
                break;
            }
        }
    }

    client->setCompleted(true);
    socket.close();
    std::cout << "Fetch Matches thread ended" << std::endl;
    return 1;
}
