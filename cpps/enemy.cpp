#include "heads/enemy.h"

Enemy::Enemy(QObject *parent)
    : Character{parent}
{
    Hp = 20;damage = 9;
}
