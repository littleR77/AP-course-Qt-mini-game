#ifndef WEAPON1_H
#define WEAPON1_H

#include "weapon.h"

class Weapon1 : public Weapon
{
    Q_OBJECT
public:
    
    explicit Weapon1(QObject *parent = nullptr);
};

#endif // WEAPON1_H
