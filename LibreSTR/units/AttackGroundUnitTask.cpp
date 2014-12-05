#include "AttackGroundUnitTask.h"

AttackGroundUnitTask::AttackGroundUnitTask(MGroundUnit *m_unit, GameMap *m_map, MGroundUnit *m_target)
    : MoveTask(m_unit, map, StiGame::Point(m_target->getX(), m_target->getY()))
{
    target = m_target;
}

AttackGroundUnitTask::~AttackGroundUnitTask()
{

}

void AttackGroundUnitTask::doStep()
{
    if(!target->equals(&endPoint))
    {
        endPoint = StiGame::Point(target->getX(), target->getY());
    }

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
