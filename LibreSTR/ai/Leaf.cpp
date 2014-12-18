#include "Leaf.h"
namespace AI {

Leaf::Leaf()
{
    condition = nullptr;
    action = nullptr;
}

Leaf::Leaf(LeafCondition *m_condition, LeafAction *m_action)
{
    condition = m_condition;
    action = m_action;
}

Leaf::~Leaf()
{

}

int Leaf::getChildsCount(void)
{
    return leafs.size();
}

Leaf* Leaf::getChild(int index)
{
    return leafs[index];
}

LeafCondition* Leaf::getCondition(void)
{
    return condition;
}

LeafAction* Leaf::getAction(void)
{
    return action;
}

}
