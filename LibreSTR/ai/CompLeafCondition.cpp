#include "CompLeafCondition.h"

namespace AI {

CompLeafCondition::CompLeafCondition()
{

}

CompLeafCondition::~CompLeafCondition()
{

}

bool CompLeafCondition::isPassed(void)
{
    auto cit(conditions.begin()), cend(conditions.end());
    for(;cit!=cend;++cit)
    {
        if(!(*cit)->isPassed())
        {
            return false;
        }
    }
    return true;
}

void CompLeafCondition::addCondition(LeafCondition *m_condition)
{
    conditions.push_back(m_condition);
}

}
