#include "CreateUnitJob.h"
#include <iostream>

CreateUnitJob::CreateUnitJob(MPlayer *m_player, Building *m_srcBuilding, GroundUnitIdentity *m_identity, GameMap *m_gameMap) :
    Job("Create Unit")
{
    timeNeeded = m_identity->getProductionTime();
    player = m_player;
    srcBuilding = m_srcBuilding;
    identity = m_identity;
    gameMap = m_gameMap;
}

CreateUnitJob::~CreateUnitJob()
{

}

void CreateUnitJob::onComplete(void)
{
    //placing the unit here

    int pt_x = 0;
    int pt_y = 0;

    MGroundUnit *unit = identity->create(player);

    pt_x = srcBuilding->getX();
    pt_y = srcBuilding->getY();

    int t_w = srcBuilding->getWidth() / Tile::TILE_WIDTH;
    int t_h = srcBuilding->getHeight() / Tile::TILE_HEIGHT;

    int i_x = 0;
    int i_y = 0;

    int step = 0;

    while(!gameMap->placeGroundUnit(unit, pt_x, pt_y))
    {
        int i_step = step % 3;
        // 0 -> adding for i_x or i_y
        // 1 -> using -1*i_x
        // 2 -> using -1*i_y

        int m_x = 1;
        int m_y = 1;

        if(i_step == 0)
        {
            if(i_x == 0)
            {
                i_x = t_w;
            }
            else if(i_y == 0)
            {
                i_y = t_h;
            }
            else if(i_x > i_y)
            {
                i_y++;
            }
            else
            {
                i_x++;
            }
        }
        else if(i_step == 1)
        {
            m_x = -1;
        }
        else if(i_step == 2)
        {
            m_y = -1;
        }

        pt_x = pt_x + (i_x * Tile::TILE_WIDTH * m_x);
        pt_y = pt_y + (i_y * Tile::TILE_HEIGHT * m_y);
        step++;
    }

    //int pop = player->getCurrentPopulation() - identity->getPopulationCost();
    //player->setCurrentPopulation(pop);
    //debug output
    //std::cout << "Unit placed at : " << pt_x << "; " << pt_y << std::endl;
}

void CreateUnitJob::onCancel(void)
{
    int metalCount = player->getMetalCount() + identity->getMetalCost();
    int gazCount = player->getGazCount() + identity->getGazCost();
    //int pop = player->getCurrentPopulation() - identity->getPopulationCost();
    player->setMetalCount(metalCount);
    player->setGazCount(gazCount);
    //player->setCurrentPopulation(pop);
}

void CreateUnitJob::onStart(void)
{
    int metalCount = player->getMetalCount() - identity->getMetalCost();
    int gazCount = player->getGazCount() - identity->getGazCost();
    //int tmpPop = player->getCurrentPopulation() + identity->getPopulationCost();
    player->setMetalCount(metalCount);
    player->setGazCount(gazCount);
    //player->setCurrentPopulation(tmpPop);
}
