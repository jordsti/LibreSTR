#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <LoadableObject.h>
#include <AssetManager.h>
class GameLoader :
        public LoadableObject
{
public:
    GameLoader(AssetManager *m_assets, int m_mapWidth, int m_mapHeight, int m_maxPop);
    virtual ~GameLoader();


    void load(void);
    void onCompletition(void);
private:
    AssetManager *assets;
    int mapWidth;
    int mapHeight;
    int maxPop;
};

#endif // GAMELOADER_H
