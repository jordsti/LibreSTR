#include "AttackBuildingTask.h"

AttackBuildingTask::AttackBuildingTask(MGroundUnit *m_unit, GameMap *m_map, MBuilding *m_target) :
    MoveTask(m_unit, m_map, StiGame::Point())
{
    target = m_target;
    endPoint = m_target->middle();
}


AttackBuildingTask::~AttackBuildingTask()
{

}

void AttackBuildingTask::doStep(void)
{
    StiGame::Point targetMidPt = target->middle();
    StiGame::Point unitMidPt = unit->middle();
    double dist = unitMidPt.distanceWith(&targetMidPt);

    if(dist <= unit->getAttackRange())
    {
        caption = "Attacking";

        if(target->getCurrentHealth() > 0)
        {
            int cur_hp = target->getCurrentHealth();
            int n_hp = cur_hp - unit->getAttackDamage();
            if(n_hp < 0)
            {
                n_hp = 0;
            }

            target->setCurrentHealth(n_hp);

            if(n_hp == 0)
            {
                terminated = true;
            }
        }
    }
    else
    {
        MoveTask::doStep();

        if(terminated)
        {
            terminated = false;
        }
    }

}
