#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameMap.h"
#include "AssetManager.h"
#include "MPlayer.h"
#include "ILogStream.h"
#include "GameMapEventListener.h"

class GameObject :
       public GameMapEventListener
{
public:
    const int PLAYERS_MAX = 2; //atm
    GameObject(AssetManager *m_assets, int mapWidth, int mapHeight, ILogStream *m_logStream);

    Player* getPlayer(int index);
    PlayerMap* getPlayerMap(int index);

    virtual ~GameObject();

    void initGame(void);

    void tick(void);

    void moveGroundUnit(Unit *groundUnit, StiGame::Point *targetPt);
    void harvestResource(Unit *groundUnit, StiGame::Point *targetPt);
    void attackGroundUnit(Unit *groundUnit, Unit *targetUnit);
    void attackBuilding(Unit *groundUnit, Unit *targetBuilding);

    bool createWorker(Player *player, Building *base);
    bool createMelee(Player *player, Building *base);

    void buildBuilding(BuildingIdentity *buildingId, Unit *groundUnit, Player *player, int t_x, int t_y);
    void repairBuilding(Building *building, Unit *groundUnit, Player *player);

    std::string getGameError(void);

    void resetLastTick(void);

    //map event handling
    void handleEvent(GameMapEventThrower *src, GameMapEvent *event);

private:
    void publishError(std::string m_error);

    MPlayer* getMPlayer(int id);

    long long lastTickMs;
    AssetManager *assets;
    GameMap *map;
    ILogStream *logStream;

    std::vector<MPlayer*> players;
    std::map<int, PlayerMap*> playerMaps;
    std::string gameError;
};

#endif // GAMEOBJECT_H
