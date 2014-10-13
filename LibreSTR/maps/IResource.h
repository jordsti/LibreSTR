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
    virtual std::string getName(void) = 0;
    virtual std::string getIcon(void) = 0;
    virtual std::string getTexture(void) = 0;
    virtual int getAmount(void) = 0;
    virtual int getId(void) = 0;
    virtual ResourceType getType(void) = 0;
protected:
    IResource();
    virtual ~IResource();

};

#endif // IRESOURCE_H
