#ifndef UNIT_H
#define UNIT_H

#include <MPoint.h>
#include <Dimension.h>
#include "Player.h"
#include <string>

enum UnitType {
    UT_None,
    UT_Building,
    UT_Ground
};

class Unit :
        public StiGame::MPoint,
        public StiGame::Dimension

{
private:
    static int _currentId;
    int getCurrentId(void);

public:
    virtual ~Unit();
    std::string getName(void);
    std::string getSpriteName(void);
    UnitType getType(void);
    int getMaxHealth(void);
    int getCurrentHealth(void);
    bool isDead(void);
    virtual bool contains(int p_x, int p_y) = 0;
    int getId(void);
    Player* getOwner(void);
    void setOwner(Player *m_player);
protected:
    Unit();
    std::string name;
    std::string spriteName;
    UnitType type;
    int maxHealth;
    int currentHealth;
    Player *owner;
private:
    int _id;

};

#endif // UNIT_H
