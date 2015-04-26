#include "HarvestTask.h"


HarvestTask::HarvestTask(MGroundUnit *m_unit, MPlayer *m_player, GameMap *m_map, StiGame::Point m_endPoint) :
    MoveTask(m_unit, m_map, m_endPoint)
{
    name = "HarvestTask";
    stepSize = unit->getIdentity()->getMovementSpeed();
    //step size when we are at the point
    harvestSpeed = unit->getIdentity()->getHarvestSpeed();
    player = m_player;
    harvestRange = unit->getIdentity()->getHarvestRange();
    currentResources = 0;
    resourcesLimit = unit->getIdentity()->getHarvestSpeed();
    state = HS_MovingToResource;
    resourceType = RT_NOT_DEFINED;
    resourcePoint.setPoint(&m_endPoint);
    depot = nullptr;
    depot = findNearestDepot(m_map, m_unit);
}

HarvestTask::~HarvestTask()
{

}

Building* HarvestTask::findNearestDepot(GameMap *m_map, GroundUnit *m_unit)
{
    Building *depot = nullptr;
    double dist = 20000;
    StiGame::Point unitMid = m_unit->middle();

    for(int i=0; i<m_map->getBuildingsCount(); i++)
    {
        Building *b = m_map->getBuilding(i);
        double b_dist = unitMid.distanceWith(b);
        if(b->getBuildingType() == BT_Base && b_dist < dist)
        {
            depot = b;
            dist = b_dist;
        }
    }

    return depot;

}

void HarvestTask::doStep(void)
{
    if(state == HS_Harvesting)
    {
        caption = "Harvesting";
        stepSize = harvestSpeed;
        if(currentResources < resourcesLimit)
        {
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
                    if(resourceType != res->getType())
                    {
                        currentResources = 0;
                        resourceType = res->getType();
                    }

                    currentResources += 1;

                }
                else
                {
                    //maybe remove the resource
                }
            }
        }
        else
        {
            state = HS_MovingToDepot;
            endPoint = StiGame::Point(depot->middle());
        }
    }
    else if(state == HS_MovingToDepot)
    {
        if(depot == nullptr)
        {
            terminated = true;
            return;
        }

        caption = "Moving to depot";
        MoveTask::doStep();
        stepSize = unit->getIdentity()->getMovementSpeed();
        StiGame::Point dMid = depot->middle();
        if(unit->distanceWith(&dMid) <= harvestRange)
        {
            state = HS_MovingToResource;
            endPoint = StiGame::Point(&resourcePoint);

            if(resourceType == RT_METAL)
            {
                player->setMetalCount(player->getMetalCount() + currentResources);
            }
            else if(resourceType == RT_GAZ)
            {
                player->setGazCount(player->getGazCount() + currentResources);
            }

            currentResources = 0;
        }
    }
    else if(state == HS_MovingToResource)
    {
        caption = "Moving to resource";
        MoveTask::doStep();
        stepSize = unit->getIdentity()->getMovementSpeed();
        double dist = unit->distanceWith(&resourcePoint);
        std::cout << dist << std::endl;
        if(dist <= harvestRange)
        {
            state = HS_Harvesting;

        }
    }

    if(terminated)
    {
        stepSize = harvestSpeed;
        //this task never terminate
        terminated = false;
    }

    if(depot == nullptr)
    {
        terminated = true;
    }
}
