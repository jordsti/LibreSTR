#ifndef PLAYER_H
#define PLAYER_H

#include <Color.h>

enum PlayerColor {
    PC_Blue,
    PC_Red
};

class Player
{
public:
    Player();
    Player(PlayerColor m_playerColor);
    virtual ~Player();
    PlayerColor getPlayerColor(void);
    StiGame::Color* getColor(void);
protected:
    void initPlayer(void);

    PlayerColor playerColor;
    StiGame::Color color;

};

#endif // PLAYER_H
