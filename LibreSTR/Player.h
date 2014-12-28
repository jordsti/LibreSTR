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

    int getMetalCount(void);
    int getGazCount(void);
    int getId(void);

    int getMaxPopulation(void);
    int getCurrentPopulation(void);

    static void ResetPlayerId(void);
protected:
    void initPlayer(void);

    int metalCount;
    int gazCount;

    int maxPopulation;
    int currentPopulation;

    PlayerColor playerColor;
    StiGame::Color color;
private:
    int _id;
    static int _currentId;
    int currentId(void);
};

#endif // PLAYER_H
