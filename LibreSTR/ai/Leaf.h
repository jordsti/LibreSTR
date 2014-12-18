#ifndef LEAF_H
#define LEAF_H

#include <vector>

#include "LeafCondition.h"
#include "LeafAction.h"

namespace AI {

class Leaf
{
public:
    Leaf();
    Leaf(LeafCondition *m_condition, LeafAction *m_action);

    virtual ~Leaf();

    LeafCondition* getCondition(void);
    LeafAction* getAction(void);

    int getChildsCount(void);
    Leaf* getChild(int index);

protected:
    LeafCondition *condition;
    LeafAction *action;

    std::vector<Leaf*> leafs;


};

}

#endif // LEAF_H
