#include "HarvestTask.h"


HarvestTask::HarvestTask(MGroundUnit *m_unit, MPlayer *m_player, int m_harvestSpeed, GameMap *m_map, StiGame::Point m_endPoint) :
    MoveTask(m_unit, m_map, m_endPoint)
{
    name = "HarvestTask";
    stepSize = unit->getIdentity()->getMovementSpeed();
    //step size when we are at the point
    harvestSpeed = m_harvestSpeed;
    player = m_player;
}

HarvestTask::~HarvestTask()
{

}

void HarvestTask::doStep(void)
{
    if(unit->equals(&endPoint))
    {
        if(caption != "Harvesting")
        {
            caption = "Harvesting";
        }

        stepSize = harvestSpeed;
        //harvest

        StiGame::Point tilePt (unit->getX() / Tile::TILE_WIDTH, unit->getY() / Tile::TILE_HEIGHT);
        Tile *tile = map->get(tilePt);

        if(tile->containsResource())
        {
            Resource *res = tile->getResource();
            if(res->getAmount() > 0)
            {
                //harvestAmount must be put into assets.def !
                //todo
                int namount = res->getAmount() - 1;
                res->setAmount(namount);

                if(res->getType() == RT_METAL)
                {
                    player->setMetalCount(player->getMetalCount() + 1);
                }
                else if(res->getType() == RT_GAZ)
                {
                    player->setGazCount(player->getGazCount() + 1);
                }

            }
            else
            {
                //maybe remove the resource
            }
        }

    }
    else
    {
        //moving
        MoveTask::doStep();

        if(terminated)
        {
            stepSize = harvestSpeed;
            //this task never terminate
            terminated = false;
        }
    }
}
