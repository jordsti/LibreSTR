#include "GameObject.h"
#include "MapGenerator.h"
#include <iostream>
#include <map>
using namespace StiGame;

GameObject::GameObject(AssetManager *m_assets, int mapWidth, int mapHeight)
{
    assets = m_assets;
    //generating a random map by default
    MapGenerator::setAssets(assets);
    map = MapGenerator::RandomMap(mapWidth, mapHeight);

    //generating player

    players.push_back(new Player(PC_Blue));
    players.push_back(new Player(PC_Red));
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

void GameObject::initGame(void)
{
    /*
     *  Placing building and player starting unit
     *  Generate Player Map
     *  be ready for starting the Game
     *
     */

    BuildingIdentity *baseId = assets->getBaseIdentity();
    std::map<Player*, Point> playerStartPts;

    auto vit(players.begin()), vend(players.end());
    for(;vit!=vend;++vit)
    {
        std::vector<Point> startingPoints = map->getPlayerStartingPoints((*vit)->getId());
        std::cout << (*vit)->getId() << std::endl;
        int p = rand() % startingPoints.size();

        Point ps = startingPoints[p];

        playerStartPts.insert(std::make_pair((*vit), ps));
    }

    auto mit(playerStartPts.begin()), mend(playerStartPts.end());
    for(;mit!=mend;++mit)
    {
        Player *pl = mit->first;
        Point ptStart = mit->second;

        Building *base = baseId->create(pl);
        base->setState(BS_Construction);
        map->forcePlaceBuilding(base, ptStart.getX(), ptStart.getY());
        std::cout << "Placing player " << pl->getId() << "base at " << ptStart.getX() << "; " << ptStart.getY() << std::endl;


        PlayerMap *pmap = map->GeneratePlayerMap(pl->getId());
        playerMaps.insert(std::make_pair(pl->getId(), pmap));
    }
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
