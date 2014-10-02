#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "VFResource.h"
#include <list>

class AssetManager
{
    public:
        AssetManager();
        virtual ~AssetManager();

        VFResource* getMetalDef(void);
        VFResource* getGazDef(void);

        std::string getTileNormal(void);
        std::string getTileBlock(void);

        std::list<std::string> getTextures(void);

    protected:
        void loadData(void);

        VFResource *resMetal;
        VFResource *resGaz;

        std::string tileNormal;
        std::string tileBlock;
    private:
};

#endif // ASSETMANAGER_H
