#ifndef GAMEOVERLAY_H
#define GAMEOVERLAY_H
#include <OverlayMenu.h>
#include <Button.h>
#include <EventListener.h>
#include "GameState.h"


class GameOverlay :
    public StiGame::Gui::OverlayMenu,
    public StiGame::EventListener
{
    public:
        GameOverlay();
        virtual ~GameOverlay();
        void handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args);
        void setState(GameState *m_state);
    protected:
        StiGame::Gui::Button resumeButton;
        StiGame::Gui::Button quitButton;
        GameState *state;
    private:
};

#endif // GAMEOVERLAY_H
