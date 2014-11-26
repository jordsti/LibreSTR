#ifndef PAUSEGAMEACTION_H
#define PAUSEGAMEACTION_H

#include <TimedGameAction.h>

class GameState;

class PauseGameAction :
        public StiGame::TimedGameAction
{
public:
    PauseGameAction(GameState *m_state);
    virtual ~PauseGameAction();

    void doAction(void);

private:
    GameState *state;
};

#endif // PAUSEGAMEACTION_H
