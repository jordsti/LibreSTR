#ifndef TOGGLECONSOLE_H
#define TOGGLECONSOLE_H

#include <Item.h>
#include <TimedGameAction.h>

class ToggleConsole :
        public StiGame::TimedGameAction
{
public:
    ToggleConsole(StiGame::Gui::Item *m_item);
    virtual ~ToggleConsole();

    void doAction(void);
private:
    StiGame::Gui::Item *item;


};

#endif // TOGGLECONSOLE_H
