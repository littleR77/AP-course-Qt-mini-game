#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Weapon;
class Enemy : public Character
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr);
    const qreal aspeed = 500;
    const QString ppos = ":/resources/enemy_r.png";
    const QString lpos = ":/resources/113201048_p3.png";
    qreal xspeed = 0;
    qreal yspeed = 0;
    qreal enemyr = 0;
    std::vector<Weapon*>weapons;
    std::vector<QGraphicsProxyWidget*>weaponwidget;

};

#endif // ENEMY_H
