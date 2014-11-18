#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameMap.h"
#include "AssetManager.h"
#include "MPlayer.h"

class GameObject
{
public:
    const int PLAYERS_MAX = 2; //atm
    GameObject(AssetManager *m_assets, int mapWidth, int mapHeight);

    Player* getPlayer(int index);
    PlayerMap* getPlayerMap(int index);

    virtual ~GameObject();

    void initGame(void);

    void tick(void);

    bool createWorker(Player *player, Building *base);

    std::string getGameError(void);
private:
    long long lastTickMs;
    AssetManager *assets;
    GameMap *map;
    std::vector<MPlayer*> players;
    std::map<int, PlayerMap*> playerMaps;
    std::string gameError;
};

#endif // GAMEOBJECT_H
