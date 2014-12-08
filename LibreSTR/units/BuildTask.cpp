#include "BuildTask.h"


BuildTask::BuildTask(MGroundUnit *m_unit, int m_buildSpeed, MBuilding *m_building, GameMap *m_map, StiGame::Point m_endPoint)
    : MoveTask(m_unit, m_map, m_endPoint)
{
    building = m_building;
    buildSpeed = m_buildSpeed;
}

BuildTask::~BuildTask()
{

}

void BuildTask::doStep(void)
{


    if(endPoint.equals(unit))
    {
        if(building->getCurrentHealth() < building->getMaxHealth())
        {
            caption = "Building";
            building->setCurrentHealth(building->getCurrentHealth() + 1);
            building->setState(BS_Construction);
        }
        else
        {
            building->setState(BS_Builded);
            terminated = true;
        }
    }
    else
    {
        MoveTask::doStep();
    }

    if(terminated && building->getCurrentHealth() != building->getMaxHealth())
    {
        terminated = false;
        stepSize = buildSpeed;
    }
}
