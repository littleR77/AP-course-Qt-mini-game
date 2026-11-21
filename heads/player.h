#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include"weapon1.h"
class Player : public Character
{
    Q_OBJECT
public:
    virtual ~Player() = default;
    explicit Player(QObject *parent = nullptr);
    Weapon* weapon=nullptr;
};

#endif // PLAYER_H
