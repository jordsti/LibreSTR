#ifndef GROUNDUNITIDENTITY_H
#define GROUNDUNITIDENTITY_H

#include <string>
#include "Player.h"

class MGroundUnit;

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

protected:
    std::string name;
    int metalCost;
    int gazCost;
    int attackRange;
    int width;
    int height;
    int vision;
    int maxHealth;
    int movemenSpeed;

};

#endif // GROUNDUNITIDENTITY_H
