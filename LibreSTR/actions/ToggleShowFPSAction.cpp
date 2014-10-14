#include "ToggleShowFPSAction.h"

ToggleShowFPSAction::ToggleShowFPSAction(StiGame::Gui::Label *m_lblFps)
{
    name = "show_fps";
    cooldown = 250;
    lblFps = m_lblFps;
}

ToggleShowFPSAction::~ToggleShowFPSAction()
{

}

void ToggleShowFPSAction::doAction(void)
{
    lblFps->setVisible(!lblFps->isVisible());
}

