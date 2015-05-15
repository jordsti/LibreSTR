#ifndef LOBBYSTATE_H
#define LOBBYSTATE_H

#include <GuiState.h>

#include <Button.h>
#include <Label.h>
#include <EventListener.h>
#include "AssetManager.h"
#include "GameClient.h"

class LobbyState :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener
{
public:
    LobbyState(AssetManager *m_assets, std::string m_serverAddr, int m_serverPort);
    virtual ~LobbyState();

    void onStart(void);

    void onResize(int m_width, int m_height);

    bool handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt);

    GameClient* getClient(void);

    void onPaint(SDL_Renderer *renderer);

protected:
    GameClient *client;

    StiGame::Gui::Label lblTitle;
    StiGame::Gui::Label lblGameName;
    StiGame::Gui::Label lblMaxPlayers;
    StiGame::Gui::Label lblCurrentPlayers;

    StiGame::Gui::Button btnBack;

    std::string serverAddr;
    int serverPort;

    AssetManager *assets;

private:
    void initComponents(void);

};

#endif // LOBBYSTATE_H
