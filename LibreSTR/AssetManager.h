#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "ResourceIdentity.h"
#include "BuildingIdentity.h"
#include "GroundUnitIdentity.h"
#include <ActionBinding.h>
#include <list>

class AssetManager
{
    public:
        static const int BINDINGS_COUNT;
        static std::string OPTION_FILE;

        AssetManager();
        virtual ~AssetManager();

        ResourceIdentity* getMetalIdentity(void);
        ResourceIdentity* getGazIdentity(void);

        BuildingIdentity* getBaseIdentity(void);
        BuildingIdentity* getBarrackIdentity(void);
        BuildingIdentity* getHouseIdentity(void);

        GroundUnitIdentity* getWorkerIdentity(void);
        GroundUnitIdentity* getMeleeIdentity(void);

        std::string getTileNormal(void);
        std::string getTileBlock(void);
        std::string getMasterServer(void);

        std::list<std::string> getTextures(void);

        std::list<std::string> getDirectionSprites(void);

        StiGame::ActionBinding* getBindings(void);

        //to be remove from asset going into unit definition
        int getHarvestSpeed(void);
        int getBuildSpeed(void);

        StiGame::VarFile* getOptions(void);

    protected:
        StiGame::VarFile options;

        void loadData(void);
        void initBindings(void);

        int harvestSpeed;
        int buildSpeed;

        ResourceIdentity *resMetal;
        ResourceIdentity *resGaz;

        BuildingIdentity *base;
        BuildingIdentity *barrack;
        BuildingIdentity *house;

        GroundUnitIdentity *worker;
        GroundUnitIdentity *melee;

        StiGame::ActionBinding *bindings;

        std::string tileNormal;
        std::string tileBlock;

        std::string masterServer;
    private:
};

#endif // ASSETMANAGER_H
