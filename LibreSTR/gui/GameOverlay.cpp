#include "GameOverlay.h"
#include "MainMenu.h"

using namespace StiGame;

GameOverlay::GameOverlay() :
    Gui::OverlayMenu()
{
    //ctor
    state = nullptr;

    resumeButton.setCaption("Resume");
    quitToMenuButton.setCaption("Quit to Menu");
    quitButton.setCaption("Quit");

    resumeButton.subscribe(this);
    quitToMenuButton.subscribe(this);
    quitButton.subscribe(this);

    width = 200;

    add(&resumeButton);
    add(&quitToMenuButton);
    add(&quitButton);
}

GameOverlay::~GameOverlay()
{
    //dtor
}


bool GameOverlay::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args)
{
    if(src == &resumeButton)
    {
        visible = false;
    }
    else if(src == &quitToMenuButton)
    {
        MainMenu *mm = new MainMenu(state->getAssets());

        Viewport *vp = state->getViewport();
        vp->push(mm);

        //delete state;

    }
    else if(src == &quitButton)
    {
        state->closeGameMenu();
        state->quit();
    }

    return false;
}

void GameOverlay::setState(GameState *m_state)
{
    state = m_state;
}
