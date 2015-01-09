#include "GameLoader.h"
#include <MapGenerator.h>

GameLoader::GameLoader(AssetManager *m_assets, int m_mapWidth, int m_mapHeight, int m_maxPop)
{
    assets = m_assets;
    mapWidth = m_mapWidth;
    mapHeight = m_mapHeight;
    maxPop = m_maxPop;
}

GameLoader::~GameLoader()
{
}


void GameLoader::load(void)
{
    MapGenerator::setAssets(assets);

    caption = "Generating map....";

    GameMap *map = MapGenerator::RandomMap(mapWidth, mapHeight);

    currentProgress = 1;

    complete = true;
}

void GameLoader::onCompletition(void)
{

}
