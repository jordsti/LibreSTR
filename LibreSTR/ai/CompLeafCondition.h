#ifndef COMPLEAFCONDITION_H
#define COMPLEAFCONDITION_H

#include "LeafCondition.h"
#include <vector>

namespace AI {

class CompLeafCondition :
        public LeafCondition
{
public:
    CompLeafCondition();
    virtual ~CompLeafCondition();

    virtual bool isPassed(void);

    void addCondition(LeafCondition *m_condition);

protected:
    std::vector<LeafCondition*> conditions;
};


}
#endif // COMPLEAFCONDITION_H
