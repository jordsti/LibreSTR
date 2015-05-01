#ifndef UNITPATH_H
#define UNITPATH_H

#include "UnitPathNode.h"
#include <vector>
#include "MPoint.h"
#include "ITileMap.h"
class UnitPath
{
public:
    UnitPath(StiGame::Point startingPoint);
    UnitPath(std::vector<StiGame::Point> points);
    virtual ~UnitPath();

    void add(StiGame::Point point);
    StiGame::Point* getPosition(void);

    UnitPathNode* getCurrent(void);
    bool moveToNext(void);

    static UnitPath* FindPath(StiGame::Point startingPoint, StiGame::Point endPoint, ITileMap *map);
    static bool TileValid(int x, int y, ITileMap *map);
    static StiGame::Point TileMiddlePoint(int t_x, int t_y);
protected:
    UnitPathNode* getLastNode(void);
private:
    UnitPathNode start;
    UnitPathNode *currentNode;
    StiGame::MPoint position;
};

class ProjectedPath {
public:
    ProjectedPath();
    virtual ~ProjectedPath();

    std::vector<StiGame::Point> points;
    unsigned int score(void);
    StiGame::Point lastPoint(void);
    bool close;
    bool complete;
    ProjectedPath* clone(void);
};

#endif // UNITPATH_H
