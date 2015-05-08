#ifndef MATCHMASTER_H
#define MATCHMASTER_H

#include <UdpPacket.h>
#include "Match.h"
#include <list>
#include <vector>

struct FetchState {
    std::vector<STRData::Match*> matches;
    IPaddress destination;
};

class MatchMaster
{
public:
    MatchMaster();
    virtual ~MatchMaster();

    void start(void);
    void handlePacket(StiGame::Net::UdpPacket *packet);

    void addMatch(STRData::Match *match);
private:
    std::list<STRData::Match*> matches;
    std::list<STRData::Match*> deleted;
    int currentMatchId;
};

int MatchMaster_SendMatches(void *data_ptr);

#endif // MATCHMASTER_H
