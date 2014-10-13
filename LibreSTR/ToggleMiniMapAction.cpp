#include "ToggleMiniMapAction.h"

ToggleMiniMapAction::ToggleMiniMapAction(GameState *m_state) : StiGame::BaseGameAction()
{
    name = "show_minimap";
    state = m_state;
}

ToggleMiniMapAction::~ToggleMiniMapAction()
{

}


void ToggleMiniMapAction::doAction(void)
{
    MiniMap *miniMap = state->getMiniMap();
    bool nhide = !miniMap->isHide();
    miniMap->setHide(nhide);
}
