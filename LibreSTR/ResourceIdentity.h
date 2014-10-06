#ifndef VFRESOURCE_H
#define VFRESOURCE_H

#include "Resource.h"

class ResourceIdentity
{
    public:
        ResourceIdentity(std::string var_file);
        virtual ~ResourceIdentity();

        Resource* create(void);

        int getStartingAmount(void);
        ResourceType getType(void);
        std::string getIcon(void);
        std::string getTexture(void);
        std::string getName(void);

    protected:
        void fromVarFile(std::string var_file);

        int startingAmount;
        ResourceType type;
        std::string icon;
        std::string texture;
        std::string name;

    private:
};

#endif // RESOURCE_H
