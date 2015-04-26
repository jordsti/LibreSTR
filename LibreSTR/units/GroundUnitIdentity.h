#ifndef GROUNDUNITIDENTITY_H
#define GROUNDUNITIDENTITY_H

#include <string>
#include "Player.h"
#include <map>

class MGroundUnit;
enum GroundUnitState : int;

class GroundUnitIdentity
{
public:
    GroundUnitIdentity(std::string vf_file);
    virtual ~GroundUnitIdentity();

    MGroundUnit* create(Player *owner);

    std::string getName(void);
    int getMetalCost(void);
    int getGazCost(void);
    int getAttackRange(void);
    int getWidth(void);
    int getHeight(void);
    int getVision(void);
    int getMaxHealth(void);
    int getMovementSpeed(void);
    int getProductionTime(void);
    int getMovementStep(void);
    int getAttackDamage(void);
    int getAttackSpeed(void);
    int getPopulationCost(void);
    int getHarvestRange(void);
    int getHarvestSpeed(void);
    int getResourcesLimit(void);

    std::string getIcon(void);
    std::string getRadialIcon(void);
    std::string getRadialHoverIcon(void);


    std::string getSprite(PlayerColor color, GroundUnitState state);

    bool isCanHarvest(void);
    bool isCanBuild(void);
    bool isCanAttack(void);

protected:
    std::string name;
    std::string icon;
    std::string radialIcon;
    std::string radialHoverIcon;
    int metalCost;
    int gazCost;
    int attackRange;
    int attackDamage;
    int attackSpeed;
    int width;
    int height;
    int vision;
    int maxHealth;
    int movementSpeed;
    int movementStep;
    int productionTime;
    int populationCost;
    int harvestRange;
    int harvestSpeed;
    int resourcesLimit;

    bool canHarvest;
    bool canBuild;
    bool canAttack;

    std::map< GroundUnitState, std::map< PlayerColor, std::string > > sprites;
};

#endif // GROUNDUNITIDENTITY_H
