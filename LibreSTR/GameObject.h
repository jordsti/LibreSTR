#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameMap.h"
#include "AssetManager.h"
#include "MPlayer.h"
#include "ILogStream.h"

class GameObject
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

    bool createWorker(Player *player, Building *base);

    std::string getGameError(void);
private:
    void publishError(std::string m_error);

    long long lastTickMs;
    AssetManager *assets;
    GameMap *map;
    ILogStream *logStream;

    std::vector<MPlayer*> players;
    std::map<int, PlayerMap*> playerMaps;
    std::string gameError;
};

#endif // GAMEOBJECT_H
