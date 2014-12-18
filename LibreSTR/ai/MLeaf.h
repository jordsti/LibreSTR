#ifndef MLEAF_H
#define MLEAF_H

#include "Leaf.h"

namespace AI {

class MLeaf :
        public Leaf
{
public:
    MLeaf();
    MLeaf(LeafCondition *m_condition, LeafAction *m_action);
    virtual ~MLeaf();

    void setCondition(LeafCondition *m_condition);
    void setAction(LeafAction *m_action);

    void addChild(Leaf *m_child);

};

}

#endif // MLEAF_H
