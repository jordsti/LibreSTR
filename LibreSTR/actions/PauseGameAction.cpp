#include "PauseGameAction.h"
#include "GameState.h"

PauseGameAction::PauseGameAction(GameState *m_state)
{
    state = m_state;
    cooldown = 250;
    name = "pause_game";
}

PauseGameAction::~PauseGameAction()
{

}

void PauseGameAction::doAction(void)
{
    state->setPause(!state->getPause());
}
