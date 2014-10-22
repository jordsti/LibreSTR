#include "MapGenerator.h"
#include "TimeTools.h"
#include <iostream>
#include <cstdlib>
#include <list>
#include <Point.h>

const int MapGenerator::LIMIT_OFFSET = 5;
const int MapGenerator::MAX_ITERATION = 1024;
const int MapGenerator::N_TILES = 48;
const int MapGenerator::METAL_TILES = 10;
const int MapGenerator::GAZ_TILES = 2;
const int MapGenerator::RES_POINT_OFFSET = 15;

AssetManager* MapGenerator::assets = nullptr;

MapGenerator::MapGenerator()
{
    //ctor
}

MapGenerator::~MapGenerator()
{
    //dtor
}

void MapGenerator::setAssets(AssetManager *m_assets)
{
    assets = m_assets;
}

GameMap* MapGenerator::RandomMap(int width, int height)
{
    int seed = StiGame::Time::GenerateSeed();
    return RandomMap(width, height, seed);
}

GameMap* MapGenerator::RandomMap(int width, int height, int seed)
{
    srand(seed);
    GameMap *gmap = new GameMap(width, height, seed);

    int tileNormal = gmap->addTexture(assets->getTileNormal());
    int tileBlock = gmap->addTexture(assets->getTileBlock());

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Tile *t = gmap->get(x, y);

            int i = rand() % 30;

            if(i >= 0 && i <= 2)
            {
                t->setType(TT_Block);
                t->setTextureId(tileBlock);
            }
            else
            {
                t->setType(TT_Normal);
                t->setTextureId(tileNormal);
            }
            /*else if(i < 5 && i > 2)
            {
                t->setType(TT_Water);
            }*/
        }
    }

    //generate starting point

    //each corner would got a spot
    //player 1 is left
    //player 2 is right
    //0,0
    std::list<StiGame::Point> pts;
    StiGame::Point p1 (RES_POINT_OFFSET, RES_POINT_OFFSET);
    pts.push_back(p1);
    gmap->addStartPoint(1, p1);

    //width, height
    StiGame::Point p2 (width - RES_POINT_OFFSET, height - RES_POINT_OFFSET);
    pts.push_back(p2);
    gmap->addStartPoint(2, p2);

    //0, height
    StiGame::Point p3 (RES_POINT_OFFSET, height - RES_POINT_OFFSET);
    pts.push_back(p3);
    gmap->addStartPoint(1, p3);

    //width, 0
    StiGame::Point p4 (width - RES_POINT_OFFSET, RES_POINT_OFFSET);
    pts.push_back(p4);
    gmap->addStartPoint(2, p4);

    //each middle
    // width/2, 0
    // not good for a start point
    pts.push_back(StiGame::Point(width/2, RES_POINT_OFFSET));

    // width/2, height
    // not good for a start point
    pts.push_back(StiGame::Point(width/2, height - RES_POINT_OFFSET));

    // 0, height/2

    StiGame::Point p5 (RES_POINT_OFFSET, height/2);
    pts.push_back(p5);
    gmap->addStartPoint(1, p5);

    // width, height/2
    StiGame::Point p6 (width - RES_POINT_OFFSET, height/2);
    pts.push_back(p6);
    gmap->addStartPoint(2, p6);

    //full middle
    StiGame::Point p7 (width/2, height/2);
    pts.push_back(p7);
    //adding some random points for ressource

    //placing random pts
    //between 3 and 5 pts

    int nb = rand() % 2;
    nb += 3;

    for(int i=0; i<nb; i++)
    {
        int x = (rand() % (width-RES_POINT_OFFSET*2)) + RES_POINT_OFFSET;
        int y = (rand() % (height-RES_POINT_OFFSET*2)) + RES_POINT_OFFSET;
        StiGame::Point rpt (x, y);
        pts.push_back(rpt);
    }



    auto lit(pts.begin()), lend(pts.end());
    for(;lit!=lend;++lit)
    {
        PlaceRessource(gmap, (*lit).getX(), (*lit).getY(), N_TILES, METAL_TILES, GAZ_TILES);
    }

    return gmap;
}

void MapGenerator::PlaceRessource(GameMap *gmap, int x, int y, int n, int metalTiles, int gazTiles)
{
    //chosing n tiles around the points
    //from those tiles choose n random and place ressource on them
    std::vector<Tile*> tilesTaken;
    std::vector<StiGame::Point> chosenPts;

    StiGame::Point mpt (x, y);
    int i=0;
    while(tilesTaken.size() < n)
    {
        int tx = LIMIT_OFFSET - (rand() % LIMIT_OFFSET*2);
        int ty = LIMIT_OFFSET - (rand() % LIMIT_OFFSET*2);


        tx += mpt.getX();
        ty += mpt.getY();

        if(gmap->contains(tx, ty))
        {
            StiGame::Point cpt (tx, ty);

            if(cpt.equals(&mpt))
            {
                continue;
            }

            auto lit(chosenPts.begin()), lend(chosenPts.end());
            for(;lit!=lend;++lit)
            {
                if((*lit).equals(&cpt))
                {
                    continue;
                }
            }

            Tile *t = gmap->get(tx, ty);
            if(t->getType() == TT_Normal)
            {
                chosenPts.push_back(cpt);
                tilesTaken.push_back(t);
            }
        }

        i++;

        if(i > 500)
        {
            std::cout << "MAX ITERATION HIT!" << std::endl;
            break;
        }
    }

    i = 0;
    int j = 0;
    while(j < gazTiles)
    {
        if(i+j >= tilesTaken.size())
        {
            std::cout << "no more tiles..." << std::endl;
            break;
        }

        Tile *t = tilesTaken[j+i];

        if(!t->containsResource())
        {
            Resource *res = assets->getGazIdentity()->create();
            t->setResource(res);
        }
        else
        {
            i++;
            continue;
        }

        i++;
        j++;
    }

    j = 0;
    while(j < metalTiles)
    {
        if(i+j >= tilesTaken.size())
        {
            std::cout << "no more tiles..." << std::endl;
            break;
        }

        Tile *t = tilesTaken[j+i];
        if(!t->containsResource())
        {
            Resource *res = assets->getMetalIdentity()->create();
            t->setResource(res);
        }
        else
        {
            i++;
            continue;
        }

        i++;
        j++;
    }



}
