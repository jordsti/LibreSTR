#include "ViewMoveAction.h"
#include "GameState.h"

using namespace StiGame;
ViewMoveAction::ViewMoveAction(GameState *m_state, std::string m_name, int m_dx, int m_dy) :
    BaseGameAction()
{
    state = m_state;
    name = m_name;
    dx = m_dx;
    dy = m_dy;
}

ViewMoveAction::~ViewMoveAction()
{

}

void ViewMoveAction::doAction(void)
{
    state->moveViewPoint(dx, dy);
}
