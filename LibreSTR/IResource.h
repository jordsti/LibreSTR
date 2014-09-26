#ifndef IRESOURCE_H
#define IRESOURCE_H

#include <string>

enum ResourceType {
    RT_NOT_DEFINED = 0,
    RT_METAL = 1,
    RT_GAZ = 2
};

class IResource
{
    public:
        virtual ~IResource();

        std::string getName(void);
        std::string getTexture(void);
        ResourceType getType(void);
        int getAmount(void);

        virtual IResource* clone(void) = 0;

    protected:
        IResource();

        std::string name;
        int amount;
        std::string texture;
        ResourceType type;

    private:
};

#endif // IRESOURCE_H
