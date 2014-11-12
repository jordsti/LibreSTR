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
};

#endif // MPLAYER_H
