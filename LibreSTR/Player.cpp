#include "Player.h"

Player::Player()
{
    playerColor = PC_Blue;
    initPlayer();
}

Player::Player(PlayerColor m_playerColor)
{
    playerColor = m_playerColor;
    initPlayer();
}

Player::~Player()
{

}

void Player::initPlayer(void)
{
    if(playerColor == PC_Blue)
    {
        color.setRGB(0, 0, 255);
    }
    else if(playerColor == PC_Red)
    {
        color.setRGB(255, 0, 0);
    }

    metalCount = 0;
    gazCount = 0;
}

int Player::getMetalCount(void)
{
    return metalCount;
}

int Player::getGazCount(void)
{
    return gazCount;
}

PlayerColor Player::getPlayerColor(void)
{
    return playerColor;
}

StiGame::Color* Player::getColor(void)
{
    return &color;
}
