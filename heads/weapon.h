#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include<QString>
#include"enemy.h"

class Weapon : public QObject
{
    Q_OBJECT
public:
    const QString ppos = ":/Sprout Lands - Sprites - Basic pack/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png";
    explicit Weapon(QObject *parent = nullptr);
    Character* master=nullptr;
    Character* target=nullptr;
    QGraphicsProxyWidget* targetenemy=nullptr;
    QGraphicsProxyWidget* targetwidget=nullptr;
signals:
};

#endif // WEAPON_H
