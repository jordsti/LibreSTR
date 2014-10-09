#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "ResourceIdentity.h"
#include <ActionBinding.h>
#include <list>

class AssetManager
{
    public:
        AssetManager();
        virtual ~AssetManager();

        ResourceIdentity* getMetalIdentity(void);
        ResourceIdentity* getGazIdentity(void);

        std::string getTileNormal(void);
        std::string getTileBlock(void);

        std::list<std::string> getTextures(void);


        StiGame::ActionBinding* getBindings(void);
    protected:
        void loadData(void);
        void initBindings(void);

        ResourceIdentity *resMetal;
        ResourceIdentity *resGaz;

        StiGame::ActionBinding *bindings;

        std::string tileNormal;
        std::string tileBlock;
    private:
};

#endif // ASSETMANAGER_H
