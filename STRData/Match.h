#ifndef MATCH_H
#define MATCH_H

#include <iostream>
#include <string>

namespace STRData
{

enum MatchMasterPacket {
    MMP_FETCH,
    MMP_REGISTER,
    MMP_REMOVE,
    MMP_MATCH,
    MMP_END,
    MMP_PLAYER_JOIN,
    MMP_MATCH_UPDATE,
    MMP_PLAYER_LIST,
    MMP_NEW_PLAYER,
    MMP_MATCH_INFO
};

const int MATCH_MASTER_PORT = 6000;

class Match
{
public:
    Match();
    virtual ~Match();

    void setId(int m_id);
    int getId(void);

    void setCurrentPlayers(int m_currentPlayers);
    int getCurrentPlayers(void);

    void setMaxPlayers(int m_maxPlayers);
    int getMaxPlayers(void);

    void setName(std::string m_name);
    std::string getName(void);

    void setPasswordProtected(bool m_passwordProtected);
    bool isPasswordProtected(void);

    void setHost(std::string m_host);
    std::string getHost(void);

    void setPort(int m_port);
    int getPort(void);

private:
    int id;
    int currentPlayers;
    int maxPlayers;
    std::string name;
    bool passwordProtected;
    std::string host;
    int port;
};

}

#endif // MATCH_H
