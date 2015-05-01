#include "UnitPath.h"

UnitPath::UnitPath(StiGame::Point startingPoint) :
    start(startingPoint),
    position(&startingPoint)
{

}

UnitPath::UnitPath(std::vector<StiGame::Point> points) :
    start(points[0])
{
    UnitPathNode *current = &start;
    auto lit(points.begin()), lend(points.end());
    int i=0;
    for(;lit!=lend;++lit)
    {
        if(i > 0)
        {
            UnitPathNode *node = new UnitPathNode((*lit));
            current->setNext(node);
            current = node;
        }

        i++;
    }
}

UnitPath::~UnitPath()
{
    //don't need to delete the starting node
    UnitPathNode *current = start.next();
    while(current != nullptr)
    {
        UnitPathNode *next = current->next();
        delete current;
        current = next;
    }
}

UnitPathNode* UnitPath::getCurrent(void)
{
    return currentNode;
}

bool UnitPath::moveToNext(void)
{
    if(currentNode->hasNext())
    {
        currentNode = currentNode->next();
        return true;
    }

    return false;
}

UnitPathNode* UnitPath::getLastNode(void)
{
    UnitPathNode *current = &start;
    while(current->hasNext())
    {
        current = current->next();
    }

    return current;
}

StiGame::Point* UnitPath::getPosition(void)
{
    return &position;
}

void UnitPath::add(StiGame::Point point)
{
    UnitPathNode *last = getLastNode();
    UnitPathNode *newNode = new UnitPathNode(point);
    last->setNext(newNode);
}

bool UnitPath::TileValid(int x, int y, ITileMap *map)
{
    if(x < map->getWidth() && x >= 0 && y < map->getHeight() && y >= 0)
    {
        Tile *tile = map->get(x, y);
        if(tile->getType() == TT_Normal)
        {
            return true;
        }

        return false;
    }

    return false;
}

StiGame::Point UnitPath::TileMiddlePoint(int t_x, int t_y)
{
    StiGame::Point mid ((t_x*Tile::TILE_WIDTH) + Tile::TILE_WIDTH/2, (t_y*Tile::TILE_HEIGHT) * Tile::TILE_HEIGHT/2);
    return mid;
}

UnitPath* UnitPath::FindPath(StiGame::Point startingPoint, StiGame::Point endPoint, ITileMap *map)
{
    // A*
    std::vector<StiGame::Point> points;
    points.push_back(startingPoint);

    //add middle of the starting tile
    StiGame::Point midTile (
                (startingPoint.getX() / Tile::TILE_WIDTH)*Tile::TILE_WIDTH + Tile::TILE_WIDTH/2,
                (startingPoint.getY() / Tile::TILE_HEIGHT)*Tile::TILE_HEIGHT + Tile::TILE_HEIGHT/2
                );

    points.push_back(midTile);

    StiGame::Point endMidTile (
                (endPoint.getX() / Tile::TILE_WIDTH) + Tile::TILE_WIDTH/2,
                (endPoint.getY() / Tile::TILE_HEIGHT) + Tile::TILE_HEIGHT/2
                );

    //starting A* here
    std::vector<ProjectedPath*> paths;
    std::vector<ProjectedPath*> allPaths;
    //initial starting path (four direction)
    int t_x = (startingPoint.getX() / Tile::TILE_WIDTH);
    int t_y = (startingPoint.getY() / Tile::TILE_HEIGHT);
    for(int i=0; i<4; i++)
    {
        StiGame::MPoint tileCoord (-1, -1);
        switch(i)
        {
        case 0:
            // Up, y-1
            if(TileValid(t_x, t_y-1, map))
            {
                tileCoord.setPoint(t_x, t_y-1);
            }
            break;
        case 1:
            // Down, y+1
            if(TileValid(t_x, t_y+1, map))
            {
                tileCoord.setPoint(t_x, t_y+1);
            }
            break;
        case 2:
            // Left, x-1
            if(TileValid(t_x-1, t_y, map))
            {
                tileCoord.setPoint(t_x-1, t_y);
            }
            break;
        case 3:
            // Right, x+1
            if(TileValid(t_x+1, t_y, map))
            {
                tileCoord.setPoint(t_x+1, t_y);
            }
            break;
        default:
            break;
        }

        if(!tileCoord.equals(-1, -1))
        {
            ProjectedPath *pp = new ProjectedPath();
            pp->points.push_back(startingPoint);
            pp->points.push_back(StiGame::Point(&tileCoord));
            paths.push_back(pp);
            allPaths.push_back(pp);
        }
    }

    std::vector<ProjectedPath*> tmpPaths;
    bool completed = false;
    while(!completed)
    {
        auto lit(paths.begin()), lend(paths.end());
        unsigned int min_score = 200000;
        unsigned int max_score = 0;
        for(;lit!=lend;++lit)
        {
            ProjectedPath *pp = (*lit);
            if(!pp->close)
            {
                StiGame::Point lastPt = pp->lastPoint();
                int t_x = lastPt.getX() / Tile::TILE_WIDTH;
                int t_y = lastPt.getY() / Tile::TILE_HEIGHT;
                unsigned int score = pp->score();

                if(score < min_score)
                {
                    min_score = score;
                }

                if(score > max_score)
                {
                    max_score = score;
                }

                for(int i=0; i<4; i++)
                {
                    StiGame::MPoint tileCoord (-1, -1);
                    switch(i)
                    {
                    case 0:
                        //Up
                        tileCoord.setPoint(t_x, t_y-1);
                        break;
                    case 1:
                        //Down
                        tileCoord.setPoint(t_x, t_y+1);
                        break;
                    case 2:
                        //Left
                        tileCoord.setPoint(t_x-1, t_y);
                        break;
                    case 3:
                        //Right
                        tileCoord.setPoint(t_x+1, t_y);
                        break;
                    }

                    if(TileValid(tileCoord.getX(), tileCoord.getY(), map))
                    {
                        StiGame::Point mid = TileMiddlePoint(tileCoord.getX(), tileCoord.getY());

                        ProjectedPath *newpp = pp->clone();

                        newpp->points.push_back(mid);

                        tmpPaths.push_back(newpp);
                        allPaths.push_back(newpp);
                    }
                }

                pp->close = true;

            }
        }

        //switching current vector
        paths = tmpPaths;
    }
}

ProjectedPath::ProjectedPath()
{
    close = false;
}

ProjectedPath::~ProjectedPath()
{

}

StiGame::Point ProjectedPath::lastPoint(void)
{
    return points[points.size()-1];
}

unsigned int ProjectedPath::score(void)
{
    return points.size();
}


ProjectedPath* ProjectedPath::clone(void)
{
    ProjectedPath *pp = new ProjectedPath();
    auto lit(points.begin()), lend(points.end());
    for(;lit!=lend;++lit)
    {
        pp->points.push_back((*lit));
    }

    return pp;
}
