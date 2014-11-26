#include "GameObject.h"
#include "MapGenerator.h"
#include <iostream>
#include <map>
#include "MBuilding.h"
#include "CreateUnitEmitter.h"
#include <TimeTools.h>
#include "MoveTask.h"
#include "HarvestTask.h"

using namespace StiGame;

GameObject::GameObject(AssetManager *m_assets, int mapWidth, int mapHeight, ILogStream *m_logStream)
{
    assets = m_assets;
    //generating a random map by default
    MapGenerator::setAssets(assets);
    map = MapGenerator::RandomMap(mapWidth, mapHeight);

    //generating player

    players.push_back(new MPlayer(PC_Blue));
    players.push_back(new MPlayer(PC_Red));

    logStream = m_logStream;

    lastTickMs = 0;
}

GameObject::~GameObject()
{
    //some cleaning todo
    delete map;

    delete playerMaps[1];
    delete playerMaps[2];
    delete players[0];
    delete players[1];
}

void GameObject::tick(void)
{
    //game tick
    if(lastTickMs == 0)
    {
        lastTickMs = StiGame::Time::GetMsTimestamp();
        return;
    }

    long long _now = StiGame::Time::GetMsTimestamp();
    int _delta = (int)(_now - lastTickMs);
    lastTickMs = _now;

    map->tickUnits(_delta);

    //ticking players maps
    auto mit(playerMaps.begin()), mend(playerMaps.end());
    for(;mit!=mend; ++mit)
    {
        Player *player = getPlayer(mit->first);
        PlayerMap *pmap = mit->second;

        pmap->cleanUnits();

        int uc = map->getGroundUnitsCount();
        int bc = map->getBuildingsCount();

        for(int i=0; i<uc; i++)
        {
            MGroundUnit *gu = map->getGroundUnit(i);
            if(gu->getOwner() != player)
            {
                StiGame::Point mpt = gu->middle();

                if(pmap->isPointVisible(&mpt))
                {
                    //this unit is visible
                    pmap->addGroundUnit(gu);
                }
            }
        }

        for(int i=0; i<bc; i++)
        {
            MBuilding *b = map->getBuilding(i);
            if(b->getOwner() != player)
            {
                StiGame::Point mpt = b->middle();
                if(pmap->isPointVisible(&mpt))
                {
                    pmap->addBuilding(b);
                }
            }
        }

    }

}

void GameObject::moveGroundUnit(Unit *groundUnit, StiGame::Point *targetPt)
{
    MGroundUnit *_unit = map->getGroundUnitById(groundUnit->getId());
    if(_unit != nullptr)
    {
        MoveTask *moveTask = new MoveTask(_unit, map, StiGame::Point(targetPt->getX(), targetPt->getY()));
        logStream->pushLine("Moving unit : " +
                            _unit->getName() +
                            "; " + std::to_string(_unit->getId()) +
                            ", target : "+std::to_string(targetPt->getX())+
                            "; "+std::to_string(targetPt->getY())
                            );
        _unit->pushTask(moveTask);
    }
}

MPlayer* GameObject::getMPlayer(int id)
{
    auto vit(players.begin()), vend(players.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getId() == id)
        {
            return (*vit);
        }
    }

    return nullptr;
}

void GameObject::harvestResource(Unit *groundUnit, StiGame::Point *targetPt)
{
    MGroundUnit *_unit = map->getGroundUnitById(groundUnit->getId());
    MPlayer *player = getMPlayer(_unit->getOwner()->getId());
    if(_unit != nullptr)
    {
        if(_unit->getIdentity()->isCanHarvest())
        {
            HarvestTask *harvestTask = new HarvestTask(_unit, player, assets->getHarvestSpeed(), map, StiGame::Point(targetPt->getX(), targetPt->getY()));
            logStream->pushLine("Harvest resource : " +
                                _unit->getName() +
                                "; " + std::to_string(_unit->getId()) +
                                ", target : "+std::to_string(targetPt->getX())+
                                "; "+std::to_string(targetPt->getY())
                                );
            _unit->pushTask(harvestTask);
        }
    }
}

void GameObject::initGame(void)
{
    /*
     *  Placing building and player starting unit
     *  Generate Player Map
     *  be ready for starting the Game
     *
     */
    logStream->pushLine("Initializing game...");

    BuildingIdentity *baseId = assets->getBaseIdentity();
    GroundUnitIdentity *workerId = assets->getWorkerIdentity();
    std::map<MPlayer*, Point> playerStartPts;

    auto vit(players.begin()), vend(players.end());
    for(;vit!=vend;++vit)
    {
        std::vector<Point> startingPoints = map->getPlayerStartingPoints((*vit)->getId());

        int p = rand() % startingPoints.size();

        Point ps = startingPoints[p];

        playerStartPts.insert(std::make_pair((*vit), ps));
    }

    logStream->pushLine("Choosing players starting point");

    //placing units
    auto mit(playerStartPts.begin()), mend(playerStartPts.end());
    for(;mit!=mend;++mit)
    {
        MPlayer *pl = mit->first;
        Point ptStart = mit->second;

        //base building
        MBuilding *base = baseId->create(pl);
        //adding worker emitter

        CreateUnitEmitter *workerEmitter = new CreateUnitEmitter(pl, assets->getWorkerIdentity(), map);
        base->addEmitter(workerEmitter);
        base->setState(BS_Builded);
        base->setCurrentHealth(baseId->getMaxHealth());
        map->forcePlaceBuilding(base, ptStart.getX(), ptStart.getY());

        //workers
        //MGroundUnit *wunit = workerId->create(pl);

        //map->placeGroundUnit(wunit, ptStart.getX() * Tile::TILE_WIDTH + 64, ptStart.getY() * Tile::TILE_HEIGHT + 64, false);

        //put this 5 into AssetManager or const
        //workers
        for(int i=0; i<5; i++)
        {
            MGroundUnit *wunit = workerId->create(pl);
            map->placeGroundUnitAroundPoint(wunit, ptStart.getX() * Tile::TILE_WIDTH, ptStart.getY() * Tile::TILE_HEIGHT, false);
            StiGame::Point tunitPt (wunit->getX() / Tile::TILE_WIDTH, wunit->getY() / Tile::TILE_HEIGHT);

            StiGame::Point resPt = map->findNearestResource(tunitPt, 10, 10, RT_METAL);

            if(resPt.getX() > 0 && resPt.getY() > 0)
            {

                StiGame::Point endPt ((resPt.getX() * Tile::TILE_WIDTH) + Tile::TILE_WIDTH / 2, (resPt.getY() * Tile::TILE_HEIGHT) + Tile::TILE_HEIGHT / 2);
                HarvestTask *task = new HarvestTask(wunit, pl, assets->getHarvestSpeed(), map, endPt);
                wunit->pushTask(task);

            }
        }

        PlayerMap *pmap = map->generatePlayerMap(pl);
        playerMaps.insert(std::make_pair(pl->getId(), pmap));
    }

    logStream->pushLine("Starting units placed");
}

std::string GameObject::getGameError(void)
{
    std::string msg = gameError;
    gameError = "";
    return msg;
}

void GameObject::publishError(std::string m_error)
{
    gameError = m_error;
    logStream->pushLine("Error : "+gameError);
}

Player* GameObject::getPlayer(int index)
{
    auto vit(players.begin()), vend(players.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getId() == index)
        {
            return (*vit);
        }
    }

    return nullptr;
}

PlayerMap* GameObject::getPlayerMap(int index)
{
    return playerMaps[index];
}

bool GameObject::createWorker(Player *player, Building *base)
{
    if(base->getBuldingType() == BT_Base)
    {
        if(base->getOwner() == player)
        {
            GroundUnitIdentity *workerId = assets->getWorkerIdentity();
            //population constraint to be added here
            if(player->getMetalCount() >= workerId->getMetalCost()
               && player->getGazCount() >= workerId->getGazCost())
            {
                //job id 0

                MBuilding *mbase = map->getBuildingById(base->getId());

                if(mbase != nullptr)
                {
                    mbase->emitJob(0);
                }

                return true;
            }
            else
            {
                publishError("Not enough ressources !");
            }
        }
        else
        {
            publishError("This is not your building !");
        }
    }
    else
    {
        publishError("Invalid building type !");
    }

    return false;
}
