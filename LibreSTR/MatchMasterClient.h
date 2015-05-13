#ifndef MATCHMASTERCLIENT_H
#define MATCHMASTERCLIENT_H

#include <list>
#include "Match.h"

class MatchMasterClient
{
public:
    MatchMasterClient(std::string m_host, int m_port);
    virtual ~MatchMasterClient();

    void fetchMatches(void);
    void addMatch(STRData::Match *match);
    std::string getHost(void);
    int getPort(void);

    void setCompleted(bool m_completed);
    bool isCompleted(void);

    std::list<STRData::Match*>& getMatches(void);

    STRData::Match* getMatchById(int matchId);

private:
    std::string host;
    int port;
    bool completed;
    std::list<STRData::Match*> matches;
};

int MatchMasterClient_FetchMatches(void *data_ptr);

#endif // MATCHMASTERCLIENT_H
