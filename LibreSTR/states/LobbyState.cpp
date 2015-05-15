#include "LobbyState.h"
#include "MatchBrowser.h"
LobbyState::LobbyState(AssetManager *m_assets, std::string m_serverAddr, int m_serverPort)
{
    assets = m_assets;
    serverAddr = m_serverAddr;
    serverPort = m_serverPort;

    client = new GameClient(serverAddr, serverPort);

    initComponents();
}

LobbyState::~LobbyState()
{

}

void LobbyState::initComponents(void)
{
    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("Game Lobby");

    lblGameName.setCaption("Name : ");
    lblMaxPlayers.setCaption("Max players : ");
    lblCurrentPlayers.setCaption("Current players : ");

    btnBack.setCaption("Back");

    add(&btnBack);
    add(&lblTitle);
    add(&lblGameName);
    add(&lblMaxPlayers);
    add(&lblCurrentPlayers);
}

GameClient* LobbyState::getClient(void)
{
    return client;
}

bool LobbyState::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt)
{
    if(src == &btnBack)
    {
        client->stop();
        MatchBrowser *state = new MatchBrowser(assets);
        viewport->push(state);
    }

    return true;
}

void LobbyState::onStart(void)
{
    running = true;
    client->start();
}

void LobbyState::onPaint(SDL_Renderer *renderer)
{
    if(client->isMatchInfoReceived())
    {
        lblGameName.setCaption("Name : "+client->getMatch()->getName());
        lblMaxPlayers.setCaption("Max players : "+std::to_string(client->getMatch()->getMaxPlayers()));
        lblCurrentPlayers.setCaption("Current players : "+std::to_string(client->getMatch()->getCurrentPlayers()));
    }


    GuiState::onPaint(renderer);
}

void LobbyState::onResize(int m_width, int m_height)
{
    btnBack.prerender();
    btnBack.setPoint(16, m_height - btnBack.getHeight() - 8);

    lblTitle.setPoint(8, 16);
    lblTitle.prerender();

    lblGameName.setPoint(8, lblTitle.getY() + lblTitle.getHeight() + 10);
    lblGameName.prerender();
    lblMaxPlayers.setPoint(lblGameName.getX(), lblGameName.getY() + lblGameName.getHeight() + 5);
    lblMaxPlayers.prerender();
    lblCurrentPlayers.setPoint(lblGameName.getX(), lblMaxPlayers.getY() + lblMaxPlayers.getHeight() + 5);

    GuiState::onResize(m_width, m_height);
}
