#include "GameOverlay.h"

using namespace StiGame;

GameOverlay::GameOverlay() :
    Gui::OverlayMenu()
{
    //ctor
    state = nullptr;

    resumeButton.setCaption("Resume");
    quitButton.setCaption("Quit");

    resumeButton.subscribe(this);
    quitButton.subscribe(this);

    add(&resumeButton);
    add(&quitButton);
}

GameOverlay::~GameOverlay()
{
    //dtor
}


void GameOverlay::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args)
{
    if(src == &resumeButton)
    {
        visible = false;
    }
    else if(src == &quitButton)
    {
        state->closeGameMenu();
        state->quit();
    }
}

void GameOverlay::setState(GameState *m_state)
{
    state = m_state;
}
