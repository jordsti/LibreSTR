#include "CompLeafAction.h"

namespace AI {

CompLeafAction::CompLeafAction()
{
}

CompLeafAction::~CompLeafAction()
{

}

void CompLeafAction::execute(void)
{
    auto ait(actions.begin()), aend(actions.end());
    for(;ait!=aend;ait++)
    {
        (*ait)->execute();
    }
}

void CompLeafAction::addAction(LeafAction *m_action)
{
    actions.push_back(m_action);
}

}
