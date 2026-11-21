#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMovie>
#include <QTimer>
#include<QString>
#include<vector>
#include<QGraphicsProxyWidget>
#include<QLabel>
class Character : public QObject
{
    Q_OBJECT
protected:
   
    
public:
    int Hp;//生命
    int damage;//伤害
    bool skill_state;//处于技能状态
    QLabel* myLable = nullptr;
public:
    explicit Character(QObject *parent = nullptr);

signals:
};

#endif // CHARACTER_H
