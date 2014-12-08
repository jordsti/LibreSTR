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
    virtual std::string getSpriteName(void) = 0;
    UnitType getType(void);
    int getMaxHealth(void);
    int getCurrentHealth(void);
    bool isDead(void);
    virtual bool contains(int p_x, int p_y);
    bool contains(StiGame::Point *pt);
    int getId(void);
    virtual int getVision(void) = 0;
    Player* getOwner(void);
    void setOwner(Player *m_player);

    StiGame::Point middle(void);
    StiGame::Point maxPoint(void);

    StiGame::Point topLeft(void);
    StiGame::Point topRight(void);
    StiGame::Point bottomRight(void);
    StiGame::Point bottomLeft(void);

    std::vector<StiGame::Point> corners(void);

protected:
    Unit();
    std::string name;
    UnitType type;
    int maxHealth;
    int currentHealth;
    int vision;
    Player *owner;
private:
    int _id;

};

#endif // UNIT_H
