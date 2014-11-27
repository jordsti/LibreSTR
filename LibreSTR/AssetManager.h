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

        AssetManager();
        virtual ~AssetManager();

        ResourceIdentity* getMetalIdentity(void);
        ResourceIdentity* getGazIdentity(void);

        BuildingIdentity* getBaseIdentity(void);
        BuildingIdentity* getBarrackIdentity(void);

        GroundUnitIdentity* getWorkerIdentity(void);


        std::string getTileNormal(void);
        std::string getTileBlock(void);

        std::list<std::string> getTextures(void);

        std::list<std::string> getDirectionSprites(void);

        StiGame::ActionBinding* getBindings(void);

        int getHarvestSpeed(void);
        int getBuildSpeed(void);

    protected:
        void loadData(void);
        void initBindings(void);

        int harvestSpeed;
        int buildSpeed;

        ResourceIdentity *resMetal;
        ResourceIdentity *resGaz;

        BuildingIdentity *base;
        BuildingIdentity *barrack;

        GroundUnitIdentity *worker;

        StiGame::ActionBinding *bindings;

        std::string tileNormal;
        std::string tileBlock;
    private:
};

#endif // ASSETMANAGER_H
