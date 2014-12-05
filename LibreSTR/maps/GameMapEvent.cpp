#include "GameMapEvent.h"

int GameMapEvent::currentId = 0;

GameMapEvent::GameMapEvent(GameMapEventType m_type, Unit *m_unit)
{
    type = m_type;
    unit = m_unit;
    _id = CurrentId();
}

GameMapEvent::~GameMapEvent()
{

}

GameMapEventType GameMapEvent::getType(void)
{
    return type;
}

Unit* GameMapEvent::getUnit(void)
{
    return unit;
}

int GameMapEvent::CurrentId(void)
{
    currentId++;
    return currentId;
}

int GameMapEvent::getId(void)
{
    return _id;
}
