#include "MPlayer.h"

MPlayer::MPlayer() : Player()
{

}

MPlayer::MPlayer(PlayerColor pColor) :
    Player(pColor)
{

}

MPlayer::~MPlayer()
{

}

void MPlayer::setMetalCount(int m_metalCount)
{
    metalCount = m_metalCount;
}

void MPlayer::setGazCount(int m_gazCount)
{
    gazCount = m_gazCount;
}
