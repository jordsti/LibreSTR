#include "AttackBuildingTask.h"

AttackBuildingTask::AttackBuildingTask(MGroundUnit *m_unit, GameMap *m_map, MBuilding *m_target) :
    MoveTask(m_unit, m_map, m_target->middle())
{
    target = m_target;
}


AttackBuildingTask::~AttackBuildingTask()
{

}

void AttackBuildingTask::doStep(void)
{
    StiGame::Point targetMidPt = target->middle();
    StiGame::Point unitMidPt = unit->middle();
    double dist = unitMidPt.distanceWith(&targetMidPt);

    if(dist <= unit->getAttackRange() + (target->getWidth()/2))
    {
        if(stepSize != unit->getAttackSpeed())
        {
            stepSize = unit->getAttackSpeed();
        }

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
        if(stepSize != unit->getIdentity()->getMovementSpeed())
        {
            stepSize = unit->getIdentity()->getMovementSpeed();
        }

        MoveTask::doStep();

        if(terminated)
        {
            terminated = false;
            stepSize = unit->getAttackSpeed();
        }
    }

}
