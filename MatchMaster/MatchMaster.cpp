#include "MatchMaster.h"
#include <UdpSocket.h>
#include <PacketStream.h>
#include <iostream>
#include <SGThread.h>
using namespace StiGame;
using namespace Net;
using namespace STRData;
MatchMaster::MatchMaster()
{
    currentMatchId = 0;
}

MatchMaster::~MatchMaster()
{

}

void MatchMaster::start(void)
{
    UdpSocket socket;

    socket.open(MATCH_MASTER_PORT);

    std::cout << "Opening Master server on " << MATCH_MASTER_PORT << std::endl;

    while(true)
    {
        UdpPacket *packet = socket.recv();
        if(packet != nullptr)
        {
            handlePacket(packet);
            delete packet;
        }

    }

    socket.close();
}

void MatchMaster::handlePacket(UdpPacket *packet)
{
    PacketStream stream = packet->stream();

    //reading packet type
    int i_type = stream.readInt32();

    MatchMasterPacket type = static_cast<MatchMasterPacket>(i_type);

    if(type == MMP_FETCH)
    {
        //starting a new thread a send all current matches
        FetchState *state = new FetchState();
        packet->copyAddress(&state->destination);

        auto lit(matches.begin()), lend(matches.end());
        for(;lit!=lend;++lit)
        {
            Match *m = (*lit);
            state->matches.push_back(m);
        }

        Thread *thread = new Thread(&MatchMaster_SendMatches, "Fetch Response", state);
    }
    else if(type == MMP_REGISTER)
    {
        std::string name = stream.readString();
        int curPlayers = stream.readInt32();
        int maxPlayers = stream.readInt32();
        bool passwordProtected = stream.readBool();

        IPaddress remote;
        packet->copyAddress(&remote);
        Match *match = new Match();

        currentMatchId++;

        match->setId(currentMatchId);

        std::string host_str (SDLNet_ResolveIP(&remote));

        match->setHost(host_str);
        match->setPort(remote.port);

        match->setName(name);
        match->setCurrentPlayers(curPlayers);
        match->setMaxPlayers(maxPlayers);
        match->setPasswordProtected(passwordProtected);

        matches.push_back(match);

    }
    else if(type == MMP_REMOVE)
    {
        int id = stream.readInt32();
        IPaddress remote;
        packet->copyAddress(&remote);

        std::string m_host (SDLNet_ResolveIP(&remote));

        Match *m = nullptr;
        auto lit(matches.begin()), lend(matches.end());
        for(;lit!=lend;++lit)
        {
            Match *im = (*lit);
            if(im->getId() == id && im->getPort() == remote.port && im->getHost() == m_host)
            {
                m = im;
                break;
            }
        }

        if(m != nullptr)
        {
            matches.remove(m);
            deleted.push_back(m);
        }
    }
}

void MatchMaster::addMatch(STRData::Match *match)
{
    matches.push_back(match);
}


int MatchMaster_SendMatches(void *data_ptr)
{
    FetchState *state = static_cast<FetchState*>(data_ptr);
    UdpSocket socket;

    std::cout << "Sending matches list" << std::endl;
    socket.open(0);

    int channel = socket.bind(-1, &state->destination);

    if(channel != -1)
    {
        auto lit(state->matches.begin()), lend(state->matches.end());
        for(;lit!=lend;++lit)
        {
            Match *match = (*lit);
            UdpPacket toSend (256);
            PacketStream stream = toSend.stream();

            stream.writeInt32(MMP_MATCH);
            stream.writeInt32(match->getId());
            stream.writeString(match->getName());
            stream.writeString(match->getHost());
            stream.writeInt32(match->getCurrentPlayers());
            stream.writeInt32(match->getMaxPlayers());
            stream.writeString(match->getHost());
            stream.writeInt32(match->getPort());
            stream.writeBool(match->isPasswordProtected());

            socket.send(toSend.packet(), channel);

            SDL_Delay(10);
        }

        UdpPacket endPacket (32);
        PacketStream endStream = endPacket.stream();
        endStream.writeInt32(MMP_END);

        socket.send(endPacket.packet(), channel);

        socket.unbind(channel);
    }
    else
    {
        std::cout << "[MatchMaster_SendMatches] Error while binding the socket" << std::endl;
    }

    socket.close();
    delete state;
    return 1;
}
