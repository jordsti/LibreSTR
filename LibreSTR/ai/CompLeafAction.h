#ifndef COMPLEAFACTION_H
#define COMPLEAFACTION_H

#include "LeafAction.h"
#include <vector>

namespace AI {

class CompLeafAction
{
public:
    CompLeafAction();
    virtual ~CompLeafAction();

    virtual void execute(void);

    void addAction(LeafAction *m_action);

protected:
    std::vector<LeafAction*> actions;
};

}

#endif // COMPLEAFACTION_H
