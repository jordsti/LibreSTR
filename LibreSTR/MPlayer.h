#ifndef MPLAYER_H
#define MPLAYER_H
#include "Player.h"

class MPlayer :
        public Player
{
public:
    MPlayer();
    MPlayer(PlayerColor pColor);
    virtual ~MPlayer();

    void setMetalCount(int m_metalCount);
    void setGazCount(int m_gazCount);

    void setCurrentPopulation(int m_currentPopulation);
    void setMaxPopulation(int m_maxPopulation);
};

#endif // MPLAYER_H
