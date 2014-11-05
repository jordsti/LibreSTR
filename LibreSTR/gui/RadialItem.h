#ifndef RADIALITEM_H
#define RADIALITEM_H

#include <string>

class RadialItem
{
public:
    RadialItem(std::string m_name, std::string m_icon, std::string m_iconHover);
    virtual ~RadialItem();

    std::string getName(void);
    std::string getIcon(void);
    std::string getIconHover(void);

private:
    std::string name;
    std::string icon;
    std::string iconHover;
};

#endif // RADIALITEM_H
