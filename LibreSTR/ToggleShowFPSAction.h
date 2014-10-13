#ifndef TOGGLESHOWFPSACTION_H
#define TOGGLESHOWFPSACTION_H

#include <TimedGameAction.h>
#include <Label.h>

class ToggleShowFPSAction :
        public StiGame::TimedGameAction
{
public:
    ToggleShowFPSAction(StiGame::Gui::Label *m_lblFps);
    virtual ~ToggleShowFPSAction();
protected:
    void doAction(void);
    StiGame::Gui::Label *lblFps;
};

#endif // TOGGLESHOWFPSACTION_H
