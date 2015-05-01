#include "UnitPathNode.h"

UnitPathNode::UnitPathNode() :
    _point(0, 0)
{
    _next = nullptr;
}

UnitPathNode::UnitPathNode(int x, int y) :
    _point(0, 0)
{
    _next = nullptr;
}

UnitPathNode::UnitPathNode(StiGame::Point m_point) :
    _point(&m_point)
{
    _next = nullptr;
}

UnitPathNode::~UnitPathNode()
{

}

UnitPathNode* UnitPathNode::next(void)
{
    return _next;
}

StiGame::Point* UnitPathNode::point(void)
{
    return &_point;
}

bool UnitPathNode::hasNext(void)
{
    return _next != nullptr;
}

void UnitPathNode::setNext(UnitPathNode *m_next)
{
    _next = m_next;
}
