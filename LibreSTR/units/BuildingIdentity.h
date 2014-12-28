#ifndef BUILDINGIDENTITY_H
#define BUILDINGIDENTITY_H
#include <string>
#include "Player.h"
#include <map>


enum BuildingType : int;

class MBuilding;

class BuildingIdentity
{
public:
    BuildingIdentity(BuildingType m_buildingType, std::string id_file);
    virtual ~BuildingIdentity();
    MBuilding* create(Player *owner);


    int getMetalCost(void);
    int getGazCost(void);
    int getMaxHealth(void);
    std::string getName(void);
    std::string getConstructSprite(PlayerColor playerColor);
    std::string getSpriteName(PlayerColor playerColor);
    int getWidth(void);
    int getHeight(void);
    int getVision(void);

    std::string getIcon(void);
    std::string getPlacedSprite(void);


    BuildingType getBuildingType(void);

    int getPopulationCapacity(void);

protected:
    int populationCapacity;
    int metalCost;
    int gazCost;
    int maxHealth;
    int vision;
    std::string name;
    std::string spriteName;
    std::string icon;
    int width;
    int height;
    std::string placedSprite;
    std::map<PlayerColor, std::string> constructSprites;
    std::map<PlayerColor, std::string> sprites;

    BuildingType buildingType;
};

#endif // BUILDINGIDENTITY_H
