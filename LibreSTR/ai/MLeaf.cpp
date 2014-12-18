#include "MLeaf.h"
namespace AI {

MLeaf::MLeaf()
    : Leaf()
{
    condition = nullptr;
    action = nullptr;
}

MLeaf::MLeaf(LeafCondition *m_condition, LeafAction *m_action)
    : Leaf(m_condition, m_action)
{

}

MLeaf::~MLeaf()
{

}

void MLeaf::setCondition(LeafCondition *m_condition)
{
    condition = m_condition;
}

void MLeaf::setAction(LeafAction *m_action)
{
    action = m_action;
}

void MLeaf::addChild(Leaf *m_child)
{
    leafs.push_back(m_child);
}

}
