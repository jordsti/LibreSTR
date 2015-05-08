#include "GameObject.h"
#include "MapGenerator.h"
#include <iostream>
#include <map>
#include "MBuilding.h"
#include "CreateUnitEmitter.h"
#include <TimeTools.h>
#include "MoveTask.h"
#include "HarvestTask.h"
#include "BuildTask.h"
#include "AttackGroundUnitTask.h"
#include "AttackBuildingTask.h"

using namespace StiGame;

GameObject::GameObject(AssetManager *m_assets, GameMap *m_map, int m_maxPopulation, ILogStream *m_logStream)
{
    assets = m_assets;
    ended = false;
    //generating a random map by default
    //MapGenerator::setAssets(assets);
    map = m_map;

    map->subscribe(this);

    //generating player

    players.push_back(new MPlayer(PC_Blue));
    players.push_back(new MPlayer(PC_Red));

    logStream = m_logStream;

    lastTickMs = 0;
    maxPopulation = m_maxPopulation;
}

GameObject::~GameObject()
{
    //some cleaning todo
    delete map;

    auto mit(playerMaps.begin()), mend(playerMaps.end());
    for(;mit!=mend;++mit)
    {
        delete mit->second;
    }

    //delete playerMaps[1];
    //delete playerMaps[2];
    delete players[0];
    delete players[1];
}

void GameObject::buildBuilding(BuildingIdentity *buildingId, Unit *groundUnit, Player *player, int t_x, int t_y)
{
    MPlayer *_player = getMPlayer(player->getId());
    MGroundUnit *gu = map->getGroundUnitById(groundUnit->getId());

    if(_player->getMetalCount() >= buildingId->getMetalCost() &&
            _player->getGazCount() >= buildingId->getGazCost() &&
            gu->getOwner() == _player &&
            gu->getIdentity()->isCanBuild()
            )
    {
        MBuilding *building = buildingId->create(_player);

        if(building->getBuildingType() == BT_Base)
        {
            //create unit job emit with worker
            CreateUnitEmitter *emitter = new CreateUnitEmitter(_player, assets->getWorkerIdentity(), map);
            building->addEmitter(emitter);
        }
        else if(building->getBuildingType() == BT_Barrack)
        {
            CreateUnitEmitter *emitter = new CreateUnitEmitter(_player, assets->getMeleeIdentity(), map);
            building->addEmitter(emitter);
        }

        _player->setMetalCount(_player->getMetalCount() - buildingId->getMetalCost());
        _player->setGazCount(_player->getGazCount() - buildingId->getGazCost());

        PlayerMap *pmap = playerMaps[_player->getId()];

        map->placeBuilding(building, t_x, t_y);
        pmap->addBuilding(building);


        std::vector<StiGame::Point> pts = building->corners();
        StiGame::Point nearestPt;
        double dist = 10000;
        auto pit(pts.begin()), pend(pts.end());
        for(;pit!=pend;++pit)
        {
            double _dist = gu->middle().distanceWith(&(*pit));
            if(_dist < dist)
            {
                dist = _dist;
                nearestPt = (*pit);
            }
        }

        if(building->contains(&nearestPt))
        {
            nearestPt = StiGame::Point(building->getX() - gu->getWidth()/2, building->getY() - gu->getHeight()/2);
        }

        //todo, test this cause we are just using middle as end point
        BuildTask *task = new BuildTask(gu, assets->getBuildSpeed(), building, map, nearestPt);
        gu->pushTask(task);
    }
    else
    {
        publishError("GameObject::buildBuilding error");
    }

}

void GameObject::repairBuilding(Building *building, Unit *groundUnit, Player *player)
{
    MPlayer *_player = getMPlayer(player->getId());
    MGroundUnit *gu = map->getGroundUnitById(groundUnit->getId());
    MBuilding *b = map->getBuildingById(building->getId());

    if(b->getOwner() == _player && b->getCurrentHealth() < b->getMaxHealth() && gu->getOwner() == _player && gu->getIdentity()->isCanBuild())
    {
        //build task

        std::vector< StiGame::Point > pts = building->corners();
        StiGame::Point nearestPt;
        double dist = 10000;
        auto pit(pts.begin()), pend(pts.end());
        for(;pit!=pend;++pit)
        {
            double _dist = gu->distanceWith(&(*pit));
            if(_dist < dist)
            {
                dist = _dist;
                nearestPt = (*pit);
            }
        }

        BuildTask *task = new BuildTask(gu, assets->getBuildSpeed(), b, map, nearestPt);
        gu->pushTask(task);

        logStream->pushLine("Repairing building : unit "
                            + std::to_string(gu->getId())
                            + ", building : "
                            + std::to_string(b->getId()));
    }
    else
    {
       publishError("GameObject::repairBuilding error");
    }

}

void GameObject::resetLastTick(void)
{
    lastTickMs = 0;
}

void GameObject::tick(void)
{
    //game tick
    if(ended)
        return;

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
    //do the units and buildings count at the same time

    Player* defeated = nullptr;

    for(;mit!=mend; ++mit)
    {
        MPlayer *player = getMPlayer(mit->first);
        int count = 0;
        int populationCapacity = 0;
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
            else
            {
                count++;
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
            else
            {
                count++;
                //population capacity count
                if(b->getState() == BS_Builded)
                {
                    populationCapacity += b->getPopulationCapacity();
                }
            }
        }

        if(populationCapacity <= maxPopulation && maxPopulation != UNLIMITED_POPULATION)
        {
            player->setMaxPopulation(populationCapacity);
        }
        else
        {
            player->setMaxPopulation(maxPopulation);
        }

        if(count == 0)
        {
            //player loss
            defeated = player;
        }


    }

    if(defeated != nullptr)
    {
        defeatedPlayers.push_back(defeated);
        //delete playerMaps[defeated];
        playerMaps.erase(defeated->getId());

        //todo
        //delete the playermaps possibly

        //publish the event
        publishPlayerDefeated(defeated);
    }


    //win condition
    if(defeatedPlayers.size() == players.size() - 1)
    {
        auto wit(playerMaps.begin());
        Player *winner = getPlayer(wit->first);
        publishPlayerVictory(winner);
        ended = true;
    }
}

void GameObject::moveGroundUnit(Unit *groundUnit, StiGame::Point *targetPt)
{
    MGroundUnit *_unit = map->getGroundUnitById(groundUnit->getId());
    if(_unit != nullptr)
    {
        MoveTask *moveTask = new MoveTask(_unit, map, StiGame::Point(targetPt));
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
            HarvestTask *harvestTask = new HarvestTask(_unit, player, map, StiGame::Point(targetPt->getX(), targetPt->getY()));
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

void GameObject::attackGroundUnit(Unit *groundUnit, Unit *targetUnit)
{
    MGroundUnit *gu = map->getGroundUnitById(groundUnit->getId());
    MGroundUnit *target = map->getGroundUnitById(targetUnit->getId());

    if(gu != nullptr && target != nullptr)
    {
        if(gu->getOwner() != target->getOwner())
        {
            if(gu->getIdentity()->isCanAttack())
            {
                AttackGroundUnitTask *task = new AttackGroundUnitTask(gu, map, target);
                logStream->pushLine("Attack Ground Unit : " +
                                    gu->getName() + ";" +
                                    std::to_string(gu->getId()) + "; " +
                                    std::to_string(target->getId())
                                    );
                gu->pushTask(task);
            }
            else
            {
                publishError("This unit can't attack !");
            }
        }
        else
        {
            publishError("GameObject::attackGroundUnit : Invalid Target unit");
        }
    }
}

void GameObject::attackBuilding(Unit *groundUnit, Unit *targetBuilding)
{
    MGroundUnit *gu = map->getGroundUnitById(groundUnit->getId());
    MBuilding *target = map->getBuildingById(targetBuilding->getId());

    if(gu != nullptr && target != nullptr)
    {
        if(gu->getOwner() != target->getOwner())
        {
            if(gu->getIdentity()->isCanAttack())
            {
                AttackBuildingTask *task = new AttackBuildingTask(gu, map, target);
                logStream->pushLine("Attack Building : " +
                                    gu->getName() + ";" +
                                    std::to_string(gu->getId()) + "; " +
                                    std::to_string(target->getId())
                                    );
                gu->pushTask(task);
            }
            else
            {
                publishError("This unit can't attack !");
            }
        }
        else
        {
            publishError("GameObject::attackGroundUnit : Invalid Target unit");
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
            pl->setCurrentPopulation(pl->getCurrentPopulation() + workerId->getPopulationCost());
            map->placeGroundUnitAroundPoint(wunit, ptStart.getX() * Tile::TILE_WIDTH, ptStart.getY() * Tile::TILE_HEIGHT, false);
            StiGame::Point tunitPt (wunit->getX() / Tile::TILE_WIDTH, wunit->getY() / Tile::TILE_HEIGHT);

            StiGame::Point resPt = map->findNearestResource(tunitPt, 10, 10, RT_METAL);

            if(resPt.getX() > 0 && resPt.getY() > 0)
            {

                StiGame::Point endPt ((resPt.getX() * Tile::TILE_WIDTH) + Tile::TILE_WIDTH / 2, (resPt.getY() * Tile::TILE_HEIGHT) + Tile::TILE_HEIGHT / 2);
                HarvestTask *task = new HarvestTask(wunit, pl, map, endPt);
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
    if(base->getBuildingType() == BT_Base && base->getState() == BS_Builded)
    {
        if(base->getOwner() == player)
        {
            GroundUnitIdentity *workerId = assets->getWorkerIdentity();

            if(player->getMetalCount() >= workerId->getMetalCost()
               && player->getGazCount() >= workerId->getGazCost())
            {
                //job id 0

                if(player->getMaxPopulation() - player->getCurrentPopulation() < workerId->getPopulationCost())
                {
                    publishError("Need more house !");
                    return false;
                }

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

bool GameObject::createMelee(Player *player, Building *base)
{
    if(base->getBuildingType() == BT_Barrack && base->getState() == BS_Builded)
    {
        if(base->getOwner() == player)
        {
            GroundUnitIdentity *meleeId = assets->getMeleeIdentity();

            if(player->getMetalCount() >= meleeId->getMetalCost()
               && player->getGazCount() >= meleeId->getGazCost())
            {
                //job id 0

                if(player->getMaxPopulation() - player->getCurrentPopulation() < meleeId->getPopulationCost())
                {
                    publishError("Need more house !");
                    return false;
                }

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


void GameObject::handleEvent(GameMapEventThrower *src, GameMapEvent *event)
{
    // will be much more used when player points will be implemented
    if(event->getType() == GMET_GroundUnitKilled)
    {
        //remove this unit population
        GroundUnit *gu = dynamic_cast<GroundUnit*>(event->getUnit());
        MPlayer *player = getMPlayer(gu->getOwner()->getId());
        player->setCurrentPopulation(player->getCurrentPopulation() - gu->getIdentity()->getPopulationCost());

        logStream->pushLine("Ground Unit Killed : " + event->getUnit()->getName() + "; " + std::to_string(event->getUnit()->getOwner()->getId()));
    }
    else if(event->getType() == GMET_BuildingKilled)
    {
        logStream->pushLine("Building killed : " + event->getUnit()->getName() + "; " + std::to_string(event->getUnit()->getOwner()->getId()));
    }
}

void GameObject::publishPlayerDefeated(Player *defeated)
{
    auto lit(_listeners.begin()), lend(_listeners.end());
    for(;lit!=lend;++lit)
    {
        (*lit)->handlePlayerDefeat(defeated);
    }
}

void GameObject::publishPlayerVictory(Player *winner)
{
    auto lit(_listeners.begin()), lend(_listeners.end());
    for(;lit!=lend;++lit)
    {
        (*lit)->handlePlayerVictory(winner);
    }
}

 void GameObject::subscribe(GameObjectListener *listener)
 {
     _listeners.push_back(listener);
 }

 bool GameObject::isEnded(void)
 {
     return ended;
 }

 int GameObject::getMaxPopulation(void)
 {
     return maxPopulation;
 }
