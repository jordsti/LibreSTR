#include "ToggleConsole.h"

ToggleConsole::ToggleConsole(StiGame::Gui::Item *m_item)
{
    name = "toggle_console";
    cooldown = 250;
    item = m_item;
}

ToggleConsole::~ToggleConsole()
{

}

void ToggleConsole::doAction(void)
{
    item->setVisible(!item->isVisible());
}
