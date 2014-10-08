#ifndef VIEWMOVEACTION_H
#define VIEWMOVEACTION_H
#include <BaseGameAction.h>

class GameState;

class ViewMoveAction :
        public StiGame::BaseGameAction
{
public:
    ViewMoveAction(GameState *m_state, std::string m_name, int m_dx, int m_dy);
    virtual ~ViewMoveAction();
protected:
    void doAction(void);
private:
    GameState *state;
    int dx;
    int dy;
};

#endif // VIEWMOVEACTION_H
