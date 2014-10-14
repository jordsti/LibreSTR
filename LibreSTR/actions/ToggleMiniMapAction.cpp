#include "ToggleMiniMapAction.h"

ToggleMiniMapAction::ToggleMiniMapAction(MiniMap *m_miniMap) : StiGame::TimedGameAction()
{
    cooldown = 250; //ms
    name = "show_minimap";
    miniMap = m_miniMap;
}

ToggleMiniMapAction::~ToggleMiniMapAction()
{

}


void ToggleMiniMapAction::doAction(void)
{
    bool nhide = !miniMap->isHide();
    miniMap->setHide(nhide);
}
