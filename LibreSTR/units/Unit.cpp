#include "Unit.h"

int Unit::_currentId = 0;

int Unit::getCurrentId(void)
{
    _currentId++;
    int id = _currentId;
    return id;
}


Unit::Unit()
{
    _id = getCurrentId();
    name = "";
    type = UT_None;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    currentHealth = 1;
    maxHealth = 1;
}


Unit::~Unit()
{

}

bool Unit::isDead(void)
{
    return (currentHealth == 0);
}


int Unit::getId(void)
{
    return _id;
}

std::string Unit::getName(void)
{
    return name;
}


UnitType Unit::getType(void)
{
    return type;
}

int Unit::getMaxHealth(void)
{
    return maxHealth;
}

int Unit::getCurrentHealth(void)
{
    return currentHealth;
}

Player* Unit::getOwner(void)
{
    return owner;
}

void Unit::setOwner(Player *m_owner)
{
    owner = m_owner;
}

bool Unit::contains(int p_x, int p_y)
{
    return (p_x >= x &&
            p_x <= x + width &&
            p_y >= y &&
            p_y <= y + height);
}

bool Unit::contains(StiGame::Point *pt)
{
    return contains(pt->getX(), pt->getY());
}

StiGame::Point Unit::middle(void)
{
    StiGame::Point pt (x + width/2, y + height/2);
    return pt;
}

StiGame::Point Unit::maxPoint(void)
{
    StiGame::Point pt (x + width, y + height);
    return pt;
}

StiGame::Point Unit::topLeft(void)
{
    return StiGame::Point(x, y);
}

StiGame::Point Unit::topRight(void)
{
    return StiGame::Point(x + width, y);
}

StiGame::Point Unit::bottomRight(void)
{
    return StiGame::Point(x + width, y + height);
}

StiGame::Point Unit::bottomLeft(void)
{
    return StiGame::Point(x, y + height);
}

std::vector<StiGame::Point> Unit::corners(void)
{
    std::vector<StiGame::Point> pts;
    pts.push_back(topLeft());
    pts.push_back(topRight());
    pts.push_back(bottomRight());
    pts.push_back(bottomLeft());

    return pts;
}
