#ifndef UNITPATHNODE_H
#define UNITPATHNODE_H
#include "Point.h"
class UnitPathNode
{
public:
    UnitPathNode();
    UnitPathNode(int x, int y);
    UnitPathNode(StiGame::Point m_point);

    virtual ~UnitPathNode();

    UnitPathNode* next(void);
    StiGame::Point* point(void);
    bool hasNext(void);
    void setNext(UnitPathNode *m_next);
private:
    UnitPathNode *_next;
    StiGame::Point _point;
};

#endif // UNITPATHNODE_H
