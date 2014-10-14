#ifndef TOGGLEMINIMAPACTION_H
#define TOGGLEMINIMAPACTION_H

#include <TimedGameAction.h>
#include "MiniMap.h"

class ToggleMiniMapAction :
        public StiGame::TimedGameAction
{
public:
    ToggleMiniMapAction(MiniMap *m_miniMap);
    virtual ~ToggleMiniMapAction();

protected:
    MiniMap *miniMap;
    void doAction(void);
};

#endif // TOGGLEMINIMAPACTION_H
