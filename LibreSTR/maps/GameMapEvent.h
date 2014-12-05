#ifndef GAMEMAPEVENT_H
#define GAMEMAPEVENT_H
#include "Unit.h"

enum GameMapEventType {
    GMET_GroundUnitKilled,
    GMET_BuildingKilled
};

class GameMapEvent
{
public:
    GameMapEvent(GameMapEventType m_type, Unit *m_unit);
    virtual ~GameMapEvent();

    GameMapEventType getType(void);
    Unit* getUnit(void);

    int getId(void);
protected:

    GameMapEventType type;
    Unit *unit;

private:
    int _id;

    static int currentId;

    static int CurrentId(void);

};

#endif // GAMEMAPEVENT_H
