#ifndef TOGGLEMINIMAPACTION_H
#define TOGGLEMINIMAPACTION_H

#include <TimedGameAction.h>
#include "GameState.h"

class ToggleMiniMapAction :
        public StiGame::TimedGameAction
{
public:
    ToggleMiniMapAction(GameState *m_state);
    virtual ~ToggleMiniMapAction();

protected:
    GameState *state;
    void doAction(void);
};

#endif // TOGGLEMINIMAPACTION_H
