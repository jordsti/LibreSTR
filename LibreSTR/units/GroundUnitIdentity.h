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

    std::string getSprite(PlayerColor color, GroundUnitState state);

protected:
    std::string name;
    int metalCost;
    int gazCost;
    int attackRange;
    int width;
    int height;
    int vision;
    int maxHealth;
    int movementSpeed;
    std::map< GroundUnitState, std::map< PlayerColor, std::string > > sprites;
};

#endif // GROUNDUNITIDENTITY_H
