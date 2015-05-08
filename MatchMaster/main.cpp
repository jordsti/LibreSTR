
#include "MatchMaster.h"
/*
 * This is the Multiplayer Match Master Server
 * Will Keep a list of all open games
 *  -> Must add Mock server list
 *
 */

int main(int argc, char ** argv)
{
    int ia=0;
    bool mock = false;

    while(ia < argc)
    {
        std::string arg (argv[ia]);

        if(arg == "-mock")
        {
            mock = true;
        }

        ia++;
    }

    MatchMaster master;

    if(mock)
    {
        STRData::Match *m = new STRData::Match();
        m->setId(1);
        m->setName("Test Match 1");
        m->setCurrentPlayers(0);
        m->setMaxPlayers(8);
        m->setPasswordProtected(false);
        m->setHost("127.0.0.1");
        m->setPort(65);

        master.addMatch(m);

        m = new STRData::Match();
        m->setId(2);
        m->setName("Test Match 2");
        m->setCurrentPlayers(0);
        m->setMaxPlayers(8);
        m->setPasswordProtected(false);
        m->setHost("127.0.0.1");
        m->setPort(65);

        master.addMatch(m);

        m = new STRData::Match();
        m->setId(3);
        m->setName("Test Match 3");
        m->setCurrentPlayers(2);
        m->setMaxPlayers(8);
        m->setPasswordProtected(false);
        m->setHost("127.0.0.1");
        m->setPort(65);

        master.addMatch(m);
    }

    master.start();
	return 0;
}
