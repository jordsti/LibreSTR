#include "Match.h"
namespace STRData
{

Match::Match()
{
    id = 0;
    name = "";
    currentPlayers = 0;
    maxPlayers = 0;
    passwordProtected = false;
    port = 0;
    host = "";
}

Match::~Match()
{

}

void Match::setId(int m_id)
{
    id = m_id;
}

int Match::getId(void)
{
    return id;
}

void Match::setCurrentPlayers(int m_currentPlayers)
{
    currentPlayers = m_currentPlayers;
}

int Match::getCurrentPlayers(void)
{
    return currentPlayers;
}

void Match::setMaxPlayers(int m_maxPlayers)
{
    maxPlayers = m_maxPlayers;
}

int Match::getMaxPlayers(void)
{
    return maxPlayers;
}

void Match::setName(std::string m_name)
{
    name = m_name;
}

std::string Match::getName(void)
{
    return name;
}

void Match::setPasswordProtected(bool m_passwordProtected)
{
    passwordProtected = m_passwordProtected;
}

bool Match::isPasswordProtected(void)
{
    return passwordProtected;
}

void Match::setHost(std::string m_host)
{
    host = m_host;
}

std::string Match::getHost(void)
{
    return host;
}

void Match::setPort(int m_port)
{
    port = m_port;
}

int Match::getPort(void)
{
    return port;
}

}
