#ifndef BUILDINGIDENTITY_H
#define BUILDINGIDENTITY_H
#include <string>
#include "Player.h"

class Building;

class BuildingIdentity
{
public:
    BuildingIdentity(std::string id_file);
    virtual ~BuildingIdentity();
    Building* create(Player *owner);

    int getMetalCost(void);
    int getGazCost(void);
    int getMaxHealth(void);
    std::string getName(void);
    std::string getSpriteName(void);
    int getWidth(void);
    int getHeight(void);

protected:
    int metalCost;
    int gazCost;
    int maxHealth;
    std::string name;
    std::string spriteName;
    int width;
    int height;
};

#endif // BUILDINGIDENTITY_H
